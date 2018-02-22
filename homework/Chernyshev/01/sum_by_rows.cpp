
#include <iostream>
#include <chrono>
#include <random>
#include <ctime>

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

    friend std::ostream &operator << (std::ostream &out, const Timer &timer);

private:
    auto get_time() const
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
    }

    const std::chrono::high_resolution_clock::time_point start_;
};

std::ostream &operator << (std::ostream &out, const Timer &timer)
{
    out << timer.get_time() << std::endl;
    return out;
}

int main()
{
    // Setting sizes of matrix
    auto rows = Sizes::max_rows;
    auto cols = Sizes::max_cols;

    // Memory allocating
    auto *data = new int[rows * cols];
    auto **matrix = new int *[rows];

    for (int r = 0; r < rows; ++r) {
        matrix[r] = data + r * cols;
    }

    // Matrix filling
    std::mt19937 gen(Random::seed);
    std::uniform_int_distribution<int> uid(Random::min_value, Random::max_value);
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
    std::cout << timer << std::endl;

    // Free memory
    delete[] matrix;
    delete[] data;
}

