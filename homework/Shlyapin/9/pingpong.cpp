#include <iostream>
#include <thread>
#include <mutex>

static int count = 1000000;
static bool flag = false;

#include <sched.h>

void thrn(int x) 
{
    std::string res = x ? "pong" : "ping";
    while (count) {
        while (flag != x) {
            sched_yield();
        }
        if (!count) {
            return;
        }
        std::cout << res << std::endl;
        --count;
        flag = !flag;
    }
}

int main()
{
    std::thread t1(thrn, 0), t2(thrn, 1);
    t1.join();
    t2.join();
    return 0;
}
