#include <iostream>
#include <chrono>

class Timer {
    std::chrono::high_resolution_clock::time_point start_;

public:
    Timer() : start_(std::chrono::high_resolution_clock::now()) {}

    ~Timer() {}

    void set_new_start_point() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    std::chrono::milliseconds get_duration() {
        const auto finish = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(finish -
                                                                     start_);
    }
};

class Matrix {
    int32_t** matrix;
    size_t row_size;
    size_t column_size;

    int64_t summation_by_row() {
        volatile int64_t sum = 0;
        for (size_t row = 0; row < row_size; ++row) {
            for (size_t column = 0; column < column_size; ++column) {
                sum += matrix[row][column];
            }
        }
        return sum;
    }

    int64_t summation_by_column() {
        volatile int64_t sum = 0;
        for (size_t column = 0; column < column_size; ++column) {
            for (size_t row = 0; row < row_size; ++row) {
                sum += matrix[row][column];
            }
        }
        return sum;
    }

public:
    Matrix() = delete;

    Matrix(size_t size_r, size_t size_c) : row_size(size_r), column_size(size_c) {
        matrix = new int32_t*[row_size];
        for (size_t it = 0; it < row_size; ++it) {
            matrix[it] = new int32_t[column_size];
        }
    }

    ~Matrix() {
        for (size_t it = 0; it < row_size; ++it) {
            delete[] matrix[it];
        }
        delete[] matrix;
    }

    void fill_matrix_random_values() {
        srand(time(nullptr));
        for (size_t row = 0; row < row_size; ++row) {
            for (size_t column = 0; column < column_size; ++column) {
                matrix[row][column] = rand() % 100;
            }
        }
    }

    void analyze_different_summation() {
        const size_t amount_traverse = 1;

        Timer t;
        for (size_t it = 0; it < amount_traverse; ++it) {
            summation_by_row();
        }
        double row_traverse_duration =
                static_cast<double>(t.get_duration().count());

        t.set_new_start_point();
        for (size_t it = 0; it < amount_traverse; ++it) {
            summation_by_column();
        }
        double column_traverse_duration =
                static_cast<double>(t.get_duration().count());

        std::cout << "Average duration of summation by row: "
                  << row_traverse_duration / amount_traverse
                  << " milliseconds \n";

        std::cout << "Average duration of summation by column: "
                  << column_traverse_duration / amount_traverse
                  << " milliseconds\n";

        std::cout << "Summation by row in "
                  << column_traverse_duration / row_traverse_duration
                  << " times faster than summation by column!\n";
    }
};

int main() {
    Matrix matrix(1000, 10000);
    matrix.fill_matrix_random_values();
    matrix.analyze_different_summation();
    return 0;
}
