#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <iostream>

class Matrix
{
    int** matr;
    int cols;
    int rows;

    class Array
    {
        int* a;
        int size;

    public:
        Array(int* a, int size)
            : a(a)
            , size(size)
        {}

        int& operator[](const int j)
        {
            if (j >= 0 && j < size)
            {
                return a[j];
            }
            else
                throw std::out_of_range("Out of range");
        }

        const int& operator[](const int j) const
        {
            if (j >= 0 && j < size)
            {
                return a[j];
            }
            else
                throw std::out_of_range("Out of range");
        }
    };

public:
    Matrix(int col, int row)
        : cols(col)
        , rows(row)
    {
        matr = new int*[cols];
        for (int i = 0; i < cols; i++)
        {
            matr[i] = new int[rows];
        }
    }

    int getColumns() const
    {
        return cols;
    }

    int getRows() const
    {
        return rows;
    }

    Array operator[](const int i)
    {
        if (i >= 0 && i < cols)
        {
            return Array(matr[i], rows);
        }
        else
            throw std::out_of_range("Out of range");
    }

    const Array operator[](const int i) const
    {
        if (i >= 0 && i < cols)
        {
            return Array(matr[i], rows);
        }
        else
            throw std::out_of_range("");
    }

    Matrix& operator*=(const int a)
    {
        for (int i = 0; i < cols; i++)
            for (int j = 0; j < rows; j++)
                matr[i][j] *= a;
        return *this;
    }

    bool operator==(const Matrix& other) const
    {
        if (cols != other.cols && rows != other.rows)
            return false;

        for (int i = 0; i < cols; i++)
            for (int j = 0; j < rows; j++)
            {
                if (matr[i][j] != other.matr[i][j])
                    return false;
            }
        return true;
    }

    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }

    ~Matrix()
    {
        for (int i = 0; i < cols; i++)
        {
            delete[] matr[i];
        }
        delete[] matr;
    }
};

#endif // MATRIX_H_INCLUDED
