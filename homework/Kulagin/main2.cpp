#include <iostream>
#include <cmath>
#include <vector>
#include "numbers.dat"

using namespace std;

int main(int argc, char** argv) {
	if (argc < 3 || argc % 2 == 0) {
		return -1;
	}

	int k1, k2, n, max_n = 0;

	for (int a = 1; a < argc; a += 2) {
		int k1 = atoi(argv[a]);
		int k2 = atoi(argv[a + 1]);

		if (k1 > k2) {
			cout << 0 << endl;

			return 0;
		}

		max_n = max(max_n, k2);
	}

	n = max_n;

	int lp[n + 1];
	vector<int> pr;

	for (int i = 2; i <= n; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back (i);
		}

		for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= n; j++)
			lp[i * pr[j]] = pr[j];
	}

	for (int i = 0; i < pr.size(); i++)cout << pr[i] << " ";
	return 0;
	// vector<bool> prime(n, true);

	// prime[0] = prime[1] = false;

	// for (int i = 2; i * i <= n; i++)
	// 	if (prime[i])
	// 		for (int j = i + i; j <= n; j += i)
	// 			prime[j] = false;

	int prime_cnt, i;

	for (int a = 1; a < argc; a += 2) {
		k1 = atoi(argv[a]);
		k2 = atoi(argv[a + 1]);

		prime_cnt = 0;

		i = 0;

		for (i = 0; Data[i] < k1; i++);

		while (Data[i] < k2) {
			prime_cnt += pr[Data[i++]];
		}

		// prime_cnt += pr[k2];

		printf("%d\n", prime_cnt);
	}

	return 0;
}