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

    Matrix(const Matrix &m){}
};

Matrix::Matrix():
    Nrows(0), Ncols(0) 
{
    data = nullptr;
}

Matrix::Matrix(int nOfrows, int nOfcols):
    Nrows(nOfrows), Ncols(nOfcols) 
{
    int *data_int = new int[nOfrows*nOfcols];
    data = new int*[nOfrows];
    for (int i = 0; i < nOfrows; i++) {
        data[i] = data_int + nOfcols * i;
    }

    std::srand(100);
    for (int i = 0; i < nOfrows; i++) {
        for (int j = 0; j < nOfcols; j++) {
            data[i][j] = std::rand();
        }
    }
}

Matrix::~Matrix()
{
    delete[] *data;
    delete[] data;
}

int Matrix::SumByRows() 
{
    int sum = 0;
    for (int i = 0; i < Nrows; i++) {
        for (int j = 0; j < Ncols; j++) {
            sum += data[i][j];
        }
    }
    return sum;
}

int Matrix::SumByCols()
{
    int sum = 0;
    for (int i = 0; i < Ncols; i++) {
        for (int j = 0; j < Nrows; j++) {
            sum += data[j][i];
        }
    }
    return sum;
}