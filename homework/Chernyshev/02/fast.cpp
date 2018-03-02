
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

bool is_prime[Limits::MAX_SIZE];
int pref[Limits::MAX_SIZE];
int cnt[Limits::MAX_SIZE];

int read_arg(char *arg)
{
    return std::min(std::max(atoi(arg), Limits::min_bound), Limits::max_bound);
}

int main(int argc, char *argv[])
{
    using Limits::MAX_SIZE;

    // Case when number of arguments is incorrect
    if (argc % 2 == 0 || argc <= 1) {
        return -1;
    }

    // Prepare 'is_prime' array
    std::fill(std::begin(is_prime), std::end(is_prime), true);
    is_prime[0] = is_prime[1] = false;

    // Sieve of Eratosthenes
    int sqr_sz = sqrt(MAX_SIZE);
    for (int i = 2; i < sqr_sz + 2; ++i) {
        if (!is_prime[i]) {
            continue;
        }

        for (int j = i * i; j < MAX_SIZE; j += i) {
            is_prime[j] = false;
        }
    }

    // Count amount of occurrences of each prime number in 'Data' array
    for (int cur : Data) {
        cnt[cur] += is_prime[cur];
    }

    // Count answer for each prefix
    for (int i = 1; i < MAX_SIZE; ++i) {
        pref[i] = pref[i - 1] + cnt[i];
    }

    // Answer queries
    for (int i = 1; i < argc; i += 2) {
        int l = read_arg(argv[i]);
        int r = read_arg(argv[i + 1]);

        std::cout << (r >= l ? pref[r] - pref[l - 1] : 0) << std::endl;
    }
}

