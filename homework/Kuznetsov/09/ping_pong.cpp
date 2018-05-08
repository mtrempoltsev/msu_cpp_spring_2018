#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

const size_t ITERS = 1000000;
std::mutex m;
std::condition_variable conditionVariable;
std::atomic<int> count(0);


void ping(){
    std::unique_lock<std::mutex> lock(m);
    while(count <= ITERS) {

        while(count % 2 == 1)
            conditionVariable.wait(lock);

        std::cout << "ping" << std::endl;
        count++;
        conditionVariable.notify_one();
    }
}
void pong(){
    std::unique_lock<std::mutex> lock(m);
    while(count <= ITERS) {

        while (count % 2 == 0)
            conditionVariable.wait(lock);
        std::cout << "pong" << std::endl;
        count++;
        conditionVariable.notify_one();

    }
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
     * но в этом случае тесты не проходятся из-за таймаута
     *
     * также если использовать while(flag) Вместо while(count %2 == 0) (bool flag)
     * и аналогичто в pong, то программа тоже работает быстрее
     * но на тестах валится по таймауту
     *
     * не понимаю почему так*/
    return 0;
}