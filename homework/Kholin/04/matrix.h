#include <cstdlib>
#include <stdint.h>
#include <stdexcept>
#include <cstring>
#include <memory>

class Matrix {
private:
    class Row {
    public:
        void alloc(uint32_t columns) {
            _columns = columns;
            _data_ptr.reset(new int32_t[_columns]);
        }

        const int32_t& operator[](uint32_t i) const {
            if (0 <= i && i < _columns) {
                return _data_ptr.get()[i];
            } else {
                throw std::out_of_range("");
            }
        }

        int32_t& operator[](uint32_t i) {
            if (0 <= i && i < _columns) {
                return _data_ptr.get()[i];
            } else {
                throw std::out_of_range("");
            }
        }

        bool operator!=(const Row& other) const{
            if (_columns != other._columns) {
                return true;
            }
            int32_t* data = _data_ptr.get();
            int32_t* other_data = other._data_ptr.get();
            for (uint32_t i = 0; i < _columns; ++i) {
                if (data[i] != other_data[i]) {
                    return true;
                }
            }
            return false;
        }

        bool operator==(const Row& other) const{
            return !((*this) != other);
        }

        void operator*=(int32_t alpha) {
            int32_t* data = _data_ptr.get();
            for (uint32_t i = 0; i < _columns; ++i) {
                data[i] *= alpha;
            }
        }

    private:
        uint32_t _columns;
        std::unique_ptr<int32_t> _data_ptr; 
    };

    uint32_t _columns;
    uint32_t _rows;
    std::unique_ptr<Row> _data_ptr;

public:
    Matrix(uint32_t rows, uint32_t columns) {
        _rows = rows;
        _columns = columns;
        _data_ptr.reset(new Row[_rows]);
        Row* data = _data_ptr.get();
        for (uint32_t i = 0; i < _rows; ++i) {
            data[i].alloc(_columns);
        }
    }

    uint32_t getColumns() {
        return _rows;
    }

    uint32_t getRows() {
        return _columns;
    }

    const Row& operator[](uint32_t i) const {
        if (0 <= i && i < _rows) {
            return _data_ptr.get()[i];
        } else {
            throw std::out_of_range("");
        }
    }

    Row& operator[](uint32_t i) {
        if (0 <= i && i < _rows) {
            return _data_ptr.get()[i];
        } else {
            throw std::out_of_range("");
        }
    }

    bool operator!=(const Matrix& other) const{
        if (_rows != other._rows) {
            return true;
        }
        Row* data = _data_ptr.get();
        Row* other_data = other._data_ptr.get();
        for (uint32_t i = 0; i < _rows; ++i) {
            if (data[i] != other_data[i]) {
                return true;
            }
        }
        return false;
    }

    bool operator==(const Matrix& other) const{
        return !((*this) != other);
    }

    void operator*=(int32_t alpha) {
        Row* data = _data_ptr.get();
        for (uint32_t i = 0; i < _rows; ++i) {
            data[i] *= alpha;
        }
    }

    ~Matrix() {
        _data_ptr.release();
    }
};
