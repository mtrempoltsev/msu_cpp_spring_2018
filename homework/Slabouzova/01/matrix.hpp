#include <cstdlib>
#include <ctime>
#include <iostream>

class Matrix
{
    int n;
    int **arr;
public:
    Matrix(int n_size) : 
        n(n_size)
    { 
        arr = new int* [n]; 
        for (int i = 0; i < n; i++) {
            arr[i] = new int [n];
        }
        initMatrix();
    }

    void initMatrix()
    {
        srand(time(nullptr));
        int low = -1000;
        int high = 1000;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j] = rand() / RAND_MAX * (high - low) + low;
            }
        }
    }

    int getElement(int i, int j)
    {
        return arr[i][j];
    }

    ~Matrix()
    {
        for (int i = 0; i < n; i++) {
            delete [] arr[i];
        }
        delete [] arr;
    }
    
};
