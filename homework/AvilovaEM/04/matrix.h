#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>

class Matrix
{
    private:
       size_t cols;
       size_t rows;
       size_t len;
       int *matrix = nullptr;
 
    public:   
        class Rows
        {
            private:
                size_t rows;
                int *matrix = nullptr;
        	
	        public:
                Rows(size_t rows_ = 0, int *matrix_ = nullptr): rows(rows_), matrix(matrix_) 
                {};
                const int &operator[](size_t i) const
                {
                    if (i >= rows)
                        throw std::out_of_range("");
                    return matrix[i];
                }
                int &operator[](size_t i)
                {
                    if (i >= rows)
                        throw std::out_of_range("");
                    return matrix[i];
                }
        };

        Matrix(size_t cols_ = 0, size_t rows_ = 0): cols(cols_), rows(rows_), len(rows_ * cols_)
        {
            matrix = new int [len];
        }
        ~Matrix() 
        { 
            delete[] matrix; 
        }
        size_t getColumns() const 
        {   
            return cols; 
        }
        size_t getRows() const 
        { 
            return rows; 
        }
        const Rows operator[](size_t i) const
        {
            if (i >= cols)
                throw std::out_of_range("");
            return Rows(rows, matrix + rows * i);
        }
        Rows operator[](size_t i)
        {
            if (i >= cols) 
                throw std::out_of_range("");
            return Rows(rows, matrix + rows * i);  
        }
        Matrix &operator*=(int num)
        {
            for (size_t i = 0; i < len; ++i)
                matrix[i] *= num;
            return *this;
        }
        bool operator==(const Matrix &other) const
        {
            if (this == &other)
                return true;
            if (len != other.len)
                return false;
            for (size_t i = 0; i < len; ++i) 
                if (matrix[i] != other.matrix[i])
                    return false;
            return true;
        }
        bool operator!=(const Matrix &other) const
        {
            return !operator==(other);
        }
};

#endif
