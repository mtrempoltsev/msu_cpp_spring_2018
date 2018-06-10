//
// Created by polina997
//
//
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mut;
std::condition_variable streamReady;

const int N = 1000000;
int cnt = 0;

void ping()
{
    while(cnt < N)
    {
        std::unique_lock<std::mutex> lock(mut);
        if (cnt % 2 == 1)
            streamReady.wait(lock);

        cnt++;
        std::cout << "ping" << std::endl;

        streamReady.notify_one();
    }
}

void pong()
{
    while(cnt < N)
    {
        std::unique_lock<std::mutex> lock(mut);
        if (cnt % 2 == 0)
            streamReady.wait(lock);

        cnt++;
        std::cout << "pong" << std::endl;

        streamReady.notify_one();
    }
}

int main()
{
    try
    {
        std::thread t1(ping);
        std::thread t2(pong);
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
