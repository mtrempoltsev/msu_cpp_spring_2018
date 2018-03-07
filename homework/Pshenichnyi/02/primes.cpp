#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "numbers.dat"
#include <cmath>

int gener_prime_seq (int *a, int x) //сгенерировать массив простых чисел меньших x
{
	int i,p = 3;
	int size = 1;
	a[0] = 2;
	bool status;

	while (p <= x)
	{
		status = 1;
		for (i = 0; i < size; i ++)
		{
			if (p % a[i] == 0) 
			{
				status = 0;
				break;
			}
		}
		if (status)
		{
			a[size] = p;
			size ++;
		}
		p ++;
	}
	return size;
}

int count_prime (const int *a, int n, int *p, int start, int finish)
{
	int i = 0,j = 0,k = 0;

	while (a[i] < start) 
		i ++;
	if (a[i] != start) return 0;

	while(a[i] <= finish && i < n)
	{
		while (p[j] < a[i])
			j ++;
		if (p[j] == a[i]) k++;
		i ++;
	}
	if (a[i-1] != finish) return 0;
	return k;
}


int main(int argc, char* argv[])
{
	if (argc < 3 || (argc+1)%2 != 0) return -1;

	int *intervals, *p, max = -1;

	intervals = new int[argc -1];
	for (int i = 1; i < argc; i ++)
		intervals[i-1] = atoi(argv[i]);

	for (int i = 0; i < argc-1; i ++)
		if (intervals[i] > max)
			max = intervals[i];

	p = new int[max/2 + 1];
	gener_prime_seq (p, max);

	int k = 0;
	for (int i = 0; i < argc - 1; i += 2)
	{
		k = count_prime (Data, Size, p, intervals[i], intervals[i+1]);
		printf("%d\n",k);
	}
	
	delete[] p;
	delete[] intervals;
    return 0;
}

