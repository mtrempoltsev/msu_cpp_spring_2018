#include "numbers.dat"
#include <iostream>


namespace options
{
    constexpr size_t size = 100000;
}

size_t binarySearchForLeft(int key)
{
	int l = 0, r = Size - 1;
	while (l < r)
	{
		int m = l + (r - l)/2;
		if (Data[m] >= key)
			r = m;
		else
			l = m + 1;
	}
	return Data[l] == key ? l : -1;
}

size_t binarySearchForRight(int key)
{
	int l = 0, r = Size - 1;
	while (l < r)
	{
		int m = r - (r - l)/2;
		if (Data[m] <= key)
			l = m;
		else
			r = m - 1;
	}
	return Data[l] == key ? l : -1;
}

void eratosphen(int *prime)
{
	prime[0] = prime[1] = 1;
	for (size_t i = 2; i < options::size; i++)
		if (!prime[i])
			for (size_t j = 2 * i; j < options::size; j += i)
				prime[j] = 1;
}

int main(int argc, char* argv[])
{
	if ((argc == 1) || (argc % 2 == 0))
		return -1;
	int first, last, summa = 0;
	int *prime = new int[options::size]();
	eratosphen(prime);
	for (int i = 0; i < (argc - 1) / 2; i++)
	{
		summa = 0;
		first = std::atoi(argv[i * 2 + 1]);
		last = std::atoi(argv[i * 2 + 2]);
		size_t leftIndex = binarySearchForLeft(first);
		if (leftIndex == -1)
			return 0;
		size_t rightIndex = binarySearchForRight(last);
		if (rightIndex == -1)
			return 0;
		for (size_t j = leftIndex; j <= rightIndex; j++)
			summa += !prime[Data[j]];
		std::cout << summa << std::endl;
	}
        delete[] prime;
}
