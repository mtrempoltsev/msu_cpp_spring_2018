#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>

std::atomic<int> i(0);
std::condition_variable v;

std::mutex mutex;

const int N = 1000000;

void thread1()
{
    while(i < N-1)
    {
        std::unique_lock <std::mutex> lock(mutex);
        if (i % 2 == 0)
        {
            std::cout << "ping" << std::endl;
            i++;
            v.notify_one();
        }
        if (i != N-1)
            v.wait(lock);
    }

}

void thread2()
{
    while(i < N)
    {
        std::unique_lock<std::mutex> lock(mutex);
        if (i % 2 == 1)
        {
            std::cout << "pong" << std::endl;
            i++;
            v.notify_one();
        }
        if (i != N)
            v.wait(lock);
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
