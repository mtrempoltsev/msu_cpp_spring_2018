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
    const size_t size = 10000;
    volatile int s;
    int **a;
    a = (int**)malloc(sizeof(int*)*size);
    for (int i = 0; i < size; ++i)
        a[i] = (int*)malloc(sizeof(int)*size);
    Timer t;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            s += a[j][i];
    return 0;
}
