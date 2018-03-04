#include <iostream>
#include <cmath>
#include "numbers.dat"

/*inline bool is_prime(int n)
{
	for(register int i = 2; i <= sqrt(n); ++i)
		if(n % i == 0)
			return false;

	if(n == 0 || n == 1)
		return false;

	return true;
}*/


inline void Eratosphen(bool sieve[], const int size)
{
	sieve[0] = sieve[1] = true;
	for(register int p = 2; p < size; p++)
	{
		if(sieve[p] != true && (size_t)p*p < size)
		for(register int j = p*p; j < size; j += p)
			sieve[j] = true;
	}
}

inline int count_prime_numb(const int size, int left, int right, const int array[], bool sieve[]) 
{
	int count = 0;
	int lindex = size;
	int rindex = size;
		
	int l = 0;
	int r = size;
	int middle;
	
	while(l + 1 < r)
	{
		middle = l + (r - l)/2;
		if(array[middle] > left)
			r = middle;
		else
			l = middle;
				
	}
	if(left == array[l])
		while(true)
		{
			if(array[l-1] == left && l-1 >= 0)
				l -= 1;
			else
			{
				lindex = l;
				break;
			}
		}
	
	if(lindex == size)
		return count;	
	
	l = lindex;
	r = size;
	
	while(l + 1 < r)
	{
		middle = l + (r - l)/2;
		if(array[middle] > right)
			r = middle;
		else
			l = middle;
				
	}
	if(right == array[l])
		while(true)
		{
			if(array[l+1] == right && l+1 < size)
				l += 1;
			else 
			{
				rindex = l;
				break;
			}
		}
						
	if(rindex == size)
		return count;
		
	for(register int i = lindex; i <= rindex; ++i)
		if(!sieve[array[i]]) //we may input: is_prime(array[i])
			count++;
		
	return count;
}



int main(int argc, char* argv[])
{	
	if (((argc - 1)%2 != 0) || (argc == 1))
		return -1;
	
	for(int i = 1; i < argc; i+=2)
	{
		if (std::atoi(argv[i]) > std::atoi(argv[i+1]))
		{
			std::cout<<0<<std::endl;
			return 0;
		}
	}
		
	int left=0;
	int right=0;

	bool sieve[Size];
	for(register int i = 0; i < Size; ++i)
		sieve[i] = false;

	Eratosphen(sieve, Size);

	
	for(int i = 1; i < argc; i+=2)
	{
		left = std::atoi(argv[i]);
		right = std::atoi(argv[i+1]);
		std::cout<<count_prime_numb(Size, left, right, Data, sieve)<<std::endl;
	}
	
	return 0;
}
