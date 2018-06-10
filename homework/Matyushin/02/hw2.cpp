#include "numbers.dat"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory>

#define MILLER_RABIN_ITER 5

int toBin(int n, std::unique_ptr<bool[]>& bins, int bins_len){
    int t = n;
    int i = 0;
    while ((t > 0) && (i < bins_len)){
        if (t % 2 == 0){
            bins[i] = 0;
            t = t / 2;
        }
        else{
            bins[i] = 1;
            t = (t - 1) / 2;
        }
            
        i++;
    }
    
    return i;
}

bool MillerRabin(int p){
    int binary_len = (int)log2(p) + 1;
    
    auto binary = std::make_unique<bool[]>(binary_len);
    
    for (int i = 0; i < MILLER_RABIN_ITER; i++){
        long int a = rand() % (p - 1) + 1;
        int l = toBin(p - 1, binary, binary_len);
        long int d = 1;
        for (int j = l - 1; j >= 0; j--){
            long int x = d;
            d = (d * d) % p;
            if ((d == 1) && (x != 1) && (x != p - 1))
                return false;
            if (binary[j] == 1)
                d = (d * a) % p;
        }
        if (d != 1)
            return false;
    }
    return true;
}

void generatePrimes(std::unique_ptr<int[]>& arr, int arr_len){    
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 1;
    for (int i = 3; i < 100000; i++)
        arr[i] = MillerRabin(i);
}

int main(int argc, char** argv){
    const int PRIME_LIMIT = 100001; //with zero counted
    
    auto primes = std::make_unique<int[]>(PRIME_LIMIT);
    
    if ((argc == 1) || (argc % 2 == 0))
        return -1;
    
    generatePrimes(primes, PRIME_LIMIT);
    for (int pair = 0; pair < ((argc - 1) / 2); pair++){
        int cnt = 0;        
        int lower = atoi(argv[2*pair + 1]);
        int upper = atoi(argv[2*pair + 2]);
        if (lower < upper){
            bool sumtr = false;
            bool fnd = false;
            for (int i = 0; i < Size; i++){
                if ((!sumtr) && (Data[i] == lower)){
                    sumtr = true;
                    fnd = true;
                }
                if (sumtr)
                    cnt += primes[Data[i]];
                if ((sumtr) && (Data[i] == upper)){
                    sumtr = false;
                    i = Size;
                }
            }
            if (sumtr){
                printf("0");
                return 0;
            }
            if (!fnd){
                printf("0");
                return 0;
            }
        }
        printf("%d\n", cnt);
    }
    
    return 0;
}
