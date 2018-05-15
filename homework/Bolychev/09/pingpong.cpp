#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;

bool isPingReady = true;
constexpr size_t MAX_ITER_FOR_THREAD = 500000;

void print_ping()
{
    for (size_t i = 0; i < MAX_ITER_FOR_THREAD; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() { return isPingReady; });
        std::cout << "ping" << std::endl;
        isPingReady = false;
        cv.notify_one();
    }
}

void print_pong()
{
    for (size_t i = 0; i < MAX_ITER_FOR_THREAD; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() { return !isPingReady; });
        std::cout << "pong" << std::endl;
        isPingReady = true;
        cv.notify_one();
    }
}

int main()
{
    std::thread t1(print_ping);
    std::thread t2(print_pong);
    
    t1.join();
    t2.join();
    return 0;
}