#include <condition_variable>
#include <atomic>
#include <cstdio>
#include <thread>
#include <mutex>

std::mutex m;
std::condition_variable cv;

constexpr size_t str_size = 5;
constexpr int MAX_ITER = 500000;
std::atomic<bool> is_pong_time(false);

void printer(bool value);

int main()
{
    try {
        std::thread t1(printer, false);
        std::thread t2(printer, true);
        t1.join();
        t2.join();
    } catch(...) {
        printf("error\n");
        return 1;
    }
    return 0;
}

void printer(bool value)
{
    char str_ping[] = "ping\n";
    char str_pong[] = "pong\n";
    char *str;
    if(value) {
        str = str_pong;
    } else {
        str = str_ping;
    }
    for(int i = 0; i < MAX_ITER; ++i) {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [value]{return is_pong_time == value;});
        fwrite(str, sizeof(char), str_size, stdout);
        is_pong_time = !value;
        lk.unlock();
        cv.notify_one();
    }
}
