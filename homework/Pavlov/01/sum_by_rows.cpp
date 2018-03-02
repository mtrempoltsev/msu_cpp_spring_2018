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
    int** a = new int*[SIZE];
    for(int i = 0; i < SIZE; ++i)
        a[i] = new int[SIZE];
    volatile long int sum = 0;

    for(int i = 0; i < SIZE; ++i) {
        for(int j = 0; j < SIZE; ++j) {
            a[i][j] = 1;
        }
    }
    std::cout<<"rows 10000:";
    {
        Timer t;
        for(int i = 0; i < SIZE; ++i) {
            for(int j = 0; j < SIZE; ++j) {
                sum += a[i][j];
            }
        }
    }
    for(int i = 0; i < SIZE; ++i) {
        delete [] a[i];
    }
    delete [] a;

    return 0;
}
