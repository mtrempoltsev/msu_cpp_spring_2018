#include "timer.h"

#define ROWS 1000
#define COLS 1000

int main()
{
    int **a = new int*[ROWS];
    for(int i = 0; i < ROWS; ++i)
        a[i] = new int[COLS];

    {
        Timer t;
        
        volatile long sum = 0;
        for(int i = 0; i < ROWS; ++i)
            for(int j = 0; j < COLS; ++j)
                sum += a[i][j];
    }

    for(int i = 0; i < ROWS; ++i)
        delete[] a[i];

    delete[] a;

    return 0;
}