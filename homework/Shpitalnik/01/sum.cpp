#include <chrono>
#include <iostream>

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


class Matrix{
    int **p;
    int rows;
    int cols;
public:
    Matrix(int v_rows, int v_cols);
    int colsSum() const;
    int rowsSum() const;
    ~Matrix();

};

Matrix::Matrix(int v_rows, int v_cols) {
    rows = v_rows;
    cols = v_cols;
    p = new int*[rows];
    for (int i=0; i<rows; i++) {
        p[i] = new int[cols];
        for (int j = 0; j < cols; j++)
            p[i][j] = 1;
    }
}

int Matrix::colsSum() const {
    Timer my_timer;
    int sum =0;
    for (int j=0; j<cols; j++){
        for(int i=0; i<rows; i++){
            sum += p[i][j];
        }
    }
    return sum;
}

int Matrix::rowsSum() const {
    Timer my_timer;
    int sum =0;
    for (int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            sum += p[i][j];
        }
    }
    return sum;
}

Matrix::~Matrix() {
    for (int i=0; i<rows; i++){
        delete[] p[i];
    }
    delete[] p;
}

int main() {
    Matrix m(10000, 10000);
    m.rowsSum();
    m.colsSum();
    return 0;
}
