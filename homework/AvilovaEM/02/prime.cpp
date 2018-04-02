#include<iostream>
#include"numbers.dat"

// Data -- массив
// Size -- размер

size_t binary_search(const int* arr, size_t n, int k, bool bl)
{
    size_t left = 0;
    size_t right = n;
    int mid = 0;
    
    while(left <= right)
    {
        mid = (left+right)/2;
        if(k == arr[mid])
        {
            if(bl)
            {
                while(k == arr[mid])   
                    --mid;
                if(mid == -1)
                    return 0;
                return (mid+1);
            }
            else
            {
                while(k == arr[mid])
                    ++mid;
                if(mid == Size)
                    return Size-1;    
                return (mid-1);
            }
        }
        if(k < arr[mid])
            right = mid-1;
        else
            left = mid+1;        
    }
    return -1; 
}

bool is_prime(size_t n)
{
    size_t i = 2;
    if(n == 1)
        return false;        
    while(1)
    {
        if(i*i > n)
            return true;
        if(n % i == 0)
            return false;
        ++i;            
    }
}

bool* array_of_primes(const size_t size, bool* arr_prime)
{
    for(size_t i = 0; i < size; ++i)
        arr_prime[i] = is_prime(i);            
        
    return arr_prime;        
}

size_t count_of_primes(bool* arr_prime, size_t left, size_t right)
{
    size_t count = 0;
    for(size_t i = left; i < right; ++i)
        if(arr_prime[Data[i]] == true)
            count++;

    return count;
}

int main(int argc, char* argv[])
{
    size_t num_left = 0;
    const size_t size = 100000;
    bool* arr_prime = new bool [size];
    size_t num_right = 0;
    size_t left = 0;
    size_t right = 0;
    size_t count = 0;

    arr_prime = array_of_primes(size, arr_prime);

    if(argc%2 == 0 || argc < 3)
        return -1;
        
    for (int i = 1; i < argc-1; i += 2)
    {

        num_left = std::atoi(argv[i]);
        num_right  = std::atoi(argv[i+1]);
        
        if(num_left > num_right)
        {
            std::cout << 0;
            return 0;
        }

    
       left = binary_search(Data, Size, num_left, 1);
        right = binary_search(Data, Size, num_right, 0);
            
        count = count_of_primes(arr_prime, left, right);
        std::cout << count << std::endl; 
    }

    free(arr_prime);    

    return 0;
}
