#include "matrix.h"
#include <iostream>

Matrix::~Matrix()
{
    for (size_t i = 0; i < cols; i++)
        delete[] arr[i];
    delete[] arr;
}

Matrix& Matrix::operator *= (int k)
{
    for (size_t i = 0; i < cols; i++)
        for (size_t j = 0; j < rows; j++)
            arr[i][j] *= k;
    return *this;
}

bool Matrix::operator == (const Matrix &m)
{
    if (rows != m.rows || cols != m.cols) return false;
    for (size_t i = 0; i < cols; i++)
        for (size_t j = 0; j < rows; j++)
            if (arr[i][j] != m.arr[i][j]) return false;
    return true;
}

bool Matrix::operator != (const Matrix &m)
{
    return !(*this == m);
}

Row Matrix::operator[](size_t j)
{
    if (j >= cols) throw std::out_of_range("");
    return Row(arr[j], rows);
}

Row Matrix::operator[](size_t j) const
{
    if (j >= cols) throw std::out_of_range("");
    return Row(arr[j], rows);
}

int& Row::operator [](size_t i)
{
    if (i >= rows) throw std::out_of_range("");
    return row[i];
}

int& Row::operator [](size_t i) const
{
    if (i >= rows) throw std::out_of_range("");
    return row[i];
}
