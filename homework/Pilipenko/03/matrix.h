#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
private:
    class Proxy {
    private:
        std::vector<int> data;
    public:
        Proxy(size_t cols) : data(cols) {}

        int& operator[](size_t i) {
            if (i < data.size())
                return data[i];
            throw std::out_of_range("");
        }
        
        int operator[](size_t i) const {
            if (i < data.size())
                return data[i];
            throw std::out_of_range("");
        }

        bool operator==(const Proxy &other) const {
            return data == other.data;
        }

        bool operator!=(const Proxy &other) const {
            return data != other.data;
        }

        Proxy &operator*=(int multiplier) {
            for (size_t i = 0; i < data.size(); i++)
                data[i] *= multiplier;
            return *this;
        }
    };

    const size_t rows, cols;
    std::vector<Proxy> data;
public:
    Matrix(size_t cols, size_t rows) : rows(rows), cols(cols), data(cols, rows) {}

    Proxy& operator[](size_t i) {
        if (i < data.size())
            return data[i];
        throw std::out_of_range("");
    }
    
    Proxy operator[](size_t i) const {
        if (i < data.size())
            return data[i];
        throw std::out_of_range("");
    }

    bool operator==(const Matrix &other) const {
        return data == other.data;
    }

    bool operator!=(const Matrix &other) const {
        return data != other.data;
    }

    Matrix &operator*=(int multiplier) {
        for (size_t i = 0; i < data.size(); i++)
            data[i] *= multiplier;
        return *this;
    }

    size_t getRows() const {
        return rows;
    }

    size_t getColumns() const {
        return cols;
    }
};

#endif
