//Kononov Sergey group BD-11
//Task 2

#include <iostream>
#include "numbers.dat"
#include <vector>

const int N = 100000;
std::vector <bool> simp_numbers_array(N + 1, true);

//Creation array of simple numbers using eratosthenes sieve
void filter_numbers()
{
	simp_numbers_array[0] = simp_numbers_array[1] = false;
	for (int i = 2; i <= N; ++i)
		if (simp_numbers_array[i])
			if (i * 1ll * i <= N) //long long type
				for (int j = i * i; j <= N; j += i)
					simp_numbers_array[j] = false;
}

//Check if current values is in array of simple numbers
int count(const int l_pos, const int r_pos)
{
	int cnt = 0;

	for (int j = l_pos; j <= r_pos; ++j)
		if (simp_numbers_array[Data[j]]) 
			cnt++;
	
	return cnt;
}

//Find positin for left and right border
int simple_numbers(int l_bound, int r_bound)
{
	int x = 0, pos = 0, l_pos = 0, r_pos = Size -1, cnt = 0;

	while (pos < Size)
	{
		x = Data[pos];
		if (x < l_bound)
		{
			pos++;
			continue;
		}
		l_pos = pos;
		break;
	}

	pos = Size - 1;
	while (pos >= 0)
	{
		x = Data[pos];
		if (x > r_bound)
		{
			pos--;
			continue;
		}
		r_pos = pos;
		break;
	}

	return count(l_pos, r_pos);
};

int main(int argc, char* argv[])
{
	if ((argc == 1) || ((argc % 2) == 0)) return -1;
	
	int l_bound, r_bound, result = 0;

	filter_numbers();

	int i = 1; 
	while (i < argc)
	{
		l_bound = std::atoi(argv[i++]);
		r_bound = std::atoi(argv[i++]);
		
		if (l_bound > r_bound)
		{
			std::cout << 0;
			return 0;
		};

		result = simple_numbers(l_bound, r_bound);
		std::cout << result << std::endl;
	}

	return 0;
}
