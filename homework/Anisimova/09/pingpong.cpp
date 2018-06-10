#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>

const int N = 1000000;

std::mutex m;
std::condition_variable c_v;
int i = 0;
void ping() {
        while(i < N -1) {
                std::unique_lock<std::mutex> lock(m);

                if (i % 2 == 1) {
                        c_v.wait(lock);
                }
                std::cout << "ping" <<std::endl;
                i++;
                c_v.notify_one();

        }

}

void pong() {
        while (i < N) {

                std::unique_lock<std::mutex> lock(m);

                if (i % 2 == 0) {
                        c_v.wait(lock);
                }
                std::cout << "pong" <<std::endl;;
                i++;
                c_v.notify_one();

        }
}

int main() {
        std::thread pin(ping);
        std::thread pon(pong);
        pin.join();
        pon.join();

        return 0;
}
