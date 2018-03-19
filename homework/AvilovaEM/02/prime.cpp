#include<iostream>
#include<vector>
#include"numbers.dat"

// Data -- массив
// Size -- размер
 
int binary_search(const int* arr, int n, int k, bool bl)
{
    int left = 0;
    int right = n;
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

int is_prime(int n)
{
    int i = 2;
    if(n == 1)
        return 1;
    if(n == 0)
        return 1;    
    while(1)
    {
        if(n % i == 0)
            return 0;
        else
            if(i*i >= n)
                return 1;
        ++i;            
    }
}

int* array_of_primes(void)
{
    int* arr_prime = new int [100000];
    
    for(int i = 0; i < 100000; ++i)
        arr_prime[i] = is_prime(i);            
        
    return arr_prime;        
}

int count_of_primes(int* arr_prime, int left, int right)
{
    int count = 0;
    for(int i = left; i < right; ++i)
        if(arr_prime[Data[i]] == 1)
            count++;
    
    return count;
}

int main(int argc, char* argv[])
{
    int num_left = 0;
    int num_right = 0;
    int left = 0;
    int right = 0;
    int count = 0;
    int sum = 0;
    int* arr_prime = array_of_primes();

    if(argc%2 == 0 || argc < 3)
        return -1;
        
    for (int i = 1; i < argc-1; i += 2)
    {

        num_left = std::atoi(argv[i]);
        num_right  = std::atoi(argv[i+1]);
        
        if(num_left > num_right)
        {
            std::cout << 0 << std::endl;
            return 0;
        }

    
        left = binary_search(Data, Size, num_left, 1);
        right = binary_search(Data, Size, num_right, 0);
        if(left == -1 || right == -1)
            return 0;
            
        count = count_of_primes(arr_prime, left, right);
        sum += count;
    }

    free(arr_prime);    
    std::cout << sum << std::endl; 
    

    return 0;
}
