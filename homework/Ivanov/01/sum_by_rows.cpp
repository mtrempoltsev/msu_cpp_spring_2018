#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;

const int SIZE = 10000;

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

int main(int argc, char const *argv[])
{
    int **arr;
    arr = new int*[SIZE];
    volatile int sum = 0;
    for(int i = 0; i < SIZE; i++) {
        arr[i] = new int[SIZE];
        for(int j = 0; j < SIZE; j++) {
            arr[i][j] = ++sum;
        }
    }
    Timer timer;
    sum = 0;
    for(volatile int i = 0; i < SIZE; i++) {
        for(volatile int j = 0; j < SIZE; j++) {
            sum += arr[i][j];
        }
    }
    for(int i = 0; i < SIZE; i++) {
    	delete[] arr[i];
    }
    delete[] arr;
    return 0;
}
