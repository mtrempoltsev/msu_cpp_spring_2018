#include <chrono>
#include <iostream>

static const int SIZE = 10000;

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
    volatile auto a = new int [SIZE][SIZE];
    volatile long int sum = 0;

    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            a[i][j] = 1;
        }
    }
    std::cout<<"cols 10000:";
    {
        Timer T;
        for(int i = 0; i < SIZE; ++i) {
            for(int j = 0; j < SIZE; ++j) {
                sum += a[j][i];
            }
        }
    }
    return 0;
}
