#include <cstddef>

class Matrix
{
    size_t cols;
    size_t rows;
    int **m;

    class Row
    {
        int *row;
        size_t len;
    public:
        Row(int *r, size_t l) : row(r), len(l) {}
        int& operator[](const int j)
        {
            if(0 <= j && j < len)
                return row[j];
            else
                throw std::out_of_range("");
        }
    };

public:
    Matrix(size_t r, size_t c) : rows(r), cols(c)
    {
        m = new int*[rows];
        for(int i = 0; i < rows; ++i)
            m[i] = new int[cols];
    }

    size_t getColumns() const { return cols; }
    size_t getRows() const { return rows; }

    Row operator[](const int i)
    {
        if (0 <= i && i < rows)
            return Row(m[i], cols);
        else
            throw std::out_of_range("");
    }

    void operator*=(const double k)
    {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                m[i][j] *= k;

    }

    bool operator==(const Matrix& other) const
    {
        if (cols != other.cols || rows != other.rows)
            return false;

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (m[i][j] != other.m[i][j])
                    return false;
        return true;
    }

    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; ++i)
            delete[] m[i];
        delete[] m;
    }
};