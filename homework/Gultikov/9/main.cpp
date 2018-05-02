#include <iostream>
#include <thread>
#include <atomic>

const int num = 500000;
std::atomic<bool> is_ready(false);

void ping_write()
{
    for(int i = 0; i<num; i++)
    {
        while(is_ready);
        std::cout<<"ping\n";
        is_ready = true;
    }
}

void pong_write()
{
    for(int i = 0; i<num; i++)
    {
        while(!is_ready);
        std::cout<<"pong\n";
        is_ready = false;
    }
}

int main()
{
    std::thread t1(ping_write);
    std::thread t2(pong_write);
    t1.join();
    t2.join();
    return 0;
}
