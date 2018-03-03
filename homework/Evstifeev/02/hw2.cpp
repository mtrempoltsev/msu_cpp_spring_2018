#include <iostream>
#include "numbers.dat"

int binary_search(const int* array, int number, int size, bool find_first_index)
{
        int left_bound = 0, mid = 0, right_bound = size - 1, result = -1;
        while(left_bound <= right_bound)
        {
                mid = (left_bound + right_bound) / 2;
                int cur_number = array[mid];
                if (cur_number == number)
                {
                        result = mid;
                        //to find left most and right most element
                        if (find_first_index) right_bound = mid - 1;
                        else left_bound = mid + 1;
                }
                else if (number > cur_number)
                        left_bound = mid + 1;
                else if (number < cur_number)
                        right_bound = mid - 1;
        }
        return result;
}

bool* make_sieve(size_t n)
{
        bool* primes = new bool[n];
        primes[0] = primes[1] = false;
        for (size_t i = 2; i < n; i++) {
                primes[i] = true;
        }
        for (size_t i = 2; i * i < n; i++) {
                if (primes[i])
                {
                        for (size_t j = 2 * i; j < n; j += i) {
                                if (j % i == 0) primes[j] = false;
                        }
                }
        }
        return primes;
}

int main(int argc, char* argv[])
{
        if (argc % 2 == 0 || argc == 1) return -1;
        const size_t sieve_n = 100000;
        const bool* sieve = make_sieve(sieve_n);
        for (int i = 1; i < argc; i+=2) {
                int prime_count = 0;
                int start_index = binary_search(Data, std::atoi(argv[i]), Size, true);
                int end_index = binary_search(Data, std::atoi(argv[i+1]), Size, false);
                if (start_index == -1 || end_index == -1)
                {
                        return -1;
                }
                for (int i = start_index; i <= end_index; i++) {
                        if (sieve[Data[i]])
                                prime_count += 1;
                }
                std::cout << prime_count << std::endl;
        }
}
