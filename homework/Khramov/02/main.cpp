#include <iostream>
#include <cmath>
#include "numbers.dat"

bool* Sieve(const int N){
	bool *rez = new bool[N];
	std::fill_n(rez, N, true);

	rez[0] = rez[1] = false;
	for (int i = 2; i < int(ceil(sqrt(N))); i++) {
		if (rez[i]) 
			for (int j = i*i; j < N; j += i)
				rez[j] = false;
	}
	return rez;
}


int binsrch(const int* a, int left, int right,int key ) {
	if (left >= right)
		return a[left] == key ? left : -1;
	int mid = (left + right) / 2;
	if (a[mid] == key)
		return mid;
	if (a[mid] < key)
		return binsrch(a, mid + 1, right, key);
	else
		return binsrch(a, left, mid - 1, key);
}


int main(int argc, char* argv[]){
	if (argc % 2 == 0 || argc == 1)
		return -1;
	
	auto sieve = Sieve(100001);
	int parz = (argc - 1) / 2;
	
	for (int i = 0; i < parz; i++) {
		int lPair = std::atoi(argv[i * 2 + 1]);
		int rPair = std::atoi(argv[i * 2 + 2]);
		
		int lInd = binsrch(Data, 0, Size - 1, lPair);
		int rInd = binsrch(Data, 0, Size - 1, rPair);
		if (lInd == -1 || rInd == -1)
			return 0;
		
		while ((lInd > 0) && (Data[lInd - 1] == lPair))
			lInd--;
		while ((rInd < Size - 1) && (Data[rInd + 1] == rPair))
			rInd++;
		
		int count = 0;
		for (int j = lInd; j <= rInd; j++)
			if (sieve[Data[j]])
				count++;
		std::cout << count << std::endl;
	}
	
	delete[] sieve;
	return 0;
}