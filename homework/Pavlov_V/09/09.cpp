
#include <iostream>
#include <thread>
#include <mutex>

bool isPing = true;
int countPing = 0;
int countPong = 0;
std::mutex m;

void ping() {
    while (countPing < 500000) {
        std::unique_lock<std::mutex> lock(m);
        if (isPing) {
            std::cout << "ping\n";
            countPing++;
            isPing = false;
        }
    }
}


void pong() {
    while (countPong < 500000) {
        std::unique_lock<std::mutex> lock(m);
        if (!isPing) {
            std::cout << "pong\n";
            countPong++;
            isPing = true;
        }
    }
}


int main() {
    std::thread t_ping(ping);
    std::thread t_pong(pong);
    t_ping.join();
    t_pong.join();
    return 0;
}
