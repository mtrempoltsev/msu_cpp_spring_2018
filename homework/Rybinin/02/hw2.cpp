#include <iostream>
#include "numbers.dat"

int* find_primes(int asize)
{
    int *arr = (int *)malloc(asize * sizeof(int));
    for(long long i = 3; i * i <= asize; i += 2)
        for(long long j = i * i; j <= asize; j += 2 * i)
            arr[j] = 1;
    for(int i = 4; i <= asize; i += 2)
        arr[i] = 1;
    arr[0] = 1;
    arr[1] = 1;
    return arr;
}

int* create_map(int asize)
{
    int *arr = (int *)malloc(asize * sizeof(int));
    for (int i = 0; i < asize; ++i)
        arr[i] = 0;
    for(int i = 0; i < Size; ++i)
        if(!arr[Data[i]])
            arr[Data[i]] = i + 1;
    return arr;
}

int main(int argc, char* argv[])
{
    if (argc % 2 == 0 || argc == 1) return -1;
    const int MAX_V = 1e5;
    int *index = create_map(MAX_V + 1);
    int *prime = find_primes(MAX_V + 1);
    for (int i = 1; i < argc; i += 2)
    {
        int start = std::atoi(argv[i]);
        int endd = std::atoi(argv[i+1]);
        if(!index[start] || !index[endd] || index[start] > index[endd]){
            std::cout << 0 << std::endl;
            continue;
        }
        int cnt = 0;
        for(int j = index[start] - 1; j < index[endd]; ++j)
            if(!prime[Data[j]])
                ++cnt;
        std::cout << cnt << std::endl;
    }
    free(index);
    free(prime);
    return 0;
}
