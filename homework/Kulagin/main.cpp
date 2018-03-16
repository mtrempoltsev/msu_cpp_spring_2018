#include <iostream>
#include <cmath>
#include "numbers.dat"

using namespace std;

bool is_prime(int x) {
	if (x == 1)
		return false;

	for (int i = 2; i <= sqrt(x); i++) {
		if (x % i == 0)
			return false;
	}

	return true;
}

int main(int argc, char** argv) {
	if (argc < 3 || argc % 2 == 0) {
		return -1;
	}


	for (int a = 1; a < argc; a += 2) {
		int k1 = atoi(argv[a]);
		int k2 = atoi(argv[a + 1]);

		if (k1 > k2) {
			cout << 0 << endl;

			return 0;
		}

		bool prime = false;

		int i;

		int prime_cnt = 0;

		for (i = 0; Data[i] < k1; i++);

		while (Data[i] < k2)
			prime_cnt += is_prime(Data[i++]);

		prime_cnt += is_prime(k2);

		cout << prime_cnt << endl;
	}


	return 0;
}