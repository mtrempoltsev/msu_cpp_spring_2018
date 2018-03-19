#include "numbers.dat"
#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    const int max = 100001;
    std::unique_ptr<bool[]> isPrime_ptr(new bool[max]);
    bool* isPrime = isPrime_ptr.get();
    for (int i = 0; i < max; ++i) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < max; ++i) {
        if (isPrime[i]) {
            for (int j = i * 2; j < max; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    std::unique_ptr<int[]> countOfPrimeNumber_ptr(new int[Size]);
    int* countOfPrimeNumber = countOfPrimeNumber_ptr.get();
    countOfPrimeNumber[0] = isPrime[Data[0]];
    for (int i = 1; i < Size; ++i) {
        countOfPrimeNumber[i] = countOfPrimeNumber[i - 1] + isPrime[Data[i]];
    }
    if (argc % 2 != 1 || argc == 1) {
        return -1;
    }
    for (int k = 1; k < argc; k += 2) {
        int n = atoi(argv[k]);
        int m = atoi(argv[k + 1]);
        if (m < n) {
            std::cout << 0 << std::endl;
            return 0;
        }
        int i = 0;
        while (i < Size && Data[i] != n) {
            ++i;
        }
        if (i >= Size) {
            std::cout << 0 << std::endl;
            return 0;
        }
        int j = Size - 1;
        while (j >= 0 && Data[j] != m) {
            --j;
        }
        if (j < 0) {
            std::cout << 0 << std::endl;
            return 0;
        }
        std::cout << countOfPrimeNumber[j] - countOfPrimeNumber[i] + isPrime[Data[i]] << std::endl;
    }
    return 0;
}
