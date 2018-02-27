#include <cstdlib>
#include <ctime>

class Matrix {
public:
    Matrix();
    Matrix(int nOfrows, int nOfcols);
    ~Matrix();
    
    int SumByRows();
    int SumByCols();

private:
    int Nrows, Ncols;
    int **data;

    Matrix(const Matrix &) = delete;
    void operator=( const Matrix& ) = delete;
};
