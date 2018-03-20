#pragma once
class Matrix
{
private:
    int* matrix = nullptr;
    size_t _rows = 0;
    size_t _columns = 0;
    class index
    {
    private:
        size_t _j = 0;
        const Matrix& _m;
    public:
        index(const Matrix& m, size_t j):
        _j(j),
        _m(m)
        {}

        int& operator[](size_t i)
        {
            if(i >= _m._rows)
                throw std::out_of_range("");
            return _m.matrix[i*_m._columns+_j];
        }

	const int& operator[](size_t i) const
        {
            if(i >= _m._rows)
                throw std::out_of_range("");
            return _m.matrix[i*_m._columns+_j];
        }

    };

public:
    Matrix(size_t columns, size_t rows):
    _rows(rows),
    _columns(columns)
    {
        matrix = new int[rows * columns];
    }

    ~Matrix()
    {
        delete[] matrix;
    }

    index operator[](size_t j)
    {
        if(j >= _columns)
            throw std::out_of_range("");
        return index(*this, j);
    }
    
    const index operator[](size_t j) const
    {
        if(j >= _columns)
            throw std::out_of_range("");
        return index(*this, j);
    }

    size_t getColumns() const
    {
        return _columns;
    }

    size_t getRows() const
    {
        return _rows;
    }

    bool operator==(const Matrix& other) const
    {
        if(_rows != other._rows && _columns != other._columns)
            return false;
        for(size_t i =0; i < _rows*_columns; i++)
            if(other.matrix[i] != matrix[i])
                return false;
        return true;
    }

    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }

    Matrix& operator*=(const int a)
    {
        for(size_t i = 0; i < _rows*_columns; i++)
            matrix[i] *= a;
        return *this;
    }
};
