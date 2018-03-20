#pragma once
#include <stdio.h>

class Row;

class Matrix
{
public:
    int **arr;
    size_t rows, cols;
    Matrix(size_t c, size_t r);
    ~Matrix();
    size_t getRows()
    {
        return rows;
    }
    size_t getColumns()
    {
        return cols;
    }
    int getElem(size_t i, size_t j)
    {
        return arr[i][j];
    }
    const Matrix& operator *= (int k);
    Row operator[] (size_t i);
};

bool operator == (const Matrix &m1, const Matrix &m2);
bool operator != (const Matrix &m1, const Matrix &m2);

class Row
{
public:
    Row(int* r, size_t t):
        row(r), rows(t) {}
    int *row;
    size_t rows;
    int& operator[](size_t i);
};
