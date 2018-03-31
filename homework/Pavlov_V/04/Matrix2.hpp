#include <iostream>
#include <vector>

class Matrix {
private:
    class Column {
    private:
        std::vector<int> row;
    public:
        Column(int n): row(n) {}
        int& operator [] (int index) {
            if (index < 0 || index >= row.size()) {
                throw std::out_of_range("");
            }
            return row[index];
        }
        const int& operator [] (int index) const {
            if (index < 0 || index >= row.size()) {
                throw std::out_of_range("");
            }
            return row[index];
        }
    };
    std::vector<Column> matrix;
    int countRows;
    int countColumns;
public:
    Matrix(int columns, int rows): matrix(columns, Column(rows)), countRows(rows), countColumns(columns) {};
    
    Column& operator [] (int index) {
        if (index < 0 || index >= matrix.size()) {
            throw std::out_of_range("");
        }
        return matrix[index];
    }
    
    const Column& operator [] (int index) const {
        if (index < 0 || index >= matrix.size()) {
            throw std::out_of_range("");
        }
        return matrix[index];
    }
    
    int getRows() const {
        return countRows;
    }
    
    int getColumns() const {
        return countColumns;
    }
    
    void operator *= (const int value) {
        for(int i = 0; i < countRows; ++i) {
            for(int j = 0; j < countColumns; ++j) {
                matrix[j][i] *= value;
            }
        }
    }
    
    bool operator != (const Matrix& m1) const {
        return !(*this == m1);
    }
    
    bool operator == (const Matrix& m1) const {
        if(countRows == m1.countRows && countColumns == m1.countColumns) {
            for(int i = 0; i < countRows; ++i) {
                for(int j = 0; j < countColumns; ++j) {
                    if(matrix[j][i] != m1.matrix[j][i]) return false;
                }
            }
            return true;
        }
        return false;
    }
};
