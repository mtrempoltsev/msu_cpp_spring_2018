#include <iostream>
#include <vector>
#include "numbers.dat"

void make_Sieve(std::vector<bool>& prime, int n)
{
	prime[0] = prime[1] = false;
	for (int i = 0; i <= n; i++)
	{
		if (prime[i])
		{
			if (i * 1ll * i <= n)
			{
				for (int j = i * i; j <= n; j += i)
					prime[j] = false;
			}
		}
	}
}

int binarySearch(int val, const int* a, int left, int right)
{
	if (left >= right)
		return a[left] == val ? left : -1;
	int mid = (left + right) / 2;
	if (a[mid] == val)
		return mid;
	if (a[mid] < val)
		return binarySearch(val, a, mid + 1, right);
	else
		return binarySearch(val, a, left, mid - 1);
}

int main(int argc, char* argv[])
{
	if (argc % 2 == 0 || argc == 1)
		return -1;

	int num_of_pairs = argc / 2;
	int* left = new int[num_of_pairs];
	int* right = new int[num_of_pairs];
	for (int n = 0; n < num_of_pairs; n++)
	{
		left[n] = std::atoi(argv[n * 2 + 1]);
		right[n] = std::atoi(argv[n * 2 + 2]);
	}

	int MAX = 100000;
	std::vector<bool> prime(MAX + 1, true);
	make_Sieve(prime, MAX);

	for (int n = 0; n < num_of_pairs; n++)
	{
		int left_index = binarySearch(left[n], Data, 0, Size - 1);
		int right_index = binarySearch(right[n], Data, 0, Size - 1);
		if (left_index == -1 || right_index == -1)
			return 0;
		while (left_index > 0 && Data[left_index - 1] == left[n])
			left_index--;
		while (right_index < Size - 1 && Data[right_index + 1] == right[n])
			right_index++;
		int count = 0;
		for (int i = left_index; i <= right_index; i++)
		{
			if (prime[Data[i]])
				count++;
		}
		std::cout << count << std::endl;
	}
	return 0;
}