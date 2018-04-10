#pragma once

#include <stdexcept>
#include <vector>

class Matrix{
private:    
    class Col
    {
    public:
        int* col;
        int sizeCol;
        Col(int sizeCol_):sizeCol(sizeCol_){
            col = new int[sizeCol]();  
        }
            
        int& operator[](size_t i){
            if(i >= sizeCol) throw std::out_of_range("");
            return col[i];
        }
        
        ~Col(){
            delete[] col;
        }
    };
       
public:

    Matrix(int sizeCols_, int sizeRows_):sizeRows(sizeRows_), sizeCols(sizeCols_){
        for(int i = 0; i < sizeCols_; i++){
            cols.push_back(Col(sizeRows_)); 
        }
    }
    
    Col& operator[](size_t i){
        if(i >= sizeCols) throw std::out_of_range("");
        return cols[i];
    }
    Matrix& operator*=(int v){
        for(int i = 0; i < sizeCols; i++){
            for(int j = 0; j < sizeRows; j++){
                (*this)[i][j] *= v;
            }
        }
        return *this;
    }
    bool operator==(Matrix const & matrix) const{
        if(sizeRows != matrix.sizeRows || sizeCols != matrix.sizeCols) return false;
        for(int i = 0; i < sizeCols; i++){
            for(int j = 0; j < sizeRows; j++){
                if(cols[i][j] != matrix.cols[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(Matrix const & matrix) const{
        return !(*this == matrix);
    }
    int getRows() const{
        return sizeRows;
    }
    int getColumns() const{
        return sizeCols;
    }

    ~Matrix(){
    }
private:
    std::vector<Col> cols;
    int sizeRows;
    int sizeCols;
};
