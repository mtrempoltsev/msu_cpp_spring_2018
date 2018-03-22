
class Array
{
    private:
        int *ptr;
        int ar_sz;
    public:
        Array(int);
        ~Array();
        const int &operator[](int ) const;
        int &operator[] (int );
        int GetSize() const;
};

class Matrix
{
    private:
        Array *ptr;
        int mRows;
    public:
        Matrix(int, int );
        ~Matrix();
        const Array &operator[](int ) const;
        Array &operator[] (int );
        int getRows() const;
        int getColumns() const;
        Matrix &operator*= (int);
        bool operator== (const Matrix&) const;
        bool operator!= (const Matrix&) const;
        Matrix &operator= (const Matrix& );
};

Array::Array(int cols)
{
    ar_sz = cols;
    ptr = new int[cols];
}

Array::~Array()
{
    delete [] ptr;
}

const int &Array::operator[] (int i) const
{
    if(i < 0 || i >= ar_sz)
        throw std::out_of_range("");
    return ptr[i];
}

int &Array::operator[] (int i)
{
    if(i < 0 || i >= ar_sz)
        throw std::out_of_range("");
    return ptr[i];
}

int Array::GetSize() const
{
    return ar_sz;
}

Matrix::Matrix(int rows,int cols)
{
    if(rows < 0 || cols < 0)
        throw std::out_of_range("");
    mRows = rows;
    ptr = static_cast<Array*>(operator new[] (rows*sizeof(Array)));
    for (int i = 0; i < rows; ++i)
        new (ptr + i) Array(cols);
}

Matrix::~Matrix()
{
    for (int i = 0; i < mRows; i++){
        ptr[i].~Array();
    }
    operator delete[] (ptr);
}

const Array &Matrix::operator[] (int i) const
{
    if(i < 0 || i >= mRows)
        throw std::out_of_range("");
    return ptr[i];
}

Array &Matrix::operator[] (int i)
{
    if(i < 0 || i >= mRows)
        throw std::out_of_range("");
    return ptr[i];
}

int Matrix::getRows() const
{
    return mRows;
}

int Matrix::getColumns() const
{
    return ptr->GetSize();
}

Matrix &Matrix::operator*= (int a)
{
    for(int i = 0; i < mRows; ++i)
        for(int j = 0; j< getColumns(); ++j)
            ptr[i][j] *= a;
    return *this;
}

bool Matrix::operator== (const Matrix &right) const
{
    if(mRows != right.mRows || getColumns() != right.getColumns())
        return false;
    for(int i = 0; i < mRows; ++i)
        for(int j = 0; j < getColumns(); ++j)
            if(ptr[i][j] != right[i][j])
                return false;
    return true;
}

bool Matrix::operator!= (const Matrix &right) const
{
    return !(*this == right);
}

Matrix &Matrix::operator= (const Matrix &right)
{
    if(this != &right){
        if(mRows != right.mRows || getColumns() != right.getColumns()){
            for (int i = 0; i < mRows; i++){
                ptr[i].~Array();
            }
            operator delete[] (ptr);
            mRows = right.mRows;
            Array* Place = static_cast<Array*>(operator new[] (mRows*sizeof(Array)));
            for (int i = 0; i < mRows; ++i)
                new (Place + i) Array(right.getColumns());
            }
        for(int i = 0; i < mRows; ++i)
            for(int j = 0; j < getColumns(); ++j)
                (*this)[i][j] = right[i][j];
    }
    return *this;
}
