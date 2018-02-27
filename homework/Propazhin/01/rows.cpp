#include "timer.h"

int main()
{
    size_t SIZE = 10000;

    int **data = new int*[SIZE];
    for (size_t i = 0; i < SIZE; i++)
	data[i] = new int[SIZE];

    for (size_t i = 0; i < SIZE; i++)
	for (size_t j = 0; j < SIZE; j++)
	    data[i][j] = 1;

    volatile int sum = 0;

  {  
    Timer t;
    for (size_t i = 0; i < SIZE; i++)
	for (size_t j = 0; j < SIZE; j++)
	    sum += data[i][j];
  }
    for (size_t i = 0; i < SIZE; i++)
	delete data[i];
    delete[] data;

    return 0;
}
