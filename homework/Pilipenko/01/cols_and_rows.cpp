#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

const size_t size_of_rows = 10000;
const size_t size_of_cols = 10000;

class Timer {
public:
    Timer()
            : start_(chrono::high_resolution_clock::now()) {
    }

    ~Timer() {
        const auto finish = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::microseconds>(finish - start_).count() << " us.";
    }

private:
    const chrono::high_resolution_clock::time_point start_;
};

void sum_by_col(int **a, size_t num_col, size_t num_row) {
    Timer t;
    volatile int sum = 0;
    for (size_t i = 0; i < num_row; i++) {
        for (size_t j = 0; j < num_col; j++) {
            sum += a[j][i];
        }
    }
}

void sum_by_row(int **a, size_t num_col, size_t num_row) {
    Timer t;
    volatile int sum = 0;
    for (size_t i = 0; i < num_row; i++) {
        for (size_t j = 0; j < num_col; j++) {
            sum += a[i][j];
        }
    }
}

int main() {
    int **a = new int *[size_of_rows];
    for (size_t i = 0; i < size_of_rows; i++) {
        a[i] = new int[size_of_cols];
    }
    cout << "Time for cols: ";
    sum_by_col(a, size_of_cols, size_of_rows);
    cout << endl;
    cout << "Time for rows: ";
    sum_by_row(a, size_of_cols, size_of_rows);

    for (size_t i = 0; i < size_of_rows; i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}
