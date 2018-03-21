#include <iostream>

class Matrix {
   private:
    int **data;
    size_t rows;
    size_t cols;
    class Proxy {
       private:
        size_t rows;
        int *row_data;

       public:
        Proxy(size_t rows_, int *row_data_)
            : rows{rows_}, row_data{row_data_} {};

        const int operator[](size_t idx) const {
            if (idx >= rows)
                throw std::out_of_range(
                    "Index should be between 0 and rows size");
            return row_data[idx];
        }

        int &operator[](size_t idx) {
            if (idx >= rows)
                throw std::out_of_range(
                    "Index should be between 0 and rows size");
            return row_data[idx];
        }
    };

   public:
    Matrix(size_t cols_, size_t rows_) : cols{cols_}, rows{rows_} {
        data = new int *[cols];
        for (size_t i = 0; i < cols; i++) {
            data[i] = new int[rows];
            for (size_t j = 0; j < rows; j++) data[i][j] = 0;
        }
    }

    size_t getRows() { return rows; }
    size_t getColumns() { return cols; }

    Proxy operator[](size_t idx) {
        if (idx >= cols)
            throw std::out_of_range(
                "Index should be between 0 and columns size");
        return Proxy(rows, data[idx]);
    }

    const Proxy operator[](size_t idx) const {
        if (idx >= cols)
            throw std::out_of_range(
                "Index should be between 0 and columns size");
        return Proxy(rows, data[idx]);
    }

    Matrix &operator*=(int mult) {
        for (size_t i = 0; i < cols; i++)
            for (size_t j = 0; j < rows; j++) data[i][j] *= mult;
        return *this;
    }

    bool operator==(const Matrix &other) const {
        if (cols != other.cols || rows != other.rows) return false;
        for (size_t i = 0; i < cols; i++)
            for (size_t j = 0; j < rows; j++)
                if (data[i][j] != other[i][j]) return false;
        return true;
    }

    bool operator!=(const Matrix &other) const { return !(*this == other); }

    void print_matrix() {
        for (size_t i = 0; i < cols; i++) {
            for (size_t j = 0; j < rows; j++) std::cout << data[i][j] << " ";
            std::cout << std::endl;
        }
    }

    ~Matrix() {
        for (size_t i = 0; i < cols; i++) {
            delete[] data[i];
        }
        delete[] data;
    }
};
