#include <iostream>
#include "numbers.dat"

void sieve(bool *primes, int len)
{
    for(int i = 0; i < len; i++)
        primes[i] = true;

    primes[0] = primes[1] = false;

    for (int i = 2; i < len; i++)
    {
        if (primes[i])
        {
            for (int j = 2 * i; j < len; j += i)
                primes[j] = false;
        }
    }
}

int left(int edge)
{
    int l = 0, r = Size, med;

    while(r - l > 1)
    {
        med = (l + r) / 2;
        if(Data[med] >= edge)
            r = med;
        else
            l = med;
    }

    if(edge == Data[l])
        return l;
    if(edge == Data[r])
        return r;
    return -1;
}

int right(int edge)
{
    int l = 0, r = Size, med;

    while(r - l > 1)
    {
        med = (l + r) / 2;
        if(Data[med] <= edge)
            l = med;
        else
            r = med;
    }

    if(edge == Data[l])
        return l;
    if(edge == Data[r])
        return r;
    return -1;
}

int main(int argc, char *argv[])
{
    if(!(argc & 1) || argc == 1)
        return -1;

    const  int n = Size + 1;

    bool *primes = new bool[n];
    sieve(primes, n);

    int l, r, ld, rd;
    for(int i = 1; i < argc; i += 2)
    {
        l = std::atoi(argv[i]);
        r = std::atoi(argv[i + 1]);

        ld = left(l);
        rd = right(r);

        if(ld == -1 || rd == -1)
            continue;

        int counter = 0;
        for(int j = ld; j <= rd; ++j)
            counter += primes[Data[j]];

        std::cout << counter << std::endl;
    }

    delete [] primes;

    return 0;
}
