#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

const int size = 10000;

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
    int **a = new int *[size];
    for (size_t i = 0; i < size; i++) {
        a[i] = new int[size];
    }
    cout << "Time for cols: ";
    sum_by_col(a, size, size);
    cout << endl;
    cout << "Time for rows: ";
    sum_by_row(a, size, size);

    for (size_t i = 0; i < size; i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}
