#include <iostream>
#include <stdio.h>

#include "numbers.dat"
// Data - array
// Size - size of Data

bool* sieve(const unsigned max_val)
{
    bool* prime = new bool [max_val + 1];
    
    
    prime[0] = prime[1] = false;
    
    for (unsigned i = 2; i <= max_val; ++i) {
        prime[i] = true;
    }
    
    for (unsigned i = 2; i <= max_val; ++i)
    {
        if (prime[i]) {
            for (unsigned j = i * i; j <= max_val; j += i) {
                prime[j] = false;
            }
        }
    }
    
    return prime;
}

// function returns true if input is correct
bool sscanfOfArgv(int argc, char* argv[], unsigned* &begin, unsigned* &end)
{
    begin = new unsigned [argc / 2];
    end = new unsigned [argc / 2];
    size_t sscanfReturnCounter = 0;
    size_t j = 0;
    
    for (int i = 1; i < argc; i += 2) {
        sscanfReturnCounter += sscanf(argv[i], "%u", begin + j)
        + sscanf(argv[i + 1], "%u", end + j);
        ++j;
    }
    
    return sscanfReturnCounter == argc - 1;
}

unsigned maxValFromArr(const unsigned* arr, const int& N)
{
    auto max_val = arr[0];
    for (int i = 1; i < N; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    return max_val;
}

int main(int argc, char* argv[])
{
    unsigned* begin = nullptr;
    unsigned* end = nullptr;
    
    
    if (argc == 1 || argc % 2 != 1 || !sscanfOfArgv(argc, argv, begin, end))
    {
        std::cout <<
        "Usage: " <<
        argv[0] << " <begin_1> <end_1> <begin_2> <end_2> ..." <<
        "\nExamples: " << std::endl <<
        argv[0] << " 10 99" << std::endl <<
        argv[0] << " 1 88 100 200" << std::endl <<
        argv[0] << " 0 99 10000 10 20 200000" << std::endl;
     
        if (!begin) {
            delete[] begin;
        }
        
        if (!end) {
            delete[] end;
        }
        
        return -1;
    }
    
    auto prime = sieve(maxValFromArr(end, argc / 2));
    
    for (int i = 0; i < argc / 2; ++i) {
        if (begin[i] > end[i]) {
            std::cout << 0 << std::endl;
            continue;
        }
        
        unsigned prime_counter = 0;
        for (unsigned j = 0; j < Size; ++j) {
            if (Data[j] >= begin[i] && Data[j] <= end[i] && prime[Data[j]]) {
                ++prime_counter;
            }
        }
        
        std::cout << prime_counter << std::endl;
    }
    
    delete [] prime;
    delete [] begin;
    delete [] end;
    
    return 0;
}
