#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable access;

namespace params {
    constexpr size_t MAXITERS = 100;
    unsigned short cnt = 0;
}

void thread_function(unsigned short parity) {
    while (true) {
        bool do_return = false;
        std::unique_lock<std::mutex> lg(mutex);
        while ((parity ^ 1) == (params::cnt & 1)) { access.wait(lg); }
        if (params::cnt >= params::MAXITERS) {
            params::cnt++;
            do_return = true;
            goto skipp;
        }
        std::cout << (parity == 0 ? "ping" : "pong") << std::endl;
        params::cnt++;
        skipp:
        access.notify_one();
        if (do_return) { return; }
    }
}

int main() {
    std::thread t0(thread_function, 0);
    std::thread t1(thread_function, 1);
    t0.join();
    t1.join();
}


