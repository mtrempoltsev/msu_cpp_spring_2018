#include <iostream>
#include <thread>
#include <condition_variable>

std::mutex pinpongMutex;
std::condition_variable pingpongCV;
bool isPingPong = false;

void ping(int64_t toggle_number) {

    for (int i = 0; i < toggle_number; ++i) {
        std::unique_lock<std::mutex> ping_lock(pinpongMutex);
        while (isPingPong) {
            pingpongCV.wait(ping_lock);
        }
        std::cout << "Ping" << std::endl;
        isPingPong = true;
        pingpongCV.notify_one();
    }
}

void pong(int64_t toggle_number) {
    for (int i = 0; i < toggle_number; ++i) {
        std::unique_lock<std::mutex> pong_lock(pinpongMutex);
        while (!isPingPong) {
            pingpongCV.wait(pong_lock);
        }
        std::cout << "Pong" << std::endl;
        isPingPong = false;
        pingpongCV.notify_one();
    }
}

int main() {
    int64_t toggle_number = 1000000;
    std::thread pingThread(ping, toggle_number);
    std::thread pongThread(pong, toggle_number);
    pingThread.join();
    pongThread.join();
    return 0;
}