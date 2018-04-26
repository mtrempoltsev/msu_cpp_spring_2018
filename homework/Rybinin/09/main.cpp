#include <iostream>
#include <thread>
#include <mutex>
#include <string>

const int N = 1e6;

std::mutex mutex;
void func_t1()
{
    for(int i = 0; i < N; ++i)
    {
        mutex.lock();
        std::cout << "Ping" << std::endl;
        mutex.unlock();
    }
}

void func_t2()
{
    for(int i = 0; i < N; ++i)
    {
        mutex.lock();
        std::cout << "Pong" << std::endl;
        mutex.unlock();
    }
}

int main()
{
    std::thread t1(func_t1);
    std::thread t2(func_t2);
    t1.join();
    t2.join();
    return 0;
}
