#include <cstdlib>
#include <stdexcept>
//#include <iostream>

class Matrix {
    size_t rows_, cols_;
    int **data_;

    friend class Column;
    class Column {
        const Matrix* m1_;
        Matrix* m2_;
        size_t i_;
        Column(const Matrix& m, size_t i): m1_(&m), i_(i) {}
        Column(Matrix& m, size_t i): m2_(&m), i_(i) {}
        
        friend class Matrix;
    public:
        const int& operator[](size_t j) const {
            if (j >= m1_->rows_) {
                throw std::out_of_range("index j out of range");
            }
            return (*m1_).data_[i_][j];
        }
        int& operator[](size_t j) {
            if (j >= m2_->rows_) {
                throw std::out_of_range("index j out of range");
            }
            return (*m2_).data_[i_][j];
        }
        Column(const Column&) = default;
        Column& operator=(const Column&) = delete;
    };
public:
    Matrix(size_t cols, size_t rows): cols_(cols), rows_(rows) {
        if (rows_ == 0 || cols_ == 0) {
            data_ = nullptr;
        } else {
            int *data_int = new int[rows_*cols_];
            data_ = new int*[cols_];
            for (int i = 0; i < cols_; i++) {
                data_[i] = data_int + rows_ * i;
            }

            for (int i = 0; i < rows_; i++) {
                for (int j = 0; j < cols_; j++) {
                    data_[i][j] = 0;
                }
            }
        }
    }

    Matrix(const Matrix &other): cols_(other.cols_), rows_(other.rows_) {
        if (rows_ == 0 || cols_ == 0) {
            data_ = nullptr;
        } else {
            int *data_int = new int[rows_*cols_];
            data_ = new int*[cols_];
            for (int i = 0; i < cols_; i++) {
                data_[i] = data_int + rows_ * i;
            }

            for (int i = 0; i < cols_; i++) {
                for (int j = 0; j < rows_; j++) {
                    data_[i][j] = other.data_[i][j];
                }
            }
        }
    }

    Matrix& operator=(const Matrix& other) { /// \todo check a = a;
        if (this->data_ != nullptr) {
            delete[] *data_;
            delete[] data_;
        }
        cols_ = other.cols_;
        rows_ = other.rows_;
        if (rows_ == 0 || cols_ == 0) {
            data_ = nullptr;
        } else {
            int *data_int = new int[rows_*cols_];
            data_ = new int*[cols_];
            for (int i = 0; i < cols_; i++) {
                data_[i] = data_int + rows_ * i;
            }

            for (int i = 0; i < cols_; i++) {
                for (int j = 0; j < rows_; j++) {
                    data_[i][j] = other.data_[i][j];
                }
            }
        }
        return *this;
    }

    ~Matrix() {
        if (cols_ && rows_){
            delete[] *data_;
            delete[] data_;
        }
    }

    size_t getColumns() {
        return cols_;
    }

    size_t getRows() {
        return rows_;
    }

    bool operator==(const Matrix& other) const {
        if (cols_ != other.cols_) {
            return false;
        }
        if (rows_ != other.rows_) {
            return false;
        }
        for (int i = 0; i < cols_; i++) {
            for (int j = 0; j < rows_; j++) {
                if (data_[i][j] != other.data_[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    Matrix& operator*=(int c) {
        for (int i = 0; i < cols_; i++) {
            for (int j = 0; j < rows_; j++) {
                data_[i][j] *= c;
            }
        }
        return *this;
    }

    const Column operator[](size_t i) const {
        if (i >= cols_) {
            throw std::out_of_range("index i out of range");
        }
        return Column(*this, i);
    }

    Column operator[](size_t i) {
        if (i >= cols_) {
            throw std::out_of_range("index i out of range");
        }
        return Column(*this, i);
    }
};