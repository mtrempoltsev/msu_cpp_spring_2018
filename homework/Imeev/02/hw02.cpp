#include "numbers.dat"
#include <iostream>

enum
{
    DELTA = 2,
    MIN_ARGS = 3,

    FIRST_PRIME = 2,
    SECOND_PRIME = 3,
};

int get_index(const int *data, int n, int num);
int prime_counter(const int *, int);
int check(int num);

int
main(int argc, char *argv[])
{
    if (argc < MIN_ARGS || !(argc & 1)) {
        return -1;
    }
    for (int i = 1; i < argc; i += DELTA) {
        int first = get_index(Data, Size, std::atoi(argv[i]));
        int last = get_index(Data, Size, std::atoi(argv[i + 1]));
        if (first >= 0 and last >= 0) {
            std::cout << prime_counter(Data + first, last - first + 1) << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }
    }
    return 0;
}

int
get_index(const int *data, int n, int num)
{
    int i;
    for (i = 0; i < n && data[i] <= num; ++i) {};
    if (num == data[i - 1]) {
        return i - 1;
    }
    return -1;
}

int
prime_counter(const int *data, int n)
{
    int counter = check(data[0]);
    for (int i = 1; i < n; ++i) {
        counter += check(data[i]);
    }
    return counter;
}

int
check(int num)
{
    if (num == FIRST_PRIME) {
        return 1;
    } 
    if (num < FIRST_PRIME || !(num & 1)) {
        return 0;
    }
    for (int i = SECOND_PRIME; i * i <= num; i += DELTA) {
        if (!(num % i)) {
            return 0;
        }
    }
    return 1;
}