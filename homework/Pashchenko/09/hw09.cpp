#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

std::mutex m;
std::condition_variable dataReady;

int count = 0;
const int N = 1000000;

void ping_thread()
{
    while(count < N)
    {
        std::unique_lock<std::mutex> lock(m);

        if (count % 2 == 1)
            dataReady.wait(lock);

        std::cout << "ping" << std::endl;
        count++;
        dataReady.notify_one();
    }
}

void pong_thread()
{
    while(count < N)
    {
        std::unique_lock<std::mutex> lock(m);

        if (count % 2 == 0)
            dataReady.wait(lock);

        std::cout << "pong" << std::endl;
        count++;
        dataReady.notify_one();
    }
}

int main()
{
    try
    {
        std::thread t1(ping_thread);
        std::thread t2(pong_thread);
        t1.join();
        t2.join();
    }
    catch(...)
    {
        std::cerr << "error" << std::endl;
        return 1;
    }

    return 0;
}
