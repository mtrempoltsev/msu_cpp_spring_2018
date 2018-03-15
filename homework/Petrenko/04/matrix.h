#pragma once

#include <stdexcept>

class Matrix {
    int * data;
    int r, c;

    class proxy {
        int p_col;
        const Matrix & owner;
    public:
        proxy(const Matrix &that, int col) : p_col(col), owner(that) {}

        int& operator[](int row) {
            if(row < 0 || row >= owner.r) {
                throw std::out_of_range("");
            }
            return owner.data[row * owner.c + p_col];
        }
    };

public:

    explicit Matrix(int cols = 3, int rows = 3) {
        if(rows < 0 || cols < 0) {
            throw std::out_of_range("");
        }
        data = new int[rows * cols];
        r = rows;
        c = cols;
    }

    ~Matrix() {
        delete[] data;
    }

    int getRows() {
        return r;
    }

    int getColumns() {
        return c;
    }

    proxy operator[](int col) const {
        if(col < 0 || col >= c) {
            throw std::out_of_range("");
        }
        return proxy(*this, col);
    }

    Matrix& operator*=(int val) {
        for(int i = 0; i < r * c; ++i) {
            data[i] *= val;
        }
        return *this;
    }

    bool operator==(const Matrix & other) const {
        if(this->r != other.r || this->c != other.c) {
            return false;
        }
        for(int i = 0; i < r * c; ++i) {
            if(this->data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(Matrix & other) const{
        return !(*this == other);
    }
};