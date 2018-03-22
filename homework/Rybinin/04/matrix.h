
class Array
{
    private:
        int *ptr;
        int ar_sz;
    public:
        Array();
        ~Array();
        SetSize(int);
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
        Matrix( Matrix &MatrixToCopy);
        ~Matrix();
        Array &operator[] (int );
        int getRows() const;
        int getColumns() const;
        Matrix &operator*= (int);
        bool operator== (const Matrix&) const;
        bool operator!= (const Matrix&) const;
        const Matrix &operator= (const Matrix& );
};

Array::Array()
{
    ar_sz = 1;
    ptr = new int[1];
}

Array::SetSize(int cols)
{
    if(cols < 0)
        throw std::out_of_range("");
    delete [] ptr;
    ar_sz = cols;
    ptr = new int[cols];
}

Array::~Array()
{
    delete [] ptr;
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
    ptr = new Array[rows];
    for(int i = 0; i < rows; ++i){
        ptr[i].SetSize(cols);
    }
}

Matrix::~Matrix()
{
    delete [] ptr;
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
            if(ptr[i][j] != right.ptr[i][j])
                return false;
    return true;
}

bool Matrix::operator!= (const Matrix &right) const
{
    return !(*this == right);
}

const Matrix &Matrix::operator= (const Matrix &right)
{
    if(this != &right){
        if(mRows != right.mRows || getColumns() != right.getColumns()){
            delete [] ptr;
            mRows = right.mRows;
            ptr = new Array[mRows];
            for(int i = 0; i < mRows; ++i){
                ptr[i].SetSize(right.getColumns());
            }
        for(int i = 0; i < mRows; ++i)
            for(int j = 0; j < getColumns(); ++j)
                ptr[i][j] = right.ptr[i][j];
        }
    }
    return *this;
}
