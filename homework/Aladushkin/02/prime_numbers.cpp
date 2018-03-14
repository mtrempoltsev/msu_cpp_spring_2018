
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include "numbers.dat"

bool* getSieve(const int sizeSieve)
{
	bool *result = new bool[sizeSieve];
	std::fill_n(result, sizeSieve, true);

	result[0] = result[1] = false;
	for (int i = 2; i < int(ceil(sqrt(sizeSieve))); i++)
	{
		if (result[i])
		{
			for (int j = i*i; j < sizeSieve; j += i)
				result[j] = false;
		}
	}

	return result;
}

int main(int argc, char *argv[])
{
	auto sieve = getSieve(100001);

	if (argc % 2 == 0 || argc == 1)
		return -1;

	const int countOfPairs = (argc-1) / 2;

	for (int j = 0; j < countOfPairs; j++)
	{
		int min_p = atoi(argv[1 + 2 * j]);
		int max_p = atoi(argv[2 * j + 1 + 1]);

		if (min_p > max_p)
		{
			std::cout << 0;
			return 0;
		}

		int prime_counter = 0;

		bool isMinExist = false;
		bool isMaxExist = false;

		int indMin;
		int indMax;

		int i = 0;
		for (; i < Size; i++)
		{
			if (Data[i] == min_p)
			{
				isMinExist = true;
				indMin = i;
				break;
			}
		}

		i = Size - 1;
		for (; i >= 0; i--)
		{
			if (Data[i] == max_p)
			{
				isMaxExist = true;
				indMax = i;
				break;
			}
		}

		if (isMinExist && isMaxExist)
		{
			for (int i = indMin; i <= indMax; i++)
				if (sieve[Data[i]])
					prime_counter++;
		}
		else
		{
			std::cout << 0;
			break;
		}

		std::cout << prime_counter << '\n';
	}

	delete[] sieve;

	return 0;
}
