#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


const size_t OUT_SIZE = 500000;
std::mutex m;
std::condition_variable var;
std::atomic_int counter;

void pinger() {
    while (true) {
        {
            std::unique_lock<std::mutex> lock(m);
            var.wait(lock, []() { return counter % 2 == 1;});
            printf("ping\n");
            counter++;
        }
        var.notify_one();
        if (counter >= OUT_SIZE * 2 - 1) {
            return;
        }
    }
}


void ponger() {
    while (true) {
        {
            std::unique_lock<std::mutex> lock(m);
            var.wait(lock, []() { return counter % 2 == 0;});
            printf("pong\n");
            counter++;
        }
        var.notify_one();
        if (counter >= OUT_SIZE * 2) {
            return;
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
