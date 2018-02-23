#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int main()
{
    volatile int s;
    int *a[10000];
    for (int i = 0; i < 10000; ++i)
        a[i] = (int*)malloc(sizeof(int)*10000);
    Timer t;
    for (int i = 0; i < 10000; ++i)
        for (int j = 0; j < 10000; ++j)
            s += a[j][i];
    return 0;
}
