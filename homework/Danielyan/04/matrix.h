#include <iostream>
#include <vector>

class Matrix {
private:
    struct Proxy {
        Proxy(std::vector<int> *pVector) : data(pVector) {}

        Proxy(const std::vector<int> *pVector) : data(const_cast<decltype(data)>(pVector)) {}

        std::vector<int>* data;
        int& operator[](size_t index) {
            if (index >= data->size())
                throw std::out_of_range("");
            return (*data)[index];
        }

        const int& operator[](size_t index) const {
            if (index >= data->size())
                throw std::out_of_range("");
            return (*data)[index];
        }
    };

    std::vector<std::vector<int>> data_;
public:
    Matrix(int cols, int rows, int val = 0)
        : data_(cols, std::vector<int>(rows, val)) {}

    size_t getRows() const { return data_.empty() ? 0 : data_.back().size();}
    size_t getColumns() const { return data_.size(); }

    Matrix& operator *= (int mult) {
        for (auto& row : data_) {
            for (auto& element : row)
                element *= mult;
        }
        return *this;
    }

    bool operator == (const Matrix& other) const {
        return data_ == other.data_;
    }
    bool operator != (const Matrix& other) const {
        return !(*this == other);
    }

    const Proxy operator [] (size_t index) const {
        if (index >= data_.size())
            throw std::out_of_range("");
        return Proxy(&data_.at(index));
    };

    Proxy operator [] (size_t index) {
        if (index >= data_.size())
            throw std::out_of_range("");
        return Proxy(&data_.at(index));
    };
};

