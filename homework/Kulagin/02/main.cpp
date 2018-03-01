#include <iostream>
#include <vector>
#include <cmath>

#include "numbers.dat"

using namespace std;

int main(int argc, char** argv) {
	if (argc < 3 || argc % 2 == 0) {
		return -1;
	}

	int k1, k2;

	int n = 0;

	for (int a = 1; a < argc; a += 2) {
		k1 = atoi(argv[a]);
		k2 = atoi(argv[a + 1]);

		if (k1 > k2) {
			printf("0");

			return 0;
		}

		n = max(n, k2);
	}

	vector<bool> prime(n, true);

	prime[0] = prime[1] = false;

	for (int i = 2; i * i <= n; i++)
		if (prime[i])
			for (int j = i + i; j <= n; j += i)
				prime[j] = false;

	int prime_cnt;

	int i;

	for (int a = 1; a < argc; a += 2) {
		k1 = atoi(argv[a]);
		k2 = atoi(argv[a + 1]);

		prime_cnt = 0;

		i = 0;

		for (i = 0; Data[i] < k1; i++);

		while (Data[i] < k2)
			prime_cnt += prime[	Data[i++]];

		printf("%d\n", prime_cnt);
	}

	return 0;
}
