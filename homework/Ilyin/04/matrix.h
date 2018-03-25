#ifndef MATRIX_H
#define MATRIX_H

#include <memory>

struct Row_proxy{
size_t rows;
std::unique_ptr<int []> storage;

Row_proxy(){
    rows = 0;
}

void * reset(size_t n){
        rows = n;
        storage.reset(new int [rows]);
}

int &operator [](size_t i){
    if (i >= rows){
        throw std::out_of_range("Out of range, rows");
    }
    return storage[i];
}

const int &operator [](size_t i) const{
    if (i >= rows){
        throw std::out_of_range("Out of range, rows");
    }
    return storage[i];
}
};

class Matrix{
private:
size_t rows;
size_t cols;
std::unique_ptr<Row_proxy []> data;

public:
Row_proxy & operator [](size_t i){
    if (i >= cols){
        throw std::out_of_range("Out of range, cols");
    }
    return data[i];
}

const Row_proxy & operator [](size_t i) const{
    if (i >= cols){
        throw std::out_of_range("Out of range, cols");
    }
    return data[i];
}

size_t getColumns() const{
    return cols;
}

size_t getRows() const{
    return rows;
}

Matrix(const size_t n, const size_t m){
    rows = m;
    cols = n;
    data.reset(new Row_proxy [cols]);
    for (size_t i = 0; i < cols; i++){
        data[i].reset(rows);
    }
}

Matrix & operator *=(const int &mult){
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < cols; j++){
            data[j][i] *= mult;
        }
    }
    return *this;
}

bool operator ==(const Matrix &a) const{
    if (rows != a.getRows() || cols != a.getColumns()){
        return false;
    }
    
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < cols; j++){
            if ( !(data[j][i] == a[j][i]) ){
                return false;
            }
        }
    }
    return true;
}

bool operator !=(const Matrix &a) const{
    return !(*this == a);
}

};

#endif
