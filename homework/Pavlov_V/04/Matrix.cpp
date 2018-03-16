#include "Matrix.hpp"
#include <iostream>
#include <vector>


Matrix::Matrix(int rows, int cols):
    matrix(std::vector<std::vector<int>> (rows, std::vector<int> (cols, 1))) {
    countRows = rows;
    countColunmns = cols;
}

int Matrix::getRows() const {
    return countColunmns;
}

int Matrix::getColumns() const {
    return countRows;
}

void Matrix::operator *= (const int value) {
    for(int i = 0; i < countRows; ++i) {
        for(int j = 0; j < countColunmns; ++j) {
            matrix[i][j] *= value;
        }
    }
}

bool Matrix::operator != (const Matrix& m1) const {
    if(*this == m1) return false;
    return true;
}

void Matrix::print() const {
    for(int i = 0; i < countRows; ++i) {
        for(int j = 0; j < countColunmns; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Matrix::operator == (const Matrix& m1) const {
    if(countRows == m1.countRows && countColunmns == m1.countColunmns) {
        for(int i = 0; i < countRows; ++i) {
            for(int j = 0; j < countColunmns; ++j) {
                if(matrix[i][j] != m1.matrix[i][j]) return false;
            }
        }
        return true;
    }
    return false;
}

Matrix::Proxy::Proxy(std::vector<int> &_array): _array(&_array) {}

int& Matrix::Proxy::operator [] (int index) {
    if(index > (*_array).size() - 1) {
        throw std::out_of_range("");
    }
    return (*_array)[index];
}

Matrix::Proxy Matrix::operator [] (int index) {
    if(index > countRows - 1) {
        throw std::out_of_range("");
    }
    return matrix[index];
}

