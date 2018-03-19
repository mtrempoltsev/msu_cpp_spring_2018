#include <iostream>

class Matrix {
    class Row {
        int* row_;
        int columns_;

    public:
        Row(){};

        ~Row() { delete[] row_; }

        void allocate(size_t columns) {
            columns_ = columns;
            row_ = new int[columns_];
        }

        const int& operator[](size_t column) const {
            if (columns_ <= column) {
                throw std::out_of_range("matrix indexes is out of range");
            }
            return row_[column];
        }

        int& operator[](size_t column) {
            if (columns_ <= column) {
                throw std::out_of_range("matrix indexes is out of range");
            }
            return row_[column];
        }
    };

    size_t rows_;
    size_t columns_;
    Row* matrix_;

public:
    Matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns) {
        matrix_ = new Row[rows_];
        for (size_t it = 0; it < rows_; ++it) {
            matrix_[it].allocate(columns_);
        }
    }

    Matrix(const Matrix& other) : rows_(other.rows_), columns_(other.columns_) {
        matrix_ = new Row[rows_];
        for (size_t row = 0; row < rows_; ++row) {
            matrix_[row].allocate(columns_);
        }
        for (size_t row = 0; row < rows_; ++row) {
            for (size_t column = 0; column < columns_; ++column) {
                matrix_[row][column] = other.matrix_[row][column];
            }
        }
    }

    ~Matrix() { delete[] matrix_; }

    const Row& operator[](size_t row) const {
        if (rows_ <= row) {
            throw std::out_of_range("matrix indexes is out of range");
        }
        return matrix_[row];
    }

    Row& operator[](size_t row) {
        if (rows_ <= row) {
            throw std::out_of_range("matrix indexes is out of range");
        }
        return matrix_[row];
    }

    Matrix&& operator*=(int mult) {
        Matrix return_matrix(rows_, columns_);
        for (size_t row = 0; row < rows_; ++row) {
            for (size_t column = 0; column < columns_; ++column) {
                matrix_[row][column] *= mult;
                return_matrix.matrix_[row][column] = matrix_[row][column];
            }
        }
        return std::move(return_matrix);
    }

    bool operator==(const Matrix& other) const {
        if (rows_ != other.rows_ || columns_ != other.columns_) {
            return false;
        }

        for (size_t row = 0; row < rows_; ++row) {
            for (size_t column = 0; column < columns_; ++column) {
                if (matrix_[row][column] != other.matrix_[row][column]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix& other) const {
        if (rows_ != other.rows_ || columns_ != other.columns_) {
            return true;
        }

        for (size_t row = 0; row < rows_; ++row) {
            for (size_t column = 0; column < columns_; ++column) {
                if (matrix_[row][column] != other.matrix_[row][column]) {
                    return true;
                }
            }
        }

        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
        for (size_t row = 0; row < matrix.rows_; ++row) {
            for (size_t column = 0; column < matrix.columns_; ++column) {
                out << matrix[row][column] << " ";
            }
            out << "\n";
        }
        return out;
    }

    size_t getRows() { return columns_; }

    size_t getColumns() { return rows_; }
};