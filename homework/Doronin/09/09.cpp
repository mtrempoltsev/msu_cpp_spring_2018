#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::atomic<int> i(0);
std::atomic<bool> flaq(true);

std::mutex mutex;

void thread1()
{
    while(flaq)
    {
        std::lock_guard <std::mutex> lock(mutex);
        {
            if (i % 2 == 0 && i != 1000000)
            {
                std::cout << "ping" << std::endl;
                i++;
            }
            if(i == 1000000)
            {
                flaq = false;
            }
        }
    }
}

void thread2()
{
    while(flaq)
    {
        std::lock_guard<std::mutex> lock(mutex);
        {
            if (i % 2 == 1 && i != 1000000)
            {
                std::cout << "pong" << std::endl;
                i++;
            }
            if(i == 1000000)
            {
                flaq = false;
            }
        }
    }
}

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join();
    t2.join();
    return 0;
}