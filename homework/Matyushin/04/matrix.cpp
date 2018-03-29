#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

class Column {
private:
    int length;
    int* elems;
public:
    Column(int len):
        length(len){
        elems = (int*)malloc(length*sizeof(int));
        for (int t = 0; t < length; t++)
            elems[t] = 0;
    }
    
    int operator[](int i) const{
        if ((i < 0) || (i >= length))
            throw std::out_of_range("");
        return elems[i];
    }
    
    int& operator[](int i){
        if ((i < 0) || (i >= length))
            throw std::out_of_range("");
        return elems[i];
    }
    
    ~Column(){
        free(elems);
    }
};

class Matrix {
private:
    int rows_num;
    int cols_num;
    Column** elems;
public:
    Matrix(int cn, int rn):
        cols_num(cn),
        rows_num(rn){
        elems = (Column**)malloc(cols_num*sizeof(Column*));
        for (int t = 0; t < cols_num; t++){
            Column* newColumn = new Column(rows_num);
            elems[t] = newColumn;
        }
    }
    
    int getColumns(void) const{
        return cols_num;
    }
    
    int getRows(void) const{
        return rows_num;
    }
    
    const Column& operator[](int i) const{
        if ((i < 0) || (i >= cols_num))
            throw std::out_of_range("");
        return *elems[i];
    }
    
    Column& operator[](int i){
        if ((i < 0) || (i >= cols_num))
            throw std::out_of_range("");
        return *elems[i];
    }
    
    void operator*=(int scalar){
        for (int i = 0; i < cols_num; i++)
            for (int j = 0; j < rows_num; j++)
                (*this)[i][j] *= scalar;
    }
    
    bool operator==(const Matrix& other) const{
        if (this->getColumns() != other.getColumns())
            return false;
        if (this->getRows() != other.getRows())
            return false;
        for (int i = 0; i < cols_num; i++)
            for (int j = 0; j < rows_num; j++)
                if ((this->operator[](i))[j] != other[i][j])
                    return false;
        return true;
    }
    
    bool operator!=(const Matrix& other) const{
        return !(*this == other);
    }
    
    ~Matrix(){
        for (int t = 0; t < cols_num; t++)
            delete elems[t];
        free(elems);
    }
};
