#pragma once

class Matrix
{
private:
    size_t cols = 0, rows = 0;
    int *data = nullptr;

    class Proxy
    {
    public:
        Proxy(int *off_, size_t rows_)
                : off(off_), rows(rows_)
        {
        }

        int &operator[] (size_t row)
        {
            if (row >= rows) {
                throw std::out_of_range("row number should be between 0 and number of rows");
            }
            return off[row];
        }

        int operator[] (size_t row) const
        {
            if (row >= rows) {
                throw std::out_of_range("row number should be between 0 and number of rows");
            }
            return off[row];
        }

    private:
        int *off;
        size_t rows;
    };

public:
    Matrix(size_t cols_, size_t rows_)
            : cols(cols_), rows(rows_)
    {
        if (cols > 0 && rows > 0) {
            data = new int[cols * rows]();
        }
    }

    auto getRows() const
    {
        return rows;
    }

    auto getColumns() const
    {
        return cols;
    }

    Proxy operator [] (size_t col)
    {
        if (col >= cols) {
            throw std::out_of_range("column number should be between 0 and number of columns");
        }
        return Proxy(data + col * rows, rows);
    }

    const Proxy operator [] (size_t col) const
    {
        if (col >= cols) {
            throw std::out_of_range("column number should be between 0 and number of columns");
        }
        return Proxy(data + col * rows, rows);
    }

    Matrix &operator *= (int k)
    {
        for (size_t i = 0; i < cols * rows; ++i) {
            data[i] *= k;
        }
        return *this;
    }

    bool operator == (const Matrix &m) const
    {
        if (cols != m.cols || rows != m.rows) {
            return false;
        }

        for (size_t i = 0; i < cols * rows; ++i) {
            if (data[i] != m.data[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator != (const Matrix &m) const
    {
        return !(*this == m);
    }

    ~Matrix()
    {
        delete[] data;
    }
};
