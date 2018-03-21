#pragma once

#include <stdexcept>
#include <iostream>
#include <vector>

class Matrix
{
private:
    std::vector< std::vector<int> > matrix;
    std::vector<int> zerov;

    class ProxyMatrix
    {
    private:
        size_t len;
        std::vector<int> rm;

    public:
        ProxyMatrix(std::vector<int> r, size_t l) : rm(r), len(l) {}

        const int operator[](const int rown) const
        {
            if(rown < 0 || rown >= len)
                throw std::out_of_range("");
            else
                return rm[rown];
        }

        int& operator[](const int rown)
        {
            if(rown < 0 || rown >= len)
                throw std::out_of_range("");
            else
                return rm[rown];
        }
    };

public:
    Matrix(const size_t cols, const size_t rows)
    {
        zerov.push_back(0);
        matrix.resize(cols, zerov);
        for(int i = 0; i < cols; i++)
            matrix[i].resize(rows, 0);
    }

    size_t getColumns(void) const
    {
        return matrix.size();
    }

    size_t getRows(void) const
    {
        return matrix[0].size();
    }

    Matrix operator*=(const int mult)
    {
        for(int i = 0; i < this->getRows(); i++)
        {
            for(int j = 0; j < this->getColumns(); j++)
                this->matrix[j][i] = this->matrix[j][i] * 2;
        }
        return *this;
    }

    bool operator==(const Matrix &other) const
    {
        if(this->getColumns() == other.getColumns() && this->getRows() == other.getRows())
        {
            for(int i = 0; i < this->getRows(); i++)
            {
                for(int j = 0; j < this->getColumns(); j++)
                    if(this->matrix[j][i] != other.matrix[j][i])
                        return false;
            }
        }
        else
            return false;
        return true;
    }

    bool operator!=(const Matrix &other) const
    {
        return !(*this == other);
    }

    const ProxyMatrix operator[](int i) const
    {
        if(i >= this->getColumns() || i < 0)
            throw std::out_of_range("");
        return ProxyMatrix(matrix[i], this->getColumns());
    }

    ProxyMatrix operator[](int i)
    {
        if(i >= this->getColumns() || i < 0)
            throw std::out_of_range("");
        return ProxyMatrix(matrix[i], this->getColumns());
    }
};
