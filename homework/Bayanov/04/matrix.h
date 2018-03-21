#include <iostream>
#include <vector>

class Matrix {
    class Column {
        std::vector<int> column_;
        size_t rows_;

    public:
        Column(size_t rows) : rows_(rows), column_(rows){};

        ~Column() {}

        const int& operator[](size_t row) const {
            if (rows_ <= row) {
                throw std::out_of_range("matrix indexes is out of range");
            }
            return column_[row];
        }

        int& operator[](size_t row) {
            if (rows_ <= row) {
                // std::cout << row <<  " there\n";
                throw std::out_of_range("matrix indexes is out of range");
            }
            return column_[row];
        }
    };

    size_t rows_;
    size_t columns_;
    std::vector<Column> matrix_;

public:
    Matrix(size_t columns, size_t rows)
            : columns_(columns), rows_(rows), matrix_(columns, rows) {}

    Matrix(const Matrix& other) : columns_(other.columns_), rows_(other.rows_) {
        for (size_t column = 0; column < columns_; ++column) {
            for (size_t row = 0; row < rows_; ++row) {
                matrix_[column][row] = other.matrix_[column][row];
            }
        }
    }

    ~Matrix() {}

    const Column& operator[](size_t column) const {
        if (columns_ <= column) {
            throw std::out_of_range("matrix indexes is out of range");
        }
        return matrix_[column];
    }

    Column& operator[](size_t column) {
        if (columns_ <= column) {
            throw std::out_of_range("matrix indexes is out of range");
        }
        return matrix_[column];
    }

    Matrix& operator*=(int mult) {
        for (size_t column = 0; column < columns_; ++column) {
            for (size_t row = 0; row < rows_; ++row) {
                matrix_[column][row] *= mult;
            }
        }
        return *this;
    }

    bool operator==(const Matrix& other) const {
        if (rows_ != other.rows_ || columns_ != other.columns_) {
            return false;
        }

        for (size_t column = 0; column < columns_; ++column) {
            for (size_t row = 0; row < rows_; ++row) {
                if (matrix_[column][row] != other.matrix_[column][row]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
        for (size_t column = 0; column < matrix.columns_; ++column) {
            for (size_t row = 0; row < matrix.rows_; ++row) {
                out << matrix[column][row] << " ";
            }
            out << "\n";
        }
        return out;
    }

    size_t getRows() { return rows_; }

    size_t getColumns() { return columns_; }
};