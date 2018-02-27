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

const size_t N = 1000;

int** initArray(const size_t N)
{
    int** arr = new int*[N];
    
    for (size_t i = 0; i < N; i++) {
        arr[i] = new int[N];
    }
    
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            arr[i][j] = i^2 + j;
        }
    }
    
    return arr;
}

int main()
{
    int** arr = initArray(N);
    
    std::cout << "Time for sum by rows:" << std::endl;
    int sum_by_rows = 0;
    {
        Timer t_sum_by_rows;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                sum_by_rows += arr[i][j];
            }
        }
    }
    
    std::cout << "Sum: " << sum_by_rows <<
    "\n\nTime for sum by columns:" << std::endl;
    int sum_by_cols = 0;
    {
        Timer t_sum_by_cols;
        for (size_t j = 0; j < N; j++) {
            for (size_t i = 0; i < N; i++) {
                sum_by_cols += arr[i][j];
            }
        }
    }
    std::cout << "Sum: " << sum_by_cols << std::endl;
    
    for (size_t i = 0; i < N; i++) {
        delete [] arr[i];
    }
    delete [] arr;
}
