#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;
std::condition_variable cv;

int counter = 1000000;
bool is_ping_time = false;

void ping();
void pong();

int main()
{
    try {
        std::thread t1(ping);
        std::thread t2(pong);
        t1.join();
        t2.join();
    } catch(...) {
        std::cerr << "error" << std::endl;
        return 1;
    }
    return 0;
}

void pong()
{
    for(int i = 0; i < counter; ++i) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return is_ping_time;});
        std::cout << "pong" << std::endl;
        is_ping_time = false;
        lk.unlock();
        cv.notify_one();
    }
}

void ping()
{
    for(int i = 0; i < counter; ++i) {
        {
            std::lock_guard<std::mutex> lk(m);
            std::cout << "ping" << std::endl;
            is_ping_time = true;
        }
        cv.notify_one();
        {
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, []{return !is_ping_time;});
        }
    }
}
