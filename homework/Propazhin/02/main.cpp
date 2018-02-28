#include <iostream>
#include "numbers.dat"
#include "header.h"

int main(int argc, char* argv[])
{
	int first = 0, last = 0, k = 0;
	if (argc < 3 || argc % 2 == 0) return -1;
    
    for (int i = 1; i < argc; i += 2)
    {
		int count = 0;
       		first = bin_search(Data, std::atoi(argv[i]), 0, Size);
		last = bin_search(Data, std::atoi(argv[i+1]), 0, Size);
		
		if (first == -1 || last == -1) return 0;
	
		for (int i = first; Data[i] == Data[first] && i >= 0; k = i, i--);
		first = k;
		for (int i = last; Data[i] == Data[last] && i <= Size; k = i, i++);
		last = k;
		
		for (int i = first; i <= last; i++) 
			count += IsPrime(Data[i]);
		std::cout << count << std::endl;
    }
	
    return 0;
}