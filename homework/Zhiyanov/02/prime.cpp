#include <stdlib.h>
#include <iostream>

#include "numbers.dat"


int indl(int n){
    for (int i = 0; i < Size; ++i)
        if (n <= Data[i])
            return i;

    return -1;
}

int indr(int n){
    if (n < 0)
        return -1;
    for (int i = 0; i < Size; ++i)
        if (n < Data[i])
            return i - 1;

    return Size - 1;
}

bool isprime(int n){
    if (n <= 1)
        return False;
    
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return False;
    return True;
}

int main(int argc, char* argv[]){
    
    if (argc % 2 != 1 || argc < 3)
        return -1;

    
    int argcc = argc - 1;

    int* ind = new int[argcc];
    for (int i = 0; i < argcc; i += 2){
        ind[i] = indl(atoi(argv[i + 1]));
        ind[i + 1] = indr(atoi(argv[i + 2]));
        if (ind[i] == -1 || ind[i + 1] == -1){
            delete [] ind;
            return -1;
        }
    }


    for (int i = 0; i < argcc; i += 2){
        int count = 0;
        for (int j = ind[i]; j <= ind[i + 1]; ++j)
            if (isprime(Data[j]))
                count += 1;
        std::cout << count << "\n";
    }

    delete [] ind;
    return 0;
}