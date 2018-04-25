#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const int MAXN = 1000000;

int a = 0;
std::mutex mutex;
std::mutex fp;
std::mutex sp;
std::condition_variable cv1;
std::condition_variable cv2;

void pr1() {
    if (!a) {
            std::lock_guard<std::mutex> g(mutex);
            a++;
            std::cout << "ping" << std::endl;
            cv2.notify_one();
    }
    while (true) {
        std::unique_lock<std::mutex> lock(fp);
        while (a%2 == 1) {
            cv1.wait(lock);
            if (a >= MAXN) {
                std::lock_guard<std::mutex> g(mutex);
                cv2.notify_one();
                return;
            }
        }
        {
            std::lock_guard<std::mutex> g(mutex);
            a++;
            std::cout << "ping" << std::endl;
            cv2.notify_one();
        }
    }
}

void pr2() {
    while (true) {
        std::unique_lock<std::mutex> lock(sp);
        while (a%2 == 0) {
            cv2.wait(lock);
            if (a >= MAXN) {
                std::lock_guard<std::mutex> g(mutex);
                cv1.notify_one();
                return;
            }
        }
        {
            if (a >= MAXN) {
                std::lock_guard<std::mutex> g(mutex);
                cv1.notify_one();
                return;
            }
            std::lock_guard<std::mutex> g(mutex);
            a++;
            std::cout << "pong" << std::endl;
            cv1.notify_one();
        }
    }
}

int main(int argc, char *argv[]) {
    std::thread t1(pr1);
    std::thread t2(pr2);
    t1.join();
    t2.join();
    return 0;
}