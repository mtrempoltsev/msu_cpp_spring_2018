#pragma once

#include <vector>
#include <algorithm>

class Array
{
public:
        const int& operator[](size_t row_) const
        {
                size_t row = array.size();
                if (row_ >= row)
                        throw std::out_of_range("");

                return array[row_];
        }

        int& operator[](size_t row_)
        {
                size_t row = array.size();
                if (row_ >= row)
                        throw std::out_of_range("");

                return array[row_];
        }

        Array& operator*=(int val)
        {
                std::for_each(array.begin(), array.end(), [val](int &n) { n *= val; });
                return *this;
        }

        bool operator==(const Array& other) const
        {
                return array == other.array;
        }

        bool operator!=(const Array& other) const
        {
                array != other.array;
        }

        void resize(size_t new_size)
        {
                array.resize(new_size);
        }

private:
        std::vector<int> array;
};

class Matrix
{
private:
        std::vector<Array> matrix;

        size_t col;
        size_t row;

public:
        Matrix(const size_t col_, const size_t row_) : col(col_), row(row_)
        {
                matrix.resize(col);

                for (int i = 0; i < col; i++)
                        matrix[i].resize(row);
        }

        size_t getRows() { return row; }
        size_t getColumns() { return col; }

        const Array& operator[](size_t col_) const
        {
                if (col_ >= col)
                        throw std::out_of_range("");
                return matrix[col_];
        }

        Array& operator[](size_t col_)
        {
                if (col_ >= col)
                        throw std::out_of_range("");
                return matrix[col_];
        }

        Matrix& operator*=(int val)
        {
                std::for_each(matrix.begin(), matrix.end(), [val](Array &vec) { vec *= val; });
                return *this;
        }

        bool operator==(const Matrix& other) const
        {
                if (!(row == other.row && col == other.col))
                        return false;

                for (int i = 0; i < col; i++)
                {
                        if (!(matrix[i] == other[i]))
                                return false;
                }

                return true;
        }

        bool operator!=(const Matrix& other) const
        {
                return !(*this == other);
        }
};
