#include <cstddef>
#include <chrono>
#include <iostream>


using namespace std;

class Timer {
public:
    Timer(string name)
        : start_(std::chrono::high_resolution_clock::now()) {
        this->name = name;
    }

    ~Timer() {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << this->name << ": " << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    string name;
    const std::chrono::high_resolution_clock::time_point start_;
};

int main() {
    const size_t rows = 10000;
    const size_t cols = 10000;
    uint64_t result;
    
    // init array
    int** array = new int*[rows];
    for (size_t i =0; i < rows; i++){
        array[i] = new int[cols];
        for (size_t j = 0; j < cols; j++) {
            array[i][j] = i + j;
        }
    }

    
    // tests

    {
        result = 0;
        Timer timer("by_rows");
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result += array[i][j];
            }
        }
    }
    cout << "result=" << result << "\n" << endl;
    {
        result = 0;
        Timer timer("by_cols");
        for (size_t j = 0; j < cols; j++) {
            for (size_t i = 0; i < rows; i++) {
                result += array[i][j];
            }
        }
    }
    cout << "result=" << result << "\n" << endl;
    delete[] array;
    return 0;
}
