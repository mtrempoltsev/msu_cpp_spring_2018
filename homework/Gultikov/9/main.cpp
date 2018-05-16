#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable ready;

int count = 0;
const int N = 500000;

void ping_write()
{
    while(count < N){
        {
            std::unique_lock<std::mutex> lock(m);
            while(count % 2 == 1)
                ready.wait(lock);
        }
        std::cout<<"ping"<<std::endl;
        ++count;
        ready.notify_one();
    }
}

void pong_write()
{
    while(count < N){
        {
            std::unique_lock<std::mutex> lock(m);
            while(count % 2 == 0)
                ready.wait(lock);
        }
        std::cout<<"pong"<<std::endl;
        ++count;
        ready.notify_one();
    }
}

int main()
{
    std::thread t1(ping_write);
    std::thread t2(pong_write);
    t1.join();
    t2.join();
    return 0;
}
