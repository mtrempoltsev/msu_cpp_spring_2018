#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <iostream>
class Matrix
{
    int** matr;
    int cols;
    int rows;

public:
    class Array
    {
        int* a;
        int size;

    public:
        Array(int* a, int size)
        {
            this->a = a;
            this->size = size;
        }

        int& operator[](int j){
            if(j < size){
                return a[j];
            }
            else
                throw std::out_of_range("");
        }
    };

    Matrix(int col, int row)
    {
        cols = col;
        rows = row;
        matr = new int* [cols];
        for(int i=0; i<cols; i++)
        {
            matr[i] = new int [rows];
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

    Array operator[](int i)
    {
        if(i<cols){
            return Array(matr[i], rows);
        }
        else
            throw std::out_of_range("");
    }

    void operator *= (int a)
    {
        for(int i=0; i<cols; i++)
            for(int j=0; j<rows; j++)
                matr[i][j] *= a;
    }

    bool operator == (const Matrix& other) const
    {
        if(cols != other.cols && rows != other.rows)
            return false;

        for(int i=0; i<cols; i++)
            for(int j=0; j<rows; j++)
            {
                if (matr[i][j]!=other.matr[i][j])
                    return false;
            }
        return true;
    }

    bool operator != (const Matrix& other) const
    {
        return !(*this==other);
    }

    ~Matrix()
    {
        for(int i=0; i<cols; i++){
            delete[]matr[i];
        }
        delete[] matr;
    }
};

#endif // MATRIX_H_INCLUDED
