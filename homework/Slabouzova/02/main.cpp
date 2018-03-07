#include "numbers.dat"
#include <iostream>
#include <cmath>

bool is_prime(int val)
{
    int sqrt_val = trunc(sqrt(val));
    for (int i = 2; i <= sqrt_val; i++) {
        if (!(val % i)) {
            return false;
        }
    }
    return true;
};

int main(int argc, char* argv[])
{

    if (argc % 2 == 0 || argc == 1) {
        return -1;
    }

    for (int k = 1; k < argc; k += 2) {
        int a = std::atoi(argv[k]);
        int b = std::atoi(argv[k+1]);

        int i;
        for (i = 0; i < Size; i++) {
            if (Data[i] == a)
                break;
        }
        // if a is not found
        if (i == Size) {
            std::cout << 0 << std::endl;
            return 0;
        }
        // for skipping all ones
        for (; i < Size; i++) {
            if (Data[i] == 1)
                continue;
            else
                break;
        }


        int count = 0;
        int prev_val = -1; // remember previous value 
        int prev_val_is_prime = 0; // and if it's prime
        for (; i < Size; i++) {
            
            if (Data[i] == prev_val)
                count += prev_val_is_prime;
            else { 
                prev_val = Data[i];                         
                if (is_prime(Data[i])) {
                    prev_val_is_prime = 1;
                    count++;
                } else {
                    prev_val_is_prime = 0;
                }
            }
            if (Data[i] == b) 
                break;
        }    

        if (i == Size) {
            std::cout << 0 << std::endl;
            return 0;
        }
        std::cout << count << std::endl;
    }
    return 0;
}
