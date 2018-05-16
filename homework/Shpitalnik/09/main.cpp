#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;
int i = 0;
const int n = 1000000;

void ping(){
    for (int j = 0; j<n; j++) {
        bool flag = false;
        do {
            mutex.lock();
            if (i == 0) {
                i++;
                std::cout << "ping\n";
                flag = true;
            }
            mutex.unlock();
        } while (!flag);
    }
}

void pong(){
    for (int j = 0; j<n; j++) {
        bool flag = false;
        do {
            mutex.lock();
            if (i == 1) {
                i--;
                std::cout << "pong\n";
                flag = true;
            }
            mutex.unlock();
        } while (!flag);
    }
}


int main() {
    std::thread t1(ping);
    std::thread t2(pong);
    t1.join();
    t2.join();
    return 0;
}
