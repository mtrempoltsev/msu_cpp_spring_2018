#include <iostream>
#include <thread>
#include <mutex>

constexpr int Count = 1000000;

#include <condition_variable>

std::mutex m[2];

void thrfunc(int f)
{
    std::string res = f ? "pong" : "ping";
    for (int i = 0; i < Count; ++i) {
        m[f].lock();
        std::cout << res << std::endl;
        m[!f].unlock();
    }
}

int main()
{
    m[1].lock();
    std::thread thr0(thrfunc, 0);
    std::thread thr1(thrfunc, 1);
    thr1.join();
    thr0.join();
    return 0;
}
