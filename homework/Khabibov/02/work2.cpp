#include "numbers.dat"
#include <iostream>

int binarySearchForLeft(int key)
{
  size_t l = 0, r = Size - 1;
  while (l < r)
  {
    size_t m = l + (r - l)/2;
    if (Data[m] >= key)
      r = m;
    else
      l = m + 1;
  }
  return Data[l] == key ? l : -1;
}

int binarySearchForRight(int key)
{
  size_t l = 0, r = Size - 1;
  while (l < r)
  {
    size_t m = r - (r - l)/2;
    if (Data[m] <= key)
      l = m;
    else
      r = m - 1;
  }
  return Data[l] == key ? l : -1;
}

int prime(int x)
{
	int i;
	if (x == 2) return 1;
	if ((x == 1) || (x % 2 == 0)) return 0;
	for (i = 3; (i * i <= x) && (x % i != 0); i += 2);
	return (i * i > x);
}

int main(int argc, char* argv[])
{
	if ((argc == 1) || (argc % 2 == 0))
		return -1;
	int first, last, summa = 0;
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
			summa += prime(Data[j]);
		std::cout << summa << std::endl;
	}
}
