#include <iostream>
#include <thread>
#include <mutex>
#include <string>

const int N = 1e6;

std::mutex mutex[2];

void func_t1()
{
    for(int i = 0; i < N; ++i)
    {
        mutex[0].lock();
        std::cout << "Ping" << std::endl;
        mutex[1].unlock();
    }
}

void func_t2()
{
    for(int i = 0; i < N; ++i)
    {
        mutex[1].lock();
        std::cout << "Pong" << std::endl;
        mutex[0].unlock();
    }
}

int main()
{
    mutex[1].lock();
    std::thread t1(func_t1);
    std::thread t2(func_t2);
    t1.join();
    t2.join();
    return 0;
}
