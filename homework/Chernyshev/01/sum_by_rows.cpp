
#include <iostream>
#include <chrono>
#include <random>


// Constants for matrix sizes
namespace Sizes
{
    constexpr size_t max_rows = 10'000;
    constexpr size_t max_cols = max_rows;
}

// Constants for random generator
namespace Random
{
    constexpr unsigned int seed = 0xbadf00d;
    constexpr int min_value = -10'000;
    constexpr int max_value = 10'000;
}


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
    auto rows = Sizes::max_rows;
    auto cols = Sizes::max_cols;

    // Memory allocating
    auto *data = new int[rows * cols];
    auto **matrix = new int *[rows];

    for (decltype(rows) r = 0; r < rows; ++r) {
        matrix[r] = data + r * cols;
    }

    // Matrix filling
    std::mt19937 gen(Random::seed);
    std::uniform_int_distribution<int> uid(Random::min_value, Random::max_value);
    for (decltype(rows) r = 0; r < rows; ++r) {
        for (decltype(cols) c = 0; c < cols; ++c) {
            matrix[r][c] = uid(gen) + r + c;
        }
    }

    // Testing
    {
        Timer timer;
        volatile int sum = 0;
        for (decltype(rows) r = 0; r < rows; ++r) {
            for (decltype(cols) c = 0; c < cols; ++c) {
                sum += matrix[r][c];
            }
        }
    }

    // Free memory
    delete[] matrix;
    delete[] data;
}

