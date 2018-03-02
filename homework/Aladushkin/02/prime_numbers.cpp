
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include "numbers.dat"

// Data - массив
// Size - размер массива

bool* getSieve()
{
	bool *result = new bool[100001];
	std::fill_n(result, 100001, true);

	result[0] = result[1] = false;
	for (int i = 2; i < ceil(sqrt(100001)); i++)
	{
		if (result[i])
		{
			for (int j = i*i; j < 100001; j += i)
				result[j] = false;
		}
	}

	return result;
}

int main(int argc, char *argv[])
{
	auto sieve = getSieve();

	//int Size;
	//scanf("%i", &Size);

	//std::unique_ptr<int[]> Data(new int[Size]);

	//for (int i = 0; i < Size; i++)
	//	scanf("%i", &Data[i]);

	if (argc % 2 == 0 || argc == 1)
		return -1;

	int countOfPairs = (argc-1) / 2;
	std::vector<std::pair<int, int>> vec_min_max_pairs(countOfPairs);

	for (int i = 0; i < countOfPairs; i++)
	{ 

		//int v_max = std::max(atoi(argv[1 + 2 * i]), atoi(argv[2 * i + 1 + 1]));
		//int v_min = std::min(atoi(argv[1 + 2 * i]), atoi(argv[2 * i + 1 + 1]));

		vec_min_max_pairs[i] = { atoi(argv[1 + 2 * i]), atoi(argv[2 * i + 1 + 1]) };
	}

	for (int j = 0; j < countOfPairs; j++)
	{
		if (vec_min_max_pairs[j].first > vec_min_max_pairs[j].second)
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
			if (Data[i] == vec_min_max_pairs[j].first)
			{
				isMinExist = true;
				indMin = i;
				break;
			}
		}

		i = Size - 1;
		for (; i >= 0; i--)
		{
			if (Data[i] == vec_min_max_pairs[j].second)
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

	return 0;

}
