#include "matrix.h"
#include <iostream>

Matrix::Matrix(size_t c, size_t r)
{
    rows = r;
    cols = c;
    arr = new int*[cols];
    for (size_t i = 0; i < cols; i++)
        arr[i] = new int[rows];
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < cols; i++)
        delete[] arr[i];
    delete[] arr;
}

const Matrix& Matrix::operator *= (int k)
{
    for (size_t i = 0; i < cols; i++)
        for (size_t j = 0; j < rows; j++)
            arr[i][j] *= k;
    return *this;
}

bool operator == (const Matrix &m1, const Matrix &m2)
{
    if (m1.rows != m2.rows || m1.cols != m2.cols) return false;
    for (size_t i = 0; i < m1.cols; i++)
        for (size_t j = 0; j < m1.rows; j++)
            if (m1.arr[i][j] != m2.arr[i][j]) return false;
    return true;
}

bool operator != (const Matrix &m1, const Matrix &m2)
{
    return !(m1 == m2);
}

Row Matrix::operator[](size_t j)
{
    if (j >= cols) throw std::out_of_range("");
    return Row(arr[j], rows);
}

int& Row::operator [](size_t i)
{
    if (i >= rows) throw std::out_of_range("");
    return row[i];
}
