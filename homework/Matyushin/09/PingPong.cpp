#include <iostream>
#include <thread>
#include <atomic>

const int N = 1000000;

std::atomic_bool pp(false);

void pingerFunc(){
    for (int i = 0; i < N; i++){
        while (pp){}
        std::cout << "ping" << std::endl;
        pp = true;
    }
}

void pongerFunc(){
    for (int i = 0; i < N; i++){
        while (!pp){}
        std::cout << "pong" << std::endl;
        pp = false;
    }
}

int main(void){
    std::thread pinger(pingerFunc);
    std::thread ponger(pongerFunc);
    
    pinger.join();
    ponger.join();
    
    return 0;
}
