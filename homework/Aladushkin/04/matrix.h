#pragma once

#include <vector>
#include <algorithm>

class Array
{
public:
        const int& operator[](int row_) const
        {
                size_t row = array.size();
                if (row_ > row - 1)
                        throw std::out_of_range("");

                return array[row_];
        }

        int& operator[](int row_)
        {
                size_t row = array.size();
                if (row_ > row - 1)
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

        int col;
        int row;

public:

        Matrix(const int col_, const int row_) : col(col_), row(row_)
        {
                matrix.resize(col);

                for (int i = 0; i < col; i++)
                        matrix[i].resize(row);
        }

        int getRows() { return row; }
        int getColumns() { return col; }

        const Array& operator[](int col_) const
        {
                if (col_ > col - 1)
                        throw std::out_of_range("");
                return matrix[col_];
        }

        Array& operator[](int col_)
        {
                if (col_ > col - 1)
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
