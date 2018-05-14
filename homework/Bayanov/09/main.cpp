#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

int const MAX = int(1e6);

std::mutex mtx;

std::atomic<bool> global_parity{0};

void print(bool parity){
    std::string word = (!parity ? "ping" : "pong");
    int ind = 0;
    while(ind < MAX){
        std::unique_lock<std::mutex> lock(mtx);
        if(global_parity == parity){
            std::cout << word << "\n";
            global_parity.store(!parity);
            ++ind;
        }
    }
}

int main() {
    std::thread t1(print, 0);
    std::thread t2(print, 1);

    if(t1.joinable())
        t1.join();
    if(t2.joinable())
        t2.join();

    return 0;
}