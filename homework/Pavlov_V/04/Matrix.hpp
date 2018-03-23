#include <iostream>
#include <vector>

class Matrix {
private:
    int countRows;
    int countColunmns;
    std::vector<std::vector<int>> matrix;
    
    class Proxy {
    private:
        std::vector<int>* _array;
    public:
        Proxy(std::vector<int>* vector_ptr);
        
        void set(const std::vector<int>* vector_ptr);
        int& operator [] (int index);
        const int& operator [] (int index) const;
    };
    mutable Proxy ptr;
public:
    Matrix(int, int);
    int getRows() const;
    int getColumns() const;
    void print() const;
    void operator *= (const int);
    bool operator == (const Matrix&) const;
    bool operator != (const Matrix&) const;
    
    
    
    Proxy operator [] (int index);
    const Proxy operator [] (int index) const;
};
