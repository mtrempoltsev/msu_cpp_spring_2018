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
    {
        std::unique_lock<std::mutex> lock(mutex);
        for (uint32_t i = 0; i < maxN; ++i) {
            while(f.load(std::memory_order_relaxed)) {
                ready.wait(lock);
            }
            f.store(true, std::memory_order_relaxed);
            std::cout << "ping" << std::endl;
            ready.notify_one();
        }
    }
}

void pong() {
    {
        std::unique_lock<std::mutex> lock(mutex);
        for (uint32_t i = 0; i < maxN; ++i) {
            while(!f.load(std::memory_order_relaxed)) {
                ready.wait(lock);
            }
            f.store(false, std::memory_order_relaxed);
            std::cout << "pong" << std::endl;
            ready.notify_one();
        }
    }
}

int main() {
    std::thread t1(ping);
    std::thread t2(pong);
    
    t1.join();
    t2.join();

    return 0;
}
