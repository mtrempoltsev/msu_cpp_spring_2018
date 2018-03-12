#include <stdlib.h>
#include <iostream>

#include "numbers.dat"

const int  N = 100000;

int indata(int n){
    for (int i = 0; i < Size; ++i)
        if (n == Data[i])
            return i;
    return -1;
}

bool isprime(int n){
    if (n <= 1)
        return 0;
    
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return 0;
    return 1;
}

int main(int argc, char* argv[]){
    
    if (argc % 2 != 1 || argc < 3)
        return -1;

    
    argc--;

    int* ind = new int[argc];
    for (int i = 0; i < argc; ++i){
        ind[i] = indata(atoi(argv[i + 1]));
        if (ind[i] == -1){
            delete [] ind;
            return -1;
        }
    }


    for (int i = 0; i < argc; i += 2){
        int count = 0;
        for (int j = ind[i]; j <= ind[i + 1]; ++j)
            if (isprime(Data[j]))
                count += 1;
        std::cout << count << "\n";
    }

    delete [] ind;
    return 0;
}