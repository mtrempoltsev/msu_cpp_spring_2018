
#include <iostream>
#include <chrono>
#include <random>


// Constants for matrix sizes
enum class Sizes : size_t
{
    max_rows = 10'000,
    max_cols = 10'000,
};

// Constants for random generator
enum class Random
{
    seed = 0xbadf00d,
    min_value = -10'000,
    max_value = 10'000,
};


// Timer class
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
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};


int main()
{
    // Setting sizes of matrix
    size_t rows = static_cast<size_t>(Sizes::max_rows);
    size_t cols = static_cast<size_t>(Sizes::max_cols);

    // Memory allocating
    auto *data = new int[rows * cols];
    auto **matrix = new int *[rows];

    for (size_t r = 0; r < rows; ++r) {
        matrix[r] = data + r * cols;
    }

    // Matrix filling
    std::mt19937 gen(static_cast<unsigned>(Random::seed));
    std::uniform_int_distribution<int> uid(static_cast<int>(Random::min_value), static_cast<int>(Random::max_value));
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            matrix[r][c] = uid(gen) + r + c;
        }
    }

    // Testing
    {
        Timer timer;
        volatile int sum = 0;
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < cols; ++c) {
                sum += matrix[r][c];
            }
        }
    }

    // Free memory
    delete[] matrix;
    delete[] data;
}

