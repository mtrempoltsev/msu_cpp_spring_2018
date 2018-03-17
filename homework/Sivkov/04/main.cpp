#include <iostream>

class Matrix {
public:
    class Vector {
    public:
        explicit Vector(size_t size) : size(size) {
            data = new int(size);
            for (size_t i = 0; i < size; ++i)
                data[i] = 1;
        }

        size_t GetSize() const {
            return size;
        }

        const int &operator[](size_t index) const {
            if (index < 0 || index >= size)
                throw std::out_of_range("");
            return data[index];
        }

        int &operator[](size_t index) {
            if (index < 0 || index >= size)
                throw std::out_of_range("");
            return data[index];
        }

        bool operator==(const Vector &other) const {
            if (other.GetSize() != size)
                return false;
            bool flag = true;
            for (size_t i = 0; i < size; ++i)
                if (data[i] != other[i])
                    flag = false;
            return flag;
        }

        bool operator!=(const Vector &other) const {
            return !((*this) == other);
        }

        Vector &operator*=(int factor) {
            for (size_t i = 0; i < size; ++i)
                data[i] *= factor;
            return *this;
        }

        ~Vector() {
            delete[] data;
        }

    private:
        int *data;
        size_t size;
    };

    Matrix(size_t cols, size_t rows) : cols(cols), rows(rows) {
        data = static_cast<Vector *>(operator new[](cols * sizeof(Vector)));
        for (size_t i = 0; i < cols; ++i) {
            new(data + i) Vector(rows);
        }
    }

    const Vector &operator[](size_t index) const {
        if (index < 0 || index >= cols)
            throw std::out_of_range("");
        return data[index];
    }

    Vector &operator[](size_t index) {
        if (index < 0 || index >= cols)
            throw std::out_of_range("");
        return data[index];
    }

    bool operator==(const Matrix &other) const {
        if (other.getColumns() != cols || other.getRows() != rows)
            return false;
        bool flag = true;
        for (size_t i = 0; i < cols; ++i)
            if (data[i] != other[i])
                flag = false;
        return flag;
    }

    bool operator!=(const Matrix &other) const {
        return !((*this) == other);
    }

    Matrix &operator*=(int factor) {
        for (size_t i = 0; i < cols; ++i)
            data[i] *= factor;
        return *this;
    }

    size_t getRows() const {
        return rows;
    }

    size_t getColumns() const {
        return cols;
    }
    
    ~Matrix() {
        delete[] data;
    }

private:
    Vector *data;
    size_t cols;
    size_t rows;
};
