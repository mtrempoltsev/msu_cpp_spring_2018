#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const size_t ITERS = 1000000;
std::mutex m;
std::condition_variable conditionVariable;
volatile int count = 0;
volatile bool ping_start_flag = false;


void ping(){
    std::unique_lock<std::mutex> lock(m);
    ping_start_flag = true;
    while(count <= ITERS) {

        //while(count % 2 == 1)
        conditionVariable.notify_one();
        conditionVariable.wait(lock);

        std::cout << "ping" << std::endl;
        ++count;
    }
    conditionVariable.notify_one();
}
void pong(){
    std::unique_lock<std::mutex> lock(m);

    while(!ping_start_flag)
        conditionVariable.wait(lock);

    while(count <= ITERS) {

        //while (count % 2 == 0)
        conditionVariable.notify_one();
        conditionVariable.wait(lock);
        std::cout << "pong" << std::endl;
        ++count;
    }
    conditionVariable.notify_one();
} 

int main() {
    std::thread thread(ping);
    std::thread(pong).join();
    thread.join();

    /*Если вместо всего этого написать
     * std::thread thread(ping);
     * pong();
     * thread.join();
     * То на моём компе это выполняется немного быстрее (вроде)
     *
     * не понимаю почему так*/
    return 0;
}