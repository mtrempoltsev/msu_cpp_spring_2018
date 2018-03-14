#include <iostream>
#include "numbers.dat"
#include <vector>
#include <cstdlib>


int IsPrime(int numb,const std::vector<int>& lpd){
    if (lpd[numb] == numb)
        return 1;
    else
        return 0;
}


int PrimesWithin(int start, int fin){
    if(start > fin){
	    return 0;
	}
    int i = 0, j = Size - 1;
    for (i; (i <= j) && Data[i] != start; ++i);
    for (j; (j >= i) && Data[j] != fin; --j);
    if(i > j){
        return 0;
    }
    std::vector<int> primes, lpd(fin + 1, 0); //littlest prime divider
    primes.reserve((size_t)(fin / 10));
    for (int i = 2; i <= fin; ++i) {
        if (lpd[i] == 0) {
            lpd[i] = i;
		    primes.push_back (i);
        }
        for (int j = 0; j < (int)primes.size() && primes[j] <= lpd[i] && i * primes[j] <= fin; ++j)
		    lpd[i * primes[j]] = primes[j];
    }
    int counter = 0, is_curr_prime = 0;
    for (int q = i + 1; q <= j + 1; ++q) {
        is_curr_prime = IsPrime(Data[q - 1], lpd);
        counter += is_curr_prime;
        while (q <= j && Data[q] == Data[q - 1]) {
            counter += is_curr_prime;
            ++q;
        }
    }
    return counter;
}


int main(int argc, char* argv[])
{
	if (argc == 1) 
		return -1;
	if (argc % 2 != 1)
		return -1;
    for (int i = 1; i < argc; i += 2)
    {
        int start = std::atoi(argv[i]), fin = std::atoi(argv[i + 1]);
        std::cout << PrimesWithin(start, fin) << std::endl;
    }
    return 0;
} 
