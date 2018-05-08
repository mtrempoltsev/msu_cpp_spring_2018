#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

namespace Limits
{
    constexpr size_t MAX_ITERS = 1'000'000;
}

std::mutex mutex;
std::condition_variable access;
std::atomic_int cnt_iters{0};

void thread_function(int parity)
{
    for (;;) {
        bool do_return = false;;
        do {
            std::unique_lock<std::mutex> lg(mutex);
            while ((cnt_iters & 1) == (parity ^ 1)) {
                access.wait(lg);
            }

            if (cnt_iters >= Limits::MAX_ITERS) {
                ++cnt_iters;
                do_return = true;
                break;
            }

            std::cout << (parity == 0 ? "ping" : "pong") << std::endl;
            ++cnt_iters;
        } while (false);
        access.notify_one();

        if (do_return) {
            return;
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
