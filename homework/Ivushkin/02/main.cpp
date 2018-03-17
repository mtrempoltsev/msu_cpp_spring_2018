// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// PVS-settings
// PVS-settings end
#include "numbers.dat"
#include <vector>
#include <iostream>

using namespace std;

int binarysearch(int v, int l, int r)
{
	int m;
	while (l < r)
	{
		m = (l + r) / 2;
		if (Data[m] >= v) r = m;
		else l = m + 1;
	}
	return l;
}

int shiftl(int a)
{
	while (a > 0 && Data[a - 1] == Data[a]) --a;
	return a;
}

int shiftr(int a)
{
	while (a < Size - 1 && Data[a + 1] == Data[a]) ++a;
	return a;
}

int main(int argc, char* argv[])
{
	if (argc % 2 == 0 || argc < 3)
		return -1;
	
	int n = Size + 1;
	vector<char> prime(n + 1, true);
	prime[0] = prime[1] = false;
	for (int i = 2; i <= n; ++i)
		if (prime[i])
			if (i * 1ll * i <= n)
				for (int j = i*i; j <= n; j += i)
					prime[j] = false;
				
	vector<int> pairs(argc - 1);
	vector<int> res;
	for (int i = 1; i < argc; ++i)
	{
		int v = atoi(argv[i]);
		pairs[i - 1] = v;
	}
	
	for (int p = 0; p < argc - 1; ++p)
	{
		if (pairs[p] > pairs[p + 1])
		{
			cout << 0;
			return 0;
		}
		int l = shiftl(binarysearch(pairs[p], 0, Size - 1));
		++p;
		int r = shiftr(binarysearch(pairs[p], 0, Size - 1));
		res.push_back(0);
		for (int i = l; i <= r; ++i)
			if (prime[Data[i]]) ++res[p / 2];
	}
	
	for (int i = 0; i < res.size(); ++i)
	{
		cout << res[i] << endl;
	}
	return 0;
}
