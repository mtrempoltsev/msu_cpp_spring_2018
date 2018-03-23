#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <stdexcept>
#include <vector>

class Matrix
{
private:
    class Column
    {
    private:
        std::vector<int> data;
    public:
        Column(size_t rows): data(rows) {}

        int& operator[](size_t i) {
            if (i < data.size())
                return data[i];
            throw std::out_of_range("");
        }
        
        const int& operator[](size_t i) const {
            if (i < data.size())
                return data[i];
            throw std::out_of_range("");
        }
        
        Column& operator*=(int number) {
            for (size_t i = 0; i < data.size(); i++)
                data[i] *= number;
            return *this;
        }
        
        bool operator==(const Column& other) const {
            return data == other.data;
        }
        
        bool operator!=(const Column& other) const {
            return data != other.data;
        }
    };
    
    const size_t rows, cols;
    std::vector<Column> data;
public:
    Matrix(size_t cols, size_t rows): rows(rows), cols(cols), data(cols, rows) {}
    
    Column& operator[](size_t i) {
        if (i < data.size())
            return data[i];
        throw std::out_of_range("");
    }
    
    const Column& operator[](size_t i) const {
        if (i < data.size())
            return data[i];
        throw std::out_of_range("");
    }
    
    Matrix& operator*=(int number) {
        for (size_t i = 0; i < data.size(); i++)
            data[i] *= number;
        return *this;
    }
    
    bool operator==(const Matrix& other) const {
        return data == other.data;
    }
    
    bool operator!=(const Matrix& other) const {
        return data != other.data;
    }

    size_t getRows() const {
        return rows;
    }
    
    size_t getColumns() const {
        return cols;
    }
};

#endif
