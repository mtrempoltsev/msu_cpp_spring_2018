#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <atomic>

const int maxN = 500000;

std::mutex mutex;
std::condition_variable ready;
std::atomic<bool> f(false);

void ping() {
    f.store(true, std::memory_order_relaxed);
    {
        std::unique_lock<std::mutex> lock(mutex);
        f = true;
        for (uint32_t i = 0; i < maxN; ++i) {
            std::cout << "ping" << std::endl;
            ready.notify_one();
            ready.wait(lock);
        }
    }
    ready.notify_one();
}

void pong() {
    bool x;
    do {
        x = f.load(std::memory_order_relaxed);
    } while (!x);
    {
        std::unique_lock<std::mutex> lock(mutex);
        for (uint32_t i = 0; i < maxN; ++i) {
            std::cout << "pong" << std::endl;
            ready.notify_one();
            ready.wait(lock);
        }
    }
    ready.notify_one();
}

int main() {
    std::thread t1(ping);
    std::thread t2(pong);
    
    t1.join();
    t2.join();

    return 0;
}
