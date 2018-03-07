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
    int n = 10000;
    int**a = new int*[n];
    for(int i = 0; i < n; i++)
    {
        a[i] = new int[n];
    }

    {
        Timer t;
        volatile int sum = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                sum += a[j][i];
    }

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}
