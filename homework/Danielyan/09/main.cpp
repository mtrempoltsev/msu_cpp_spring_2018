#include <atomic>
#include <iostream>
#include <thread>

int main(int argc, char **argv) {
    std::atomic<bool> ping_time{false};
    std::thread ping([&ping_time]() {
        for (size_t i = 0; i < 1000000; ++i) {
            while (!ping_time) {
            }
            std::cout << "ping\n";
            ping_time.store(false);
        }
    });
    std::thread pong([&ping_time]() {
        for (size_t i = 0; i < 1000000; ++i) {
            while (ping_time) {
            }
            std::cout << "pong\n";
            ping_time.store(true);
        }
    });

    ping.join();
    pong.join();

    return 0;
}
