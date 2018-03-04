
// Some optimizations
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <iostream>
#include <cmath>
#include "numbers.dat"

namespace Limits
{
    constexpr int min_bound = 2;
    constexpr int max_bound = 100'000;
    constexpr int MAX_SIZE = max_bound + 1;
}

int read_arg(char *arg)
{
    return std::min(std::max(atoi(arg), Limits::min_bound), Limits::max_bound);
}

int main(int argc, char *argv[])
{
    // Case when number of arguments is incorrect
    if (argc % 2 == 0 || argc <= 1) {
        return -1;
    }

    using Limits::MAX_SIZE;

    // Arrays for computing answer
    bool *is_prime = new bool[MAX_SIZE];
    int *pref = new int[MAX_SIZE];
    int *cnt = new int[MAX_SIZE];

    // Prepare 'is_prime' array
    std::fill(is_prime, is_prime + MAX_SIZE, true);
    is_prime[0] = is_prime[1] = false;

    // Sieve of Eratosthenes
    int sqr_sz = sqrt(Limits::max_bound);
    for (int i = 2; i < sqr_sz + 2; ++i) {
        if (!is_prime[i]) {
            continue;
        }

        for (int j = i * i; j <= Limits::max_bound; j += i) {
            is_prime[j] = false;
        }
    }

    // Count amount of occurrences of each prime number in 'Data' array
    for (int cur : Data) {
        cnt[cur] += is_prime[cur];
    }

    // Count answer for each prefix
    for (int i = 1; i <= Limits::max_bound; ++i) {
        pref[i] = pref[i - 1] + cnt[i];
    }

    // Answer queries
    for (int i = 1; i < argc; i += 2) {
        int l = read_arg(argv[i]);
        int r = read_arg(argv[i + 1]);

        std::cout << (r >= l ? pref[r] - pref[l - 1] : 0) << std::endl;
    }

    delete[] cnt;
    delete[] pref;
    delete[] is_prime;
}

