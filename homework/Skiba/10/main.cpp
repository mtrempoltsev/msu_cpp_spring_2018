#include <iostream>
#include <thread>
#include <mutex>


int a = 0;
std::mutex mutex;

void pr1() {
    while (a < 1000000) {
        if (!(a%2)) {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "ping" << std::endl;
            a++;
        }
    }
}

void pr2() {
    while (a < 1000000) {
        if (a%2) {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "pong" << std::endl;
            a++;
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