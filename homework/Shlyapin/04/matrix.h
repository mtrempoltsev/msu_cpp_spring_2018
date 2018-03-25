class Matrix
{
    class Row
    {
        int *els = nullptr;
        int len = 0;
    public:
        Row() {}
        Row(int m) : len(m), els(new int[m]) {}
        Row(Row& x) : len(x.len)
        {
            els = new int[len];
            for (int i = 0; i < len; ++i) {
                els[i] = x.els[i];
            }
        }
        Row operator= (Row&& x) {
            std::swap(els, x.els);
            len = x.len;
            return *this;
        }
        int operator[] (int i) const
        {
            if (i < 0 || i >= len) {
                throw std::out_of_range("");
            }
            return els[i];
        }
        int& operator[] (int i)
        {
            if (i < 0 || i >= len) {
                throw std::out_of_range("");
            }
            return els[i];
        }
        void operator*= (int x)
        {
            for (int i = 0; i < len; ++i) {
                els[i] *= x;
            }
        }
        bool operator== (const Row& x) const
        {
            for (int i = 0; i < len; ++i) {
                if (els[i] != x.els[i]) {
                    return false;
                }
            }
            return true;
        }
        bool operator!= (const Row& x) const
        {
            return !(*this == x);
        }
        ~Row()
        {
            if (els) {
                delete[] els;
            }
        }
    };
    int nrows = 0, ncols = 0;
    Row *rs = nullptr;
public:
    Matrix() {}
    Matrix(int rows, int cols) : ncols(cols), nrows(rows)
    {
        rs = new Row[nrows];
        for (int i = 0; i < nrows; ++i) {
            rs[i] = Row(ncols);
        }
    }
    int getRows() const
    {
        return ncols;
    }
    int getColumns() const
    {
        return nrows;
    }
    Row& operator[] (int i)
    {
        if (i < 0 || i >= nrows) {
            throw std::out_of_range("");
        }
        return rs[i];
    }
    Matrix& operator*= (int x)
    {
        for (int i = 0; i < nrows; ++i)
        {
            rs[i] *= x;
        }
        return *this;
    }
    bool operator== (const Matrix& z) const
    {
        if (ncols != z.ncols || nrows != z.nrows) {
            return false;
        }
        for (int i = 0; i < nrows; ++i) {
            if (rs[i] != z.rs[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator!= (const Matrix& z) const
    {
        return !(*this == z);
    }
    ~Matrix()
    {
        if (rs) {
            delete[] rs;
        }
    }
};
