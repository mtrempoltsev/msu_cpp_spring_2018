#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


const size_t OUT_SIZE = 1000000;
std::mutex m1, m2;
std::condition_variable var;
std::atomic_int counter;

void pinger() {
    while (true) {
        std::unique_lock<std::mutex> lock(m2);
        while (counter % 2 == 1) {
            var.wait(lock);
            if (counter >= OUT_SIZE * 2) {
                var.notify_all();
                return;
            }
        }

        {
            std::lock_guard<std::mutex> lk(m1);
            std::cout << "ping" << std::endl;
            counter++;
            var.notify_one();
        }
    }
}


void ponger() {
    while (true) {
        std::unique_lock<std::mutex> lock(m1);
        while (counter % 2 == 0) {
            var.wait(lock);
            if (counter >= OUT_SIZE * 2) {
                var.notify_all();
                return;
            }
        }

        {
            std::lock_guard<std::mutex> lk(m2);
            std::cout << "pong" << std::endl;
            counter++;
            var.notify_one();
        }
    }
}

int main() {
    counter = 0;
    std::thread t1(pinger);
    std::thread t2(ponger);
    t1.join();
    t2.join();
    return 0;
}