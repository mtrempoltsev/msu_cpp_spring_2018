
#include <iostream>
#include <chrono>
#include <random>
#include <ctime>

// Constants for matrix sizes and value limits
namespace Limits
{
    constexpr uint32_t max_rows = 10'000;
    constexpr uint32_t max_cols = Limits::max_rows;
    constexpr uint32_t max_value = 10'000;
    constexpr uint32_t min_value = -Limits::max_value;
}

// Timer class
class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    void print_time() {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int main()
{
    // Setting sizes of matrix
    uint32_t rows = Limits::max_rows;
    uint32_t cols = Limits::max_cols;

    // Memory allocating
    int *data = new int[rows * cols];
    int **matrix = new int *[rows];

    for (int r = 0; r < rows; ++r) {
        matrix[r] = data + r * cols;
    }

    // Matrix filling
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<int> uid(Limits::min_value, Limits::max_value);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            matrix[r][c] = uid(gen) + r + c;
        }
    }

    // Testing
    Timer timer;
    volatile int sum = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            sum += matrix[r][c];
        }
    }
    timer.print_time();

    // Free memory
    delete[] matrix;
    delete[] data;
}

