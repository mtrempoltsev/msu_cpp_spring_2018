#include <bits/stdc++.h>
#include "numbers.dat"

void eryth_sieve(bool *prime, const int m_n) {
    prime[0] = prime[1] = true;
    for (size_t i = 2; i < m_n; i++) {
        if (!prime[i]) {
            for (size_t j = 2 * i; j < m_n; j += i) {
                prime[j] = true;
            }
        }
    }

}

int binary_s(int x) {
    int l = 0, r = Size, m;
    while (r - 1 > 0) {
        m = (l + r) / 2;
        if (Data[m] == x) {
            return m;
        }
        if (Data[m] < x) {
            l = m;
        }
        if (Data[m] > x) {
            r = m;
        }
    }
    if (Data[l] == x) {
        return l;
    }
    if (Data[r] == x) {
        return r;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (!(argc & 1) || argc == 1) {
        return -1;
    }

    const int MAX_N = 100004;

    bool *prime = new bool[MAX_N];
    std::fill_n(prime, MAX_N, false);

    eryth_sieve(prime, MAX_N);

    int l, l_ind, r, r_ind, result;
    for (size_t i = 1; i < argc; i += 2) {

        l = std::atoi(argv[i]);
        l_ind = binary_s(l);
        r = std::atoi(argv[i+1]);
        r_ind = binary_s(r);

        if (l_ind == -1 || r_ind == -1) {
            continue;
        }

        result = 0;
        for (int j = l_ind; j <= r_ind; ++j) {
            result += !prime[Data[j]];
        }

        std::cout << result << std::endl;
    }

    delete[] prime;

    return 0;
}
