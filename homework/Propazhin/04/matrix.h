#pragma once
#include <stdio.h>

class Row;

class Matrix
{
public:
    int **arr;
    size_t rows, cols;
    Matrix(size_t c, size_t r):
        rows(r), cols(c)
    {
        arr = new int*[cols];
        for (size_t i = 0; i < cols; i++)
            arr[i] = new int[rows];
    }
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
    Matrix& operator *= (int k);
    bool operator == (const Matrix &m);
    bool operator != (const Matrix &m);
    Row operator[] (size_t i);
    Row operator[] (size_t i) const;
};

class Row
{
public:
    Row(int* r, size_t t):
        row(r), rows(t) {}
    int *row;
    size_t rows;
    int& operator[](size_t i);
    int& operator[](size_t i) const;
};
