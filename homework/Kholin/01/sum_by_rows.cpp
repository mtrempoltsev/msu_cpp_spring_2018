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
    const uint64_t numberOfStarts = 500; 
    Timer timer(numberOfStarts);

    const uint64_t numberOfRows = 500;
    const uint64_t numberOfColumns = 500;
    int* data = new int[numberOfRows * numberOfColumns];
    int** a = new int*[numberOfRows];
    for (auto i = 0; i < numberOfRows; ++i) {
        a[i] = &data[i * numberOfColumns];
        for (auto j = 0; j < numberOfColumns; ++j) {
            a[i][j] = i + j;
        }
    }

    int answer;
    for (auto t = 0; t < numberOfStarts; ++t) {
        answer = 0;
        for (auto j = 0; j < numberOfColumns; ++j) {
            for (auto i = 0; i < numberOfRows; ++i) {
                answer += a[i][j];
            }
        }
    }
    delete a;
    delete data;
    std::cout << answer << std::endl;

    return 0;
}
