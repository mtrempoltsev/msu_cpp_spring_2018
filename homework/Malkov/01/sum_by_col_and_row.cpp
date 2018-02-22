#include <chrono>
#include <iostream>
#include <vector>

namespace opt
{
    // Size of matrix
    constexpr size_t size = 10000;
    // Number of iterations
    constexpr size_t numb_of_iter = 10;
}

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
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us.";
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int sum_by_col(int** arr)
{
    Timer t;
    volatile int sum = 0;
    for(int i = 0; i < opt::size; i++)
    {
        for(int j = 0; j < opt::size; j++)
        {
            sum += arr[j][i];
        }
    }
}

int sum_by_row(int** arr)
{
    Timer t;
    volatile int sum = 0;
    for(int i = 0; i < opt::size; i++)
    {
        for(int j = 0; j < opt::size; j++)
        {
            sum += arr[i][j];
        }
    }
}

int main()
{
    // Allocates memory
    int** arr = new int*[opt::size];
    for(int i = 0; i < opt::size; i++)
    {
        arr[i] = new int[opt::size];
    }

    // Fill the array
    for(int i = 0; i < opt::size; i++)
    {
	    for(int j = 0; j < opt::size; j++)
        {
            arr[i][j] = 0;
	    }
    }

    // Show benchmark results
    for(int i = 0; i < opt::numb_of_iter; i++)
    {
        std::cout << "Time for sum by col: ";
        sum_by_col(arr);
        std::cout << " and time for sum by row: ";
        sum_by_row(arr);
        std::cout << std::endl;
    }

    // Release the memory area
    for(int i = 0; i < opt::size; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}
