#include<iostream>
#include "numbers.dat"
void seive(bool*,size_t); //eratosthenes sieve 
int bin_search(int, int, int, bool);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return -1;
	const size_t seive_size=100001;
	bool*A = new bool[seive_size];//mask for eratosthenes sieve
	seive(A, seive_size);
	int l, r,left,right; //l,r - indices; left,right - corresponding values
	for (int i = 0; i < argc-1; i++)
	{
		left = atoi(argv[i + 1]);
		i++;
		if (i + 1 == argc)
			return -1;
		right = atoi(argv[i + 1]);
		if (left > right)
		{
			std::cout << 0 << std::endl;
			continue;
		}
		l = bin_search(0, Size - 1, left, true); //true for left boundary
		r = bin_search(0, Size - 1, right, false); 
		if (l == -1 || r == -1)
			std::cout << 0 << std::endl;
		else
		{
			int sum = 0;
			for (int n = l; n <= r; n++)
				if (!A[Data[n]])
					sum += 1;
			std::cout << sum<<std::endl;
		}
	}
	delete[]A;
	return 0;
}
int bin_search(int l, int r, int a,bool flag)
{
	int c = (r + l) / 2;
	if (l>r)
		return -1;
	else if (Data[c] < a)
		return bin_search(c + 1, r, a, flag);
	else if (Data[c] > a)
		return bin_search(l, c - 1, a, flag);
	else
	{
		if (flag) //if flag is true, search left boundary
		{
			while (Data[c] == a)
				c -= 1;
			c += 1;
			return c;
		}
		else
		{
			while (Data[c] == a)
				c += 1;
			c -= 1;
			return c;
		}
	}
}
void seive(bool* A,size_t seive_size)
{
	
	for (size_t i = 0; i < seive_size; i++)
		A[i] = false;
	A[1] = true;
	for (size_t i = 4; i < seive_size; i += 2)
		A[i] = true;
	for (size_t i = 3; i*i < seive_size; i += 2)
	{
		if (!A[i])
			for (size_t j = i*i; j < seive_size; j += i)
				A[j] = true;
	}
}
