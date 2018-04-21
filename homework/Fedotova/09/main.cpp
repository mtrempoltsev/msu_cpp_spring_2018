#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

const int N = 1000000;
int i = 0;

std::mutex mutex;
std::condition_variable cv;

void ping() {
    while (i < 2 * N - 1) {
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (i % 2 == 1)
                cv.wait(lock);
            std::cout << "ping\n";
            i++;
        }
        cv.notify_one();
    }
}

void pong() {
    while (i < 2 * N) {
        {
            std::unique_lock<std::mutex> lock(mutex);
            while (i % 2 == 0)
                cv.wait(lock);
            std::cout << "pong\n";
            i++;
        }
        cv.notify_one();
    }
}

int main() {
    std::thread t1(ping);
    std::thread t2(pong);
    t1.join();
    t2.join();
    
    return 0;
}
