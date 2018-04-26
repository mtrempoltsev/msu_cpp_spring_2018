#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

namespace Limits
{
    constexpr size_t MAX_ITERS = 1'000'000;
}

std::mutex mutex;
std::atomic_int cnt_iters{0};

void thread_function(int parity)
{
    for (;;) {
        std::lock_guard<std::mutex> lg(mutex);
        if (cnt_iters >= Limits::MAX_ITERS) {
            break;
        }

        if ((cnt_iters & 1) == parity) {
            std::cout << (parity == 0 ? "ping" : "pong") << std::endl;
            ++cnt_iters;
        }
    }
}

int main()
{
    std::thread t0(thread_function, 0);
    std::thread t1(thread_function, 1);

    t0.join();
    t1.join();
}
