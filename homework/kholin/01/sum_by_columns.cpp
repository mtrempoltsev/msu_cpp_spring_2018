#include <chrono>
#include <iostream>

class Timer {
public:
    Timer(uint64_t numberOfStarts)
        : start_(std::chrono::high_resolution_clock::now()), numberOfStarts_(numberOfStarts) {
    }

    ~Timer() {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() / numberOfStarts_ <<
            " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
    const uint64_t numberOfStarts_;
};

int main() {
    const uint64_t numberOfRows = 500;
    const uint64_t numberOfColumns = 500;
    volatile int a[numberOfRows][numberOfColumns], b[numberOfRows][numberOfColumns], c[numberOfRows][numberOfColumns];
    for (auto i = 0; i < numberOfRows; ++i) {
        for (auto j = 0; j < numberOfColumns; ++j) {
            a[i][j] = i * j;
            b[i][j] = i + j;
        }
    }

    const uint64_t numberOfStarts = 500; 
    Timer* timer = new Timer(numberOfStarts);
    for (auto t = 0; t < numberOfStarts; ++t) {
        for (auto i = 0; i < numberOfRows; ++i) {
            for (auto j = 0; j < numberOfColumns; ++j) {
                c[i][j] = a[i][j] + b[i][j];
            }
        }
    }
    delete timer;
}
