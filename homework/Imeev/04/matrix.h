class Matrix
{
public:
    class Proxy
    {
        size_t rows;
        size_t delta = 0;
        int *arr = nullptr;
    public:
        Proxy(size_t rows_ = 0): rows(rows_) {};
        Proxy &setProxy(size_t delta_, int *arr_);
        const int &operator[](size_t i) const;
        int &operator[](size_t i);
    };
    Matrix(size_t cols_ = 0, size_t rows_ = 0): cols(cols_), rows(rows_), len(rows_ * cols_)
    {
        proxy = new Proxy(rows);
        arr = new int [len];
    }
    ~Matrix() { delete proxy; delete[] arr; }

    size_t getColumns() const { return cols; }
    size_t getRows() const { return rows; }

    const Proxy &operator[](size_t i) const;
    Proxy &operator[](size_t i);
    Matrix &operator*=(int num);
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
private:
    size_t cols;
    size_t rows;
    size_t len;
    Proxy *proxy = nullptr;
    int *arr = nullptr;
};

Matrix::Proxy &Matrix::Proxy::setProxy(size_t delta_, int *arr_)
{
    delta = delta_;
    arr = arr_;
    return *this;
}

const int &Matrix::Proxy::operator[](size_t i) const
{
    if (i >= rows){
        throw std::out_of_range("Wrong row number");
    }
    return arr[delta + i];
}

int &Matrix::Proxy::operator[](size_t i)
{
    if (i >= rows){
        throw std::out_of_range("Wrong row number");
    }
    return arr[delta + i];
}

const Matrix::Proxy &Matrix::operator[](size_t i) const
{
    if (i >= cols) {
        throw std::out_of_range("Wrong column number");
    }
    return proxy->setProxy(rows * i, arr);
}

Matrix::Proxy &Matrix::operator[](size_t i)
{
    if (i >= cols) {
        throw std::out_of_range("Wrong column number");
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

bool Matrix::operator==(const Matrix &other) const
{
    if (this == &other) {
        return true;
    }
    if (len != other.len) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (arr[i] != other.arr[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other) const
{
    return !operator==(other);
}
