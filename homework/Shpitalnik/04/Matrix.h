class Col{
    int rows;
    double *data;
public:
    Col(int r);
    Col(const Col& c);
    double &operator[](int index);
    const double &operator[](int index) const;
    bool operator== (const Col &h) const;
    Col &operator*= (double x);
    ~Col();

};


class Matrix{
    int rows, cols;
    Col **data;
public:
    Matrix(int c, int r);
    Matrix(const Matrix& m);
    int getColumns() const;
    int getRows() const;
    Col &operator[](int index);
    const Col &operator[](int index) const;
    bool operator== (const Matrix &m) const;
    bool operator!= (const Matrix &m) const;
    Matrix &operator*= (double x);
    ~Matrix();
};


Col::Col(int r): rows(r) {
    data = new double[r];
}

Col::Col(const Col &c): rows(c.rows) {
    data = new double[rows];
    for (int i =0; i<rows; i++)
        data[i] = c.data[i];
}

double& Col::operator[](int index) {
    if (index>=rows)
        throw std::out_of_range("");
    return data[index];
}

const double& Col::operator[](int index) const {
    if (index>=rows)
        throw std::out_of_range("");
    return data[index];
}


Col &Col::operator*=(double x) {
    for (int i=0;i<rows;i++)
        data[i] *= x;
    return *this;
}

bool Col::operator==(const Col &h) const{
    for (int i=0; i<rows; i++)
        if (this->data[i] != h.data[i])
            return false;
    return true;
}

Col::~Col() {
    delete[] data;
}


Matrix::Matrix(int c, int r): rows(r), cols(c){
    data = new Col* [cols];
    for(int i=0; i<cols; i++)
        data[i] = new Col(rows);
}

Matrix::Matrix(const Matrix &m): rows(m.rows), cols(m.cols) {
    data = new Col* [cols];
    for(int i=0; i<cols; i++) {
        data[i] = new Col(rows);
        data[i] = m.data[i];
    }
}

Col& Matrix::operator[](int index) {
    if (index >= cols)
        throw std::out_of_range("");
    return *(data[index]);

}

const Col& Matrix::operator[](int index) const {
    if (index >= cols)
        throw std::out_of_range("");
    return *(data[index]);

}

Matrix &Matrix::operator*=(double x) {
    for (int i=0;i<cols;i++)
        *(data[i]) *= x;
    return *this;
}

bool Matrix::operator==(const Matrix &m) const {
    if (rows != m.rows || cols != m.cols)
        return false;
    for(int i=0; i<cols;i++)
        if (this->data[i] != m.data[i])
            return false;
    return true;
}

int Matrix::getColumns() const {
    return cols;
}

int Matrix::getRows() const {
    return rows;
}

bool Matrix::operator!=(const Matrix &m) const {
    return !(*this == m);
}

Matrix::~Matrix() {
    for(int i=0; i<cols; i++)
        delete data[i];
    delete[] data;
}
