#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;

bool Is_Ping_Ready = true;
constexpr size_t MAX_ITER = 500000;

void ping()
{
    for (size_t i = 0; i < MAX_ITER; ++i) 
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() { return Is_Ping_Ready; });
        std::cout << "ping" << std::endl;
        Is_Ping_Ready = false;
        cv.notify_one();
    }
}

void pong()
{
    for (size_t i = 0; i < MAX_ITER; ++i) 
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() { return !Is_Ping_Ready; });
        std::cout << "pong" << std::endl;
        Is_Ping_Ready = true;
        cv.notify_one();
    }
}

int main()
{
    std::thread t1(ping);
    std::thread t2(pong);
    
    t1.join();
    t2.join();
    return 0;
}
