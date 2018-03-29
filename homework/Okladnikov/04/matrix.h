//
//  matrix.h
//  HW-4-C++
//
//  Created by Сергей Окладников on 22/03/2018.
//  Copyright © 2018 Сергей Окладников. All rights reserved.
//

#ifndef matrix_h
#define matrix_h


class Matrix
{
private:
    size_t cols, rows;
    int** data;
public:
    class line
    {
    private:
        size_t len;
        int* data;
    public:
        line (int* _data, size_t _len) : data(_data), len(_len) {}
        int & operator [] (size_t i)
        {
            if (i < len) {
                return data[i];
            } else {
                throw std::out_of_range("out of range");
            }
        }
        const int & operator [] (size_t i) const
        {
            if (i < len) {
                return data[i];
            } else {
                throw std::out_of_range("out of range");
            }
        }
    };
    
    Matrix(size_t _cols, size_t _rows)
    {
        cols = _cols;
        rows = _rows;
        data = new int* [cols];
        for (int i = 0; i < cols; i++) {
            data[i] = new int[rows];
        }
    }
    
    ~Matrix()
    {
        for (int i = 0; i < cols; i++)
            delete [] data[i];
        delete [] data;
    }
    
    line operator [] (size_t i)
    {
        if (i < cols) {
            return line(data[i], rows);
        } else {
            throw std::out_of_range("out of range");
        }
    }
    
    const line operator [] (size_t i) const
    {
        if (i < cols) {
            return line(data[i], rows);
        } else {
            throw std::out_of_range("out of range");
        }
    }
    
    Matrix & operator *= (int x)
    {
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                data[i][j] *= x;
            }
        }
        return *this;
    }
    
    bool operator == (const Matrix & other) const
    {
        if (cols != other.cols || rows != other.rows)
            return false;
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                if (data[i][j] != other.data[i][j])
                    return false;
            }
        }
        return true;
    }
    
    bool operator != (const Matrix & other) const
    {
        return !(*this == other);
    }
    
    const std::size_t getRows() const
    {
        return rows;
    }
    const std::size_t getColumns() const
    {
        return cols;
    }
};


#endif /* matrix_h */
