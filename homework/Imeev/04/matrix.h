class Proxy
{
    int rows;
    int delta;
    int *arr;
public:
    Proxy(int rows_ = 0): rows(rows_) {};
    Proxy &setProxy(int delta_, int *arr_);
    int &operator[](int i);
};

class Matrix
{
    size_t cols;
    size_t rows;
    size_t len;
    Proxy *proxy;
    int *arr;
public:
    Matrix(size_t cols_ = 0, size_t rows_ = 0): cols(cols_), rows(rows_), len(rows_ * cols_)
    {
        proxy = new Proxy(rows);
        arr = new int [len];
    }
    ~Matrix() { delete proxy; delete[] arr; }

    const size_t getColumns(void) const { return cols; }
    const size_t getRows(void) const { return rows; }

    const Proxy &operator[](size_t i) const;
    Proxy &operator[](size_t i);
    Matrix &operator*=(int num);
    const bool operator==(const Matrix &other) const;
    const bool operator!=(const Matrix &other) const;
};

Proxy &Proxy::setProxy(int delta_, int *arr_)
{
    delta = delta_;
    arr = arr_;
    return *this;
}

int &Proxy::operator[](int i)
{
    if (i >= rows){
        throw std::out_of_range("cols err");
    }
    return arr[delta + i];
}


const Proxy &Matrix::operator[](size_t i) const
{
    if (i >= cols) {
        throw std::out_of_range("cols err");
    }
    return proxy->setProxy(rows * i, arr);
}

Proxy &Matrix::operator[](size_t i)
{
    if (i >= cols) {
        throw std::out_of_range("cols err");
    }
    return proxy->setProxy(rows * i, arr);
}

Matrix &Matrix::operator*= (int num)
{
    for (int i = 0; i < len; ++i) {
        arr[i] *= num;
    }
    return *this;
}

const bool Matrix::operator==(const Matrix &other) const
{
    if (this == &other) return true;
    for (int i = 0; i < len; ++i) {
        if (arr[i] != other.arr[i]) {
            return false;
        }
    }
    return true;
}

const bool Matrix::operator!=(const Matrix &other) const
{
    return !operator==(other);
}
