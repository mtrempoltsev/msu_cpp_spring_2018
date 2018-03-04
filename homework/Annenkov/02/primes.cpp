#include "numbers.dat"
// Data - массив
// Size - размер массива
#include <iostream>

#define N 100000

int in_data(int n);
bool prime(int n);

int main(int argc, char* argv[])
{
    // проверка аргументов и запись индексов начала/конца перебора
    if ( (argc-1) % 2 != 0 || argc == 1)
        return -1;

    int* args = new int[argc];
    for (int i = 1; i < argc; ++i)
        args[i] = std::atoi(argv[i]);

    int* index = new int[argc];
    for (int i = 1; i < argc; ++i)
        if ( (index[i] = in_data(args[i])) < 0)
            return 0;

    delete[] args;
    // ----

    bool is_prime[N];
    for (int i = 2; i < N; ++i)
        is_prime[i] = prime(i);

    for (int s = 1; s < argc; s += 2)
    {
        int prime_count = 0;
        for (int i = index[s]; i <= index[s+1]; ++i)
            if ( is_prime[Data[i]] )
                prime_count += 1;

        std::cout << prime_count << std::endl;
    }

    delete[] index;
    return 0;
}


int in_data(int n)
{
    for (int i = 0; i < Size; ++i)
        if (n == Data[i])
            return i;
    return -1;
}

bool prime(int n)
{
    for (int i = 2; i*i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}