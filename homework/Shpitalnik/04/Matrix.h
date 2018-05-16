#include <memory>

class Col{
    int rows;
    std::unique_ptr<double[]> data;
public:
    Col(int r = 1);
    Col(const Col& c);
    double &operator[](int index);
    const double &operator[](int index) const;
    bool operator!= (const Col &c) const;
    Col& operator=(const Col& c);
    Col &operator*= (double x);

};


class Matrix{
    int rows, cols;
    std::unique_ptr<Col[]> data;
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
};


Col::Col(int r): rows(r), data(std::make_unique<double[]>(rows)) {}

Col::Col(const Col &c): rows(c.rows), data(std::make_unique<double[]>(rows)) {
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

bool Col::operator!=(const Col &c) const{
    for (int i=0; i<rows; i++)
        if (this->data[i] != c.data[i])
            return true;
    return false;
}


Col& Col::operator=(const Col &c) {
    rows = c.rows;
    data = std::make_unique<double[]>(rows);
    for(int i = 0;i<rows;i++)
        data[i] = c.data[i];
    return *this;
}



Matrix::Matrix(int c, int r): rows(r), cols(c), data(std::make_unique<Col[]>(c)){
    for(int i=0; i<cols; i++)
        data[i] = Col(rows);
}

Matrix::Matrix(const Matrix &m): rows(m.rows), cols(m.cols), data(std::make_unique<Col[]>(cols)) {
    for(int i=0; i<cols; i++) {
        data[i] = m.data[i];
    }
}

Col& Matrix::operator[](int index) {
    if (index >= cols)
        throw std::out_of_range("");
    return data[index];

}

const Col& Matrix::operator[](int index) const {
    if (index >= cols)
        throw std::out_of_range("");
    return  data[index];

}

Matrix &Matrix::operator*=(double x) {
    for (int i=0;i<cols;i++)
        data[i] *= x;
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

