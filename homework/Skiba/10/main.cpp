#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

const int MAXN = 1000000;

class Sem{
    std::mutex mutex;
    std::condition_variable cv;
    int count;
public:
    Sem(int _count = 1): count(_count) {}
    void add() {
        std::unique_lock<std::mutex> lock(mutex);
        while (count <= 0) {
            cv.wait(lock);
        }
        --count;
    }
    void dec() {
        std::unique_lock<std::mutex> lock(mutex);
        ++count;
        cv.notify_one();
    }
};

Sem ping(1);
Sem pong(0);

void ping_f() {
    for (int i = 0; i < MAXN; ++i) {
        ping.add();
        std::cout << "ping" << std::endl;
        pong.dec();
    }
}

void pong_f() {
    for (int i = 0; i < MAXN; ++i) {
        pong.add();
        std::cout << "pong" << std::endl;
        ping.dec();
    }
}

int main(int argc, char *argv[]) {
    std::thread th1(ping_f);
    std::thread th2(pong_f);
    th1.join();
    th2.join();
    return 0;
}