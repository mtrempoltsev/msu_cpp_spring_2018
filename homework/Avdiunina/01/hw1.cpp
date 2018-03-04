//
// Created by polina997 on 3/2/18.
//
#include <cstdlib>
#include <chrono>
#include <iostream>
using namespace std;

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
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int** matrix_init(int m, int  n) {
    int** i_arr = new int*[n];
    for(int i = 0; i != n; i++){
        i_arr[i] = new int[m];
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            i_arr[i][j] = rand() % 100;
        }
    }
    return i_arr;
}

int64_t sum_row_matrix(int** matrix, int m, int n) {
    int64_t sum_matrix = 0;
    Timer t;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            sum_matrix += matrix[i][j];
        }
    }
    return sum_matrix;
}

int64_t sum_col_matrix(int** matrix, int m, int n) {
    int64_t sum_matrix = 0;
    Timer t;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            sum_matrix += matrix[j][i];
        }
    }
    return sum_matrix;
}

int main() {
    int n = 0;
    int m = 0;
    cout << "Enter the numbers of rows and columns: ";
    cin >> n >> m;
    int** matrix = matrix_init(m, n);
    cout << "the sum of the rows of the matrix = "
         << sum_row_matrix(matrix, m, n)
         << endl;
    cout << "the sum of the columns of the matrix = "
         << sum_col_matrix(matrix, m, n)
         << endl;
    return 0;
}
