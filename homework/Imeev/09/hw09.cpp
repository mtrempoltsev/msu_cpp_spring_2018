#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;
std::condition_variable cv;

const int MAX_ITER = 1000000;
bool is_pong_time = false;

void printer(const std::string &str, bool value);

int main()
{
    try {
        std::thread t1(printer, "ping", false);
        std::thread t2(printer, "pong", true);
        t1.join();
        t2.join();
    } catch(...) {
        std::cerr << "error" << std::endl;
        return 1;
    }
    return 0;
}

void printer(const std::string &str, bool value)
{
    for(int i = 0; i < MAX_ITER; ++i) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [value]{return is_pong_time == value;});
        std::cout << str << std::endl;
        is_pong_time = !value;
        lk.unlock();
        cv.notify_one();
    }
}
