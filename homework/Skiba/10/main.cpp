#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

const int MAXN = 1000000;

std::atomic<int> a;
std::mutex mutex1, mutex2;
std::condition_variable cv;

void pr1() {
    if (!a) {
            std::lock_guard<std::mutex> g(mutex1);
            a++;
            std::cout << "ping" << std::endl;
            cv.notify_one();
    }

    while (true) {
        std::unique_lock<std::mutex> lock(mutex1);
        while (a%2 == 1) {
            cv.wait(lock);
            if (a >= MAXN) {
                std::lock_guard<std::mutex> g(mutex2);
                cv.notify_all();
                return;
            }
        }

        {
            std::lock_guard<std::mutex> g(mutex2);
            a++;
            std::cout << "ping" << std::endl;
            cv.notify_all();
        }
    }
}

void pr2() {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex1);
        while (a%2 == 0) {
            cv.wait(lock);
            if (a >= MAXN) {
                std::lock_guard<std::mutex> g(mutex2);
                cv.notify_all();
                return;
            }
        }

        {
            if (a >= MAXN) {
                std::lock_guard<std::mutex> g(mutex2);
                cv.notify_all();
                return;
            }
            std::lock_guard<std::mutex> g(mutex2);
            a++;
            std::cout << "pong" << std::endl;
            cv.notify_all();
        }
    }
}

int main(int argc, char *argv[]) {
    a.store(0);
    std::thread t1(pr1);
    std::thread t2(pr2);
    t1.join();
    t2.join();
    return 0;
}