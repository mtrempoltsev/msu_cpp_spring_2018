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
        Proxy(std::vector<int> &_array);// : _array(&_array) { }
        int& operator [] (int index);/* {
            try {
                if(index > (*_array).size() - 1) {
                    throw std::out_of_range("");
                }
                return (*_array)[index];
            } catch(std::out_of_range &e) {
                std::cout << "Caught: " << e.what() << std::endl;
            }
            return (*_array)[index];
        }*/

    };
    
    Proxy operator [] (int index);
//    {
//        try {
//            if(index > countRows - 1) {
//                throw std::out_of_range("");
//            }
//            return Proxy(matrix[index]);
//        } catch(std::out_of_range &e) {
//            std::cout << "Caught: " << e.what() << std::endl;
//        }
//        return Proxy(matrix[index]);
//    }
};
