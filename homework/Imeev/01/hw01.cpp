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

void sum_row(int **arr, size_t n);
void sum_col(int **arr, size_t n);

int
main(void)
{
    int **arr = new int*[SIZE];
    arr[0] = new int[SIZE * SIZE];
    for (int i = 1; i < SIZE; ++i) {
        arr[i] = arr[i - 1] + SIZE;
        for (int j = 0; j < SIZE; ++j) {
            arr[i][j] = 1;
        }
    }
    std::cout << "By rows:" << std::endl;
    sum_row(arr, SIZE);
    std::cout << "By cols:" << std::endl;
    sum_col(arr, SIZE);
    delete[] arr[0];
    delete[] arr;
    return 0;
}

void
sum_row(int **arr, size_t n)
{
    Timer t;
    volatile int sum = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            sum += arr[i][j];
        }
    }
}

void
sum_col(int **arr, size_t n)
{
    Timer t;
    volatile int sum = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            sum += arr[j][i];
        }
    }
}
