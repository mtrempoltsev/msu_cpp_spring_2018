#include <iostream>
#include <cmath>
#include <cstdlib>
#include "numbers.dat"

int main(int argc, char *argv[])
{
    using std::cout;
    using std::size_t;
    using std::endl;
    if (argc == 1 || (argc & 1) == 0) {
        return -1;
    }
    constexpr int MAX = sqrt(100000) + 1, BASE = 10;
    int *f = new int[Size];
    for (size_t i = 0; i < Size; ++i) {
        f[i] = 1;
    }
    for (int i = 2; i < MAX; ++i) {
        for (size_t j = 0; j < Size; ++j) {
            if (f[j] && ((Data[j] != i && Data[j] % i == 0) || Data[j] == 1)) {
                f[j] = 0;
            }
        }
    }
    char *test = nullptr;
    for (int i = 1; i < argc; i += 2) {
        int left = strtol(argv[i], &test, BASE);
        unsigned sum = 0;
        if (*test) {
            return -1;
        }
        int right = strtol(argv[i + 1], &test, BASE);
        if (*test) {
            return -1;
        }
        if (left > right) {
            cout << 0 << endl;
            continue;
        }
        size_t L = 0, R = Size - 1;
        for (; Data[L] < left; L++) {};
        if (Data[L] != left) {
            cout << 0 << endl;
            continue;
        }
        for (; Data[R] > right; R--) {};
        if (Data[R] != right) {
            cout << 0 << endl;
            continue;
        }
        for (size_t i = L; i <= R; ++i) {
            sum += f[i];
        }
        cout << sum << endl;
    }
    return 0;
}
