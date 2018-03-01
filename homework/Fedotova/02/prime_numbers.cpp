#include <iostream>
#include "numbers.dat"
#include <vector>
#define MAX 100000

// Data - массив
// Size - размер массива

std::vector<unsigned> prime_bin;
unsigned bs = 8 * sizeof(unsigned);

void erat_bin() {
    prime_bin.resize(MAX / bs + 2, ~0);
    prime_bin[0] &= ~(1 + (1 << 1));
    for (unsigned j = 4; j < MAX; j += 2) {
        prime_bin[j / bs] &= ~(1 << (j % bs));
    }
    for (unsigned i = 3; i * i < MAX; i++)
        if (prime_bin[i / bs] & (1 << (i % bs)))
            for (unsigned j = i * i; j < MAX; j += 2 * i)
                prime_bin[j / bs] &= ~(1 << (j % bs));
}

bool is_prime(unsigned n) {
    return (prime_bin[n / bs] & (1 << (n % bs))) != 0;
}

unsigned binary_search(unsigned n, bool begin) {
    unsigned left = 0, right = Size - 1, mid;
    while (left < right) {
        mid = (right + left) / 2;
        if (Data[mid] == n) {
            if (begin) {
                if (mid == 0 || Data[mid - 1] != n)
                    return mid;
                else {
                    right = mid;
                    continue;
                }
            }
            else {
                if (mid == Size - 1 || Data[mid + 1] != n)
                    return mid;
                else {
                    left = mid + 1;
                    continue;
                }
            }
        }
        else if (Data[mid] < n) 
            left = mid + 1;
        else
            right = mid;
    }
    if (Data[left] == n)
        return left;
    else
        return -1;
}

int main(int argc, char* argv[]) {
    erat_bin();
    if (argc % 2 != 1 || argc == 1)
        return -1;

    for (int i = 1; i < argc; i += 2)
    {
        unsigned v1 = std::atoi(argv[i]);
        unsigned v2 = std::atoi(argv[i + 1]);
        if (v2 < v1) {
            std::cout << 0 << std::endl;
            continue;
        }

        unsigned pos1 = binary_search(v1, true);
        unsigned pos2 = binary_search(v2, false);
        if (pos1 == -1 || pos2 == -1) {
            std::cout << 0 << std::endl;
            continue;
        }
        
        unsigned res = 0;
        for (unsigned p = pos1; p <= pos2; p++) {
            if (is_prime(Data[p]))
                res++;
        }
        std::cout << res << std::endl;
    }
    return 0;
}


