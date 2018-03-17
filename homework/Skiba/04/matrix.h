class Matrix{
private:
    size_t rows, cols;
    int ** ptr;
    class Matrix_proxy{
        int *ptr;
        int rows;
    public:
        Matrix_proxy(int *_ptr, int _rows): ptr(_ptr), rows(_rows) {}
        ~Matrix_proxy() {}
        int& operator[](size_t ind) {
            if (ind >= rows) {
                throw std::out_of_range("");
            }
            return *(ptr + ind);
        }
    };
public:
    Matrix(size_t _cols, size_t _rows): cols(_cols), rows(_rows) {
        ptr = new int*[cols];
        for (size_t i = 0; i < cols; i++) {
            ptr[i] = new int[rows];
        }
    }
    ~Matrix() {
        for (size_t i = 0; i < cols; i++) {
            delete[] ptr[i];
        }
        delete[] ptr;
    }
    size_t getRows() const{
        return rows;
    }
    size_t getColumns() const{
        return cols;
    }
    Matrix_proxy operator[](size_t ind) {
        if (ind >= cols) {
            throw std::out_of_range("");
        }
        return Matrix_proxy(*(ptr + ind), rows);
    }
    Matrix& operator*=(int x) {
        for (size_t i = 0; i < cols; i++) {
            for (size_t j = 0; j < rows; j++) {
                *(*(ptr + i) + j) *= x;
            }
        }
        return *this;
    }
    bool operator==(const Matrix& mid) const{
        bool ans = true;
        if ((cols != mid.cols) || (rows != mid.rows)) {
            return false;
        }
        for (size_t i = 0; (i < cols) && ans; i++) {
            for (size_t j = 0; (j < rows) && ans; j++) {
                ans = *(*(ptr + i) + j) == *(*(mid.ptr + i) + j);
            }
        }
        return ans;
    }
    bool operator!=(const Matrix& mid) const{
        return !operator==(mid);
    }
};