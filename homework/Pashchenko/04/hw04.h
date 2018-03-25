#pragma once

#include <stdexcept>
#include <iostream>
#include <cstddef>
#include <vector>

class Matrix
{
private:
    class Column
    {
    private:
        std::vector<int> col;

    public:
        Column(size_t nrows): col(nrows) {}

        bool operator==(const Column &other) const
        {
            return col == other.col;
        }

        bool operator!=(const Column& other) const
        {
            return col != other.col;
        }


        Column& operator*=(int mult)
        {
            for (size_t i = 0; i < col.size(); i++)
                col[i] *= mult;
            return *this;
        }

        int& operator[](size_t i)
        {
            if (i < col.size())
                return col[i];
            else
                throw std::out_of_range("");
        }

        const int& operator[](size_t i) const
        {
            if (i < col.size())
                return col[i];
            else
                throw std::out_of_range("");
        }
    };

    const size_t nrows, ncols;
    std::vector<Column> matrix;

public:
    Matrix(size_t cols, size_t rows): nrows(rows), ncols(cols), matrix(cols, rows) {}

    size_t getRows() const
    {
        return nrows;
    }

    size_t getColumns() const
    {
        return ncols;
    }

    bool operator==(const Matrix& other) const
    {
        return matrix == other.matrix;
    }

    bool operator!=(const Matrix& other) const
    {
        return matrix != other.matrix;
    }

    Matrix& operator*=(int mult)
    {
        for (size_t i = 0; i < matrix.size(); i++)
            matrix[i] *= mult;
        return *this;
    }

    Column& operator[](size_t i)
    {
        if (i < matrix.size())
            return matrix[i];
        throw std::out_of_range("");
    }

    const Column& operator[](size_t i) const
    {
        if (i < matrix.size())
            return matrix[i];
        throw std::out_of_range("");
    }
};
