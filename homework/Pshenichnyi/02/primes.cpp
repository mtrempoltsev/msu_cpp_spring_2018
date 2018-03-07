#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "numbers.dat"
#include <cmath>


int gener_prime_seq (int *a, int n, int x) //сгенерировать массив простых чисел меньших x
{
	int i;
	int p = 3; //простое число которое и будем добавлять в массив
	int size = 1; //размер генерируемого массива
	a[0] = 2;
	bool status; //прошло ли число проверку на простоту для дальнейшего добавления в массив пр.чис.

	while (p <= x)
	{
		if (size > n) return -1; //ошибка с размером массива

		status = true;
		for (i = 0; i < size; i ++)
		{
			if (p % a[i] == 0) 
			{
				status = false;
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

int count_prime (const int *a, int n, int *p, int start, int finish) //возвращает количество прост чисел на ОДНОМ промежутке
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

	intervals = new int[argc -1]; //массив границ 
	for (int i = 1; i < argc; i ++)
		intervals[i-1] = atoi(argv[i]);

	for (int i = 0; i < argc-1; i ++)
		if (intervals[i] > max)
			max = intervals[i]; /*нашли максимальное число из промежутка для 
								  того чтобы знать сколько выделить памяти для массива прост.чис.*/ 

	p = new int[max/2 + 1]; //массив простых чисел
	if (gener_prime_seq (p, max/2 + 1, max) < 0)
	{
		return 0;
	}

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

