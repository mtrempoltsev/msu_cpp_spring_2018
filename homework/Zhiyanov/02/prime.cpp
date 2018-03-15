#include <stdlib.h>
#include <iostream>

#include "numbers.dat"

bool isprime(int n){
    if (n <= 1)
        return false;
    
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

int main(int argc, char* argv[]){
    
    if (argc % 2 != 1 || argc < 3)
        return -1;

    
    int count = argc - 1;

    for (int i = 0; i < count; i += 2){
        int l = atoi(argv[i + 1]);
        int r = atoi(argv[i + 2]);
        int indl = -1, indr = -1;

        if ((r < l) || (Data[0] > r) || (Data[Size - 1] < l)){
            std::cout << 0 << "\n";
            continue;
        }

        for (int j = 0; j < Size; ++j){
            if (Data[j] >= l && indl == -1)
                indl = j;
            if (Data[j] > r && indr == -1)
                indr = j - 1;
        }

        if (indr == -1)
            indr = Size - 1;

        if (Data[indr] != r || Data[indl] != l){
            std::cout << 0 << "\n";
            continue;
        }

        int count = 0;

        for (int j = indl; j <= indr; ++j)
            if (isprime(Data[j]))
                count++;

        std::cout << count << "\n";

    }

    return 0;
}