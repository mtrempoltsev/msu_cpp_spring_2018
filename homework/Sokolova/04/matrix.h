#include <cstdlib>
#include <stdexcept>
//#include <iostream>

class Matrix {
    size_t rows_, cols_;
    int **data_;

    class Column;
    class Column {
        int *col_;
        size_t i_, len_;
        
    public:
        Column(int *col, size_t i, size_t len): col_(col), i_(i), len_(len) {}
        const int& operator[](int j) const{
            if (j >= len_) {
                throw std::out_of_range("index j out of range");
            }
            return col_[j];
        }
        int& operator[](int j) {
            if (j >= len_) {
                throw std::out_of_range("index j out of range");
            }
            return col_[j];
        }
        Column(const Column&) = default;
        Column& operator=(const Column&) = default;
        ~Column() = default;
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

    const size_t getColumns() const {
        return cols_;
    }

    const size_t getRows() const {
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

    const int& operator()(int i, int j) const {
        return data_[i][j];
    }

    int& operator()(int i, int j) {
        return data_[i][j];
    }

    const Column operator[](size_t i) const {
        if (i >= cols_) {
            throw std::out_of_range("index i out of range");
        }
        return Column(this->data_[i], i, rows_);
    }

    Column operator[](size_t i) {
        if (i >= cols_) {
            throw std::out_of_range("index i out of range");
        }
        return Column(this->data_[i], i, rows_);
    }
};