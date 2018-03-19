//
// Created by alexmal on 3/19/18.
//
#include <iostream>
#include <stdint-gcc.h>

class Col {
private:
    int *col_;
    uint32_t rows_;
public:
    explicit Col(int *col, uint32_t rows) : col_(col), rows_(rows) {}

    int &operator[](const uint32_t row) const {
        if (row < rows_) {
            return col_[row];
        } else {
            throw std::out_of_range("");
        }
    }
};

class Matrix {
private:
    int **matrix_;
    uint32_t cols_,
            rows_;
public:
    Matrix(uint32_t cols, uint32_t rows) : cols_(cols), rows_(rows) {
        matrix_ = new int *[cols];
        for (int i = 0; i < cols; ++i) {
            matrix_[i] = new int[rows];
        }
    }

    void matrix_zero() {
        for (int row = 0; row < rows_; ++row) {
            for (int col = 0; col < cols_; ++col) {
                matrix_[col][row] = 0;
            }
        }
    }

    uint32_t getColumns() {
        return cols_;
    }

    uint32_t getRows() {
        return rows_;
    }

    const Col &operator[](uint32_t col) {
        if (col < cols_) {
            const Col &tmp = Col(matrix_[col], rows_);
            return tmp;
        } else {
            throw std::out_of_range("");
        }

    }

    Matrix &operator*=(const int &m) {
        for (int row = 0; row < rows_; ++row) {
            for (int col = 0; col < cols_; ++col) {
                matrix_[col][row] *= m;
            }
        }
        return *this;
    }

    bool operator==(const Matrix &matrix) const {
        if (this == &matrix) {
            return true;
        }
        if (matrix.rows_ != rows_ || matrix.cols_ != cols_) {
            return false;
        }
        for (int row = 0; row < rows_; ++row) {
            for (int col = 0; col < cols_; ++col) {
                if (matrix_[col][row] != matrix.matrix_[col][row]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix &matrix) {
        return !(*this == matrix);
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        for (int row = 0; row < matrix.rows_; ++row) {
            for (int col = 0; col < matrix.cols_; ++col) {
                os << matrix.matrix_[col][row];
            }
            os << std::endl;
        }
    }

    ~Matrix() {
        for (int i = 0; i < cols_; ++i) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }


};