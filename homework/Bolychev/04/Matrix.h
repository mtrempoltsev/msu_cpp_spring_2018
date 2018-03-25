#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <stdexcept>
#include <new>

class Shape
{
public:
    size_t rows;
    size_t cols;

    Shape() {
        rows = cols = 0;
    }


    Shape(size_t n_cols, size_t n_rows) {
        rows = n_rows;
        cols = n_cols;
    }

    bool operator==(const Shape& other) const {
        return other.cols == cols && other.rows == rows;
    }

    bool operator!=(const Shape& other) const {
        return  other.cols != cols || other.rows != rows;
    }
};

class Matrix {
private:
    class Column { //Proxy
        int* data = nullptr;
        size_t rows;
    public:
        Column() : rows(0) {
            data = nullptr;
        }

        Column(const size_t rows) : rows(rows) {
            data = new int[rows];
        }

        ~Column() {
            delete[] data;
        }

        const size_t getRows() const {
            return rows;
        }

        const int& operator[](const size_t i) const
        {
            if (i >= rows) {
                throw std::out_of_range("Matrix::coloumn: index is out of range");
            }

            return data[i];
        }

        int& operator[](const size_t i)
        {
            if (i >= rows) {
                throw std::out_of_range("Matrix::coloumn: index is out of range");
            }

            return data[i];
        }

        bool operator==(const Column &other) const
        {
            if (rows != other.getRows()) {
                return false;
            }

            for (size_t i = 0; i < rows; ++i) {
                if (data[i] != other.data[i]) {
                    return false;
                }
            }

            return true;
        }

        bool operator!=(const Column &other) const
        {
            return !(other == *this);
        }
    };

    Column* data;
    Shape shape;
public:
    Matrix(const size_t n_cols, const size_t n_rows) : shape(n_cols, n_rows)
    {
        // Выделяем память
        data = static_cast<Column*>(operator new[] (n_cols * sizeof(Column)));

        // Создаем столбцы с помощью конструктура Column
        for (size_t i = 0; i < n_cols; i++) {
            new (data + i)Column(n_rows);
        }
    }

    ~Matrix()
    {
        for (size_t i = 0; i < shape.cols; ++i) {
            data[i].~Column();
        }

        operator delete[] (data);
    }

    size_t getRows()
    {
        return shape.rows;
    }

    size_t getColumns()
    {
        return shape.cols;
    }

    const Column& operator[](const size_t i) const
    {
        if (i >= shape.cols) {
            throw std::out_of_range("Matrix:: index >= shape.cols");
        }

        return data[i];
    }

    Column& operator[](const size_t i)
    {
        if (i >= shape.cols) {
            throw std::out_of_range("Matrix:: index >= shape.cols");
        }

        return data[i];
    }

    Matrix& operator*=(const int number)
    {
        for (size_t i = 0; i < shape.cols; ++i)
        {
            for (size_t j = 0; j < shape.rows; ++j)
            {
                data[i][j] *= number;
            }
        }

        return *this;
    }

    bool operator==(const Matrix &other) const
    {
        if (shape != other.shape) {
            return false;
        }

        for (size_t i = 0; i < shape.cols; ++i) {
            if (other[i] != (*this)[i]) {
                return false;
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
