#pragma once

#include <iostream>

class Matrix {
private:
    int *matrix;
    std::size_t cols, rows;

    class Proxy {
    private:
        std::size_t j;
        const Matrix &link;
    public:
        Proxy(const Matrix &_link, std::size_t _j) : link(_link), j(_j) {}

        int &operator[](size_t _i) {
            if (_i >= link.rows) {
                throw std::out_of_range("bad row index");
            }
            return link.matrix[_i * link.cols + j];
        }

        int &operator[](size_t _i) const {
            if (_i >= link.rows) {
                throw std::out_of_range("bad row index");
            }
            return link.matrix[_i * link.cols + j];
        }
    };

public:
    Matrix(std::size_t _cols, std::size_t _rows) : cols(_cols), rows(_rows) {
        matrix = new int[_cols * _rows];
    }

    ~Matrix() {
        delete[] matrix;
    }

    Proxy operator[](std::size_t _j) {
        if (_j >= cols) {
            throw std::out_of_range("bad col index");
        }
        return Proxy(*this, _j);
    }

    const Proxy operator[](std::size_t _j) const {
        if (_j >= cols) {
            throw std::out_of_range("bad col index");
        }
        return Proxy(*this, _j);
    }

    size_t getColumns() const {
        return cols;
    }

    size_t getRows() const {
        return rows;
    }

    Matrix &operator*=(int k) {
        for (size_t i = 0; i < cols * rows; i++) {
            matrix[i] *= k;
        }
        return *this;
    }

    bool operator==(const Matrix &comp_matrix) const {
        if (cols != comp_matrix.cols || rows != comp_matrix.rows) {
            return false;
        }
        for (size_t i = 0; i < cols * rows; i++) {
            if (matrix[i] != comp_matrix.matrix[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix &comp_matrix) const {
        return !(*this == comp_matrix);
    }
};
