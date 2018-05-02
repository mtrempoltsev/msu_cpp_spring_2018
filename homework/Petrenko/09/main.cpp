#include <cstdio>
#include <thread>
#include <condition_variable>

class Semaphore
{
    std::mutex mutex_;
    std::condition_variable condition_;
    int counter_;
public:
    explicit Semaphore(int initialValue = 1)
            : counter_(initialValue)
    {
    }

    void enter()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this](){ return counter_ > 0; });
        --counter_;
    }

    void leave()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        ++counter_;
        condition_.notify_one();
    }
};

Semaphore s1(1), s2(0);

int i = 0;

void f1() {
    for(size_t i = 0; i < 500000; ++i) {
        s1.enter();
        printf("ping\n");
        s2.leave();
    }
}

void f2() {
    for(size_t i = 0; i < 500000; ++i) {
        s2.enter();
        printf("pong\n");
        s1.leave();
    }
}

int main() {


    std::thread t1(f1);
    std::thread t2(f2);

    t1.join();
    t2.join();

    return 0;
}