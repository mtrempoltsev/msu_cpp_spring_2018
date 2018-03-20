class Matrix
{
public:
    class Proxy
    {
        size_t rows;
        int *arr = nullptr;
    public:
        Proxy(size_t rows_ = 0, int *arr_ = nullptr): rows(rows_), arr(arr_) {};
        const int &operator[](size_t i) const;
        int &operator[](size_t i);
    };
    Matrix(size_t cols_ = 0, size_t rows_ = 0): cols(cols_), rows(rows_), len(rows_ * cols_)
    {
        arr = new int [len];
    }
    ~Matrix() { delete[] arr; }

    size_t getColumns() const { return cols; }
    size_t getRows() const { return rows; }

    const Proxy operator[](size_t i) const;
    Proxy operator[](size_t i);
    Matrix &operator*=(int num);
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
private:
    size_t cols;
    size_t rows;
    size_t len;
    int *arr = nullptr;
};

const int &Matrix::Proxy::operator[](size_t i) const
{
    if (i >= rows){
        throw std::out_of_range("Wrong row number");
    }
    return arr[i];
}

int &Matrix::Proxy::operator[](size_t i)
{
    if (i >= rows){
        throw std::out_of_range("Wrong row number");
    }
    return arr[i];
}

const Matrix::Proxy Matrix::operator[](size_t i) const
{
    if (i >= cols) {
        throw std::out_of_range("Wrong column number");
    }
    return Proxy(rows, arr + rows * i);
}

Matrix::Proxy Matrix::operator[](size_t i)
{
    if (i >= cols) {
        throw std::out_of_range("Wrong column number");
    }
    return Proxy(rows, arr + rows * i);
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
