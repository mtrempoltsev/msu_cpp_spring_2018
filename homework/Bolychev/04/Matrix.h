//
// Created by Anton on 21/03/18.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <stdexcept>
#include <vector>

class Matrix {
private:

    class Shape
    {
    public:
        size_t rows;
        size_t cols;
        
        bool operator==(const Shape& other) const
        {
            if (other.cols == cols && other.rows == rows) {
                return true;
            } else {
                return false;
            }
        }

        bool operator!=(const Shape& other) const
        {
            if (other.cols != cols || other.rows != rows) {
                return true;
            } else {
                return false;
            }
        }
    };

    class Column { //Proxy
        int* _data;
        size_t _rows;
    public:

        Column()
        {
            _data = nullptr;
            _rows = 0;
        }

        void setColoumn(size_t rows)
        {
            if (_data) {
                delete [] _data;
            }

            _data = new int[rows];
            _rows = rows;
        }

        ~Column()
        {
            if (_data) {
                delete[] _data;
            }
        }

        int& operator[](const size_t i) const
        {
            if (i >= _rows) {
                throw std::out_of_range("Matrix::coloumn: index is out of range");
            }

            return _data[i];
        }
    };


    Shape shape;
    Column* _data;
public:

    Matrix(const size_t n_cols, const size_t n_rows)
    {
        _data = new Column[n_cols];
        shape.rows = n_rows;
        shape.cols = n_cols;

        for (size_t i = 0; i < shape.cols; ++i)
        {
            _data[i].setColoumn(n_rows);
        }
    }

    ~Matrix()
    {
        delete [] _data;
    }

    size_t getRows()
    {
        return shape.rows;
    }

    size_t getColumns()
    {
        return shape.cols;
    }

    Column& operator[](const size_t i) const
    {
        if (i >= shape.cols) {
            throw std::out_of_range("out of range. Matrix:: index >= shape.cols");
        }

        return _data[i];
    }

    Matrix& operator*=(const int number)
    {
        for (size_t i = 0; i < shape.rows; ++i)
        {
            for (size_t j = 0; j < shape.cols; ++j)
            {
                _data[j][i] *= number;
            }
        }

        return *this;
    }

    bool operator==(const Matrix &other) const
    {
        if (shape != other.shape) {
            return false;
        }

        for (size_t i = 0; i < shape.rows; ++i)
        {
            for (size_t j = 0; j < shape.cols; ++j)
            {
                if ((*this)[j][i] != other[j][i]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix &other) const
    {
        return !(*this == other);
    }
};


#endif //MATRIX_MATRIX_H
