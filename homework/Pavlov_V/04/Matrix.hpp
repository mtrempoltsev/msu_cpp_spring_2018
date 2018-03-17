#include <iostream>
#include <vector>

class Matrix {
private:
    int countRows;
    int countColunmns;
    std::vector<std::vector<int>> matrix;
public:
    Matrix(int, int);
    int getRows() const;
    int getColumns() const;
    void print() const;
    void operator *= (const int);
    bool operator == (const Matrix&) const;
    bool operator != (const Matrix&) const;
    
    class Proxy {
    private:
        std::vector<int>* _array;
    public:
        Proxy(std::vector<int> &_array);
        int& operator [] (int index);
    };
    Proxy operator [] (int index);
};
