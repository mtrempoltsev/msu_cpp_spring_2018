#include <iostream>
#include <thread>
#include <atomic>

int const MAX = int(1e6);

std::atomic<bool> global_parity{0};

void print(bool parity){
    std::string word = (!parity ? "ping" : "pong");
    for(int i = 0; i < MAX; ++i){
        while(global_parity != parity){
        }
        std::cout << word << "\n";
        global_parity.store(!parity);
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