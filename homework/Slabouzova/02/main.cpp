#include "numbers.dat"
#include "primes.dat"
#include <iostream>

int main(int argc, char* argv[])
{

    if (argc % 2 == 0)
        return -1;

    for (int k = 1; k < argc; k += 2) {
        int a = std::atoi(argv[k]);
        int b = std::atoi(argv[k+1]);

        int i;
        for (i = 0; i < Size; i++) {
            if (Data[i] == a)
                break;
        }

        if (i == Size) {
            std::cout << 0 << std::endl;
            return 0;
        }

        int count = 0;
        for (; i < Size; i++) {            
            if (Primes[Data[i]])
                count++;
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
