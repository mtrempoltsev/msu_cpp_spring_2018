#include "timer.h"

int main()
{
    volatile int **data;
    data = new volatile int*[10000];
    for (int i = 0; i < 10000; i++)
	data[i] = new volatile int[10000];

    for (int i = 0; i < 10000; i++)
	for (int j = 0; j < 10000; j++)
	    data[i][j] = 10;

    volatile int sum = 0;
    
    Timer t;
    for (int i = 0; i < 10000; i++)
	for (int j = 0; j < 10000; j++)
	    sum += data[j][i];

    delete[] data;

    return 0;
}
