#include <cstdlib>
#include <stdint.h>
#include <stdexcept>
#include <cstring>
#include <memory>

class Matrix {
private:
    class Row {
    public:
        Row() {}

        Row(uint32_t columns) {
            _columns = columns;
            _data.reset(new int32_t[_columns]);
        }
        
        Row(const Row& other) {
            _columns = other._columns;
            _data.reset(new int32_t[_columns]);
            for (uint32_t i = 0; i < _columns; ++i) {
                _data[i] = other._data[i];
            }
        }

        void operator=(const Row& other) {
            _columns = other._columns;
            _data.reset(new int32_t[_columns]);
            for (uint32_t i = 0; i < _columns; ++i) {
                _data[i] = other._data[i];
            }
        }

        const int32_t& operator[](uint32_t i) const {
            if (i < _columns) {
                return _data[i];
            } else {
                throw std::out_of_range("");
            }
        }

        int32_t& operator[](uint32_t i) {
            if (i < _columns) {
                return _data.get()[i];
            } else {
                throw std::out_of_range("");
            }
        }

        bool operator!=(const Row& other) const {
            if (_columns != other._columns) {
                return true;
            }
            for (uint32_t i = 0; i < _columns; ++i) {
                if (_data[i] != other._data[i]) {
                    return true;
                }
            }
            return false;
        }

        bool operator==(const Row& other) const {
            return !((*this) != other);
        }

        Row operator*=(int32_t alpha) {
            for (uint32_t i = 0; i < _columns; ++i) {
                _data[i] *= alpha;
            }
            return *this;
        }

    private:
        uint32_t _columns;
        std::unique_ptr<int32_t[]> _data; 
    };

    uint32_t _columns;
    uint32_t _rows;
    std::unique_ptr<Row[]> _data;

public:
    Matrix(uint32_t rows, uint32_t columns) {
        _rows = rows;
        _columns = columns;
        _data.reset(new Row[_rows]);
        for (uint32_t i = 0; i < _rows; ++i) {
            _data[i] = Row(_columns);
        }
    }

    Matrix(const Matrix& other) {
        _rows = other._rows;
        _columns = other._columns;
        _data.reset(new Row[_rows]);
        for (uint32_t i = 0; i < _rows; ++i) {
            _data[i] = other._data[i];
        }
    }

    void operator=(const Matrix& other) {
        _rows = _rows;
        _columns = _columns;
        _data.reset(new Row[_rows]);
        for (uint32_t i = 0; i < _rows; ++i) {
            _data[i] = other._data[i];
        }
    }

    uint32_t getColumns() {
        return _rows;
    }

    uint32_t getRows() {
        return _columns;
    }

    const Row& operator[](uint32_t i) const {
        if (i < _rows) {
            return _data[i];
        } else {
            throw std::out_of_range("");
        }
    }

    Row& operator[](uint32_t i) {
        if (i < _rows) {
            return _data.get()[i];
        } else {
            throw std::out_of_range("");
        }
    }

    bool operator!=(const Matrix& other) const {
        if (_rows != other._rows) {
            return true;
        }
        for (uint32_t i = 0; i < _rows; ++i) {
            if (_data[i] != other._data[i]) {
                return true;
            }
        }
        return false;
    }

    bool operator==(const Matrix& other) const {
        return !((*this) != other);
    }

    Matrix operator*=(int32_t alpha) {
        for (uint32_t i = 0; i < _rows; ++i) {
            _data[i] *= alpha;
        }
        return Matrix(*this);
    }
};
