#include <chrono>
#include <iostream>

enum
{
    SIZE = 10000,
};

class
Timer
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

void sum_row(int **arr);
void sum_col(int **arr);

int
main()
{
    int **arr = new int*[SIZE];
    arr[0] = new int[SIZE * SIZE];
    for (int i = 1; i < SIZE; ++i) {
        arr[i] = arr[i - 1] + SIZE;
    }
    std::cout << "By rows:" << std::endl;
    sum_row(arr);
    std::cout << "By cols:" << std::endl;
    sum_col(arr);
    delete[] arr[0];
    delete[] arr;
    return 0;
}

void
sum_row(int **arr)
{
    Timer t;
    volatile int sum = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sum += arr[i][j];
        }
    }
}

void
sum_col(int **arr)
{
    Timer t;
    volatile int sum = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sum += arr[j][i];
        }
    }
}
