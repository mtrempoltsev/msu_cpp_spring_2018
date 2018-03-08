#include <chrono>
#include <iostream>

class Timer{
    public:
        Timer():start_(std::chrono::high_resolution_clock::now()){}

        ~Timer()
        {
            const auto finish = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
        }
    
    private:
        const std::chrono::high_resolution_clock::time_point start_;
};

void sum_by_rows(int** arr, size_t size, volatile int* sum)
{
    *sum = 0;
    std::cout << "Time sum_by_rows:" << std::endl;
    Timer t;
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            sum += arr[j][i];
}

void sum_by_cols(int** arr, size_t size, volatile int* sum)
{
    *sum = 0;
    std::cout << "Time sum_by_cols:" << std::endl;
    Timer t;
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            sum += arr[i][j];
}

int main()
{

    const size_t SIZE = 10000;
    int** arr = new int*[SIZE];

    for (size_t i = 0; i < SIZE; ++i)
        arr[i] = new int[SIZE];

    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
            arr[i][j] = (i+j)*2-i*j;
        
    volatile int sum = 0;

    sum_by_rows(arr, SIZE, &sum);    
    sum_by_cols(arr, SIZE, &sum);

    for (size_t i = 0; i < SIZE; ++i)
        delete [] arr[i];
    delete [] arr;
    return 0;
}
