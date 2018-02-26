#include <chrono>
#include <iostream>

#define ROWS 1000
#define COLS 1000

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
    int **a = new int*[ROWS];
    for(int i = 0; i < ROWS; ++i)
        a[i] = new int[COLS];

    Timer t;
    volatile long sum = 0;
    for(int i = 0; i < ROWS; ++i)
        for(int j = 0; j < COLS; ++j)
            sum += a[i][j];

    long s2 = sum*2;

    return 0;
}