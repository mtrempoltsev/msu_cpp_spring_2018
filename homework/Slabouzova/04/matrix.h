#include <iostream>
#include <vector>

class Matrix
{
    size_t n_cols;
    size_t n_rows;

    
    class vectorWrapper
    {
        std::vector<int> vector_;
    public:
        vectorWrapper(size_t n_rows): 
            vector_(n_rows)
        { }

        int& operator[](size_t i)
        {
            if (i >= vector_.size())
                throw std::out_of_range("");
            return vector_[i];
        }

        const int& operator[](size_t i) const 
        {
            if (i >= vector_.size())
                throw std::out_of_range("");
            return vector_[i];
        }
    };

    std::vector<vectorWrapper> data_;

public:
    Matrix(size_t n_cols, size_t n_rows) :
        n_cols(n_cols),
        n_rows(n_rows)
    { 
        for (int i = 0; i < n_cols; i++) {
            data_.push_back(vectorWrapper(n_rows));
        }
    }

    vectorWrapper& operator[](size_t i)
    {
        if (i >= n_cols)
            throw std::out_of_range("");    
        return data_[i];
    }

    const vectorWrapper& operator[](size_t i) const
    {
        if (i >= n_cols)
            throw std::out_of_range("");    
        return data_[i];
    }
    
    Matrix operator*=(int value)
    {
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                (*this)[j][i] *= value; 
            }
        }
        return *this;
    }       


    bool operator==(const Matrix& other) const
    {
        // check matrix shapes
        if (this->getColumns() != other.getColumns() or 
                    this->getRows() != other.getRows())
            return false;

        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                if (this->data_[j][i] != other.data_[j][i]) {
                    return false;
                }
            }
        }                
        return true;
    }
    
    bool operator!=(const Matrix& other) const
    {
        return not (*this == other);
    }

    size_t getColumns() const
    { 
        return n_cols; 
    }
    
    size_t getRows() const
    { 
        return n_rows;
    }
};
