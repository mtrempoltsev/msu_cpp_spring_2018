
#include <iostream>
#include "numbers.dat"

namespace Limits
{
    constexpr int min_bound = 2;
    constexpr int max_bound = 100'000;
}

// Returns true if prime and false in another case
bool is_prime(int x)
{
    if (x <= 1) {
        return false;
    }

    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }

    return true;
}

int read_arg(char *arg)
{
    return std::min(std::max(atoi(arg), Limits::min_bound), Limits::max_bound);
}

int main(int argc, char *argv[])
{
    // Case when number of arguments is incorrect
    if (argc % 2 == 0 || argc == 1) {
        return -1;
    }

    for (int i = 1; i + 1 < argc; i += 2) {
        int l = read_arg(argv[i]);
        int r = read_arg(argv[i + 1]);

        int ans = 0;

        //   For each number in 'Data' check if it's prime and 
        // it's in [l, r] segment
        for (int cur : Data) {
            if (l <= cur && cur <= r) {
                ans += is_prime(cur);
            }
        }
        std::cout << ans << std::endl;
    }
}

