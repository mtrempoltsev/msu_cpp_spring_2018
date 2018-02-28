#include <iostream>
#include <ctime>
#include "numbers.dat"
/* MAYBE MAKE A LIST OF PRIMES??? */



int binary_search(int const arr[], int arr_sz, int needed);
int find_alike(int const arr[], int arr_sz, int pos, int dir);
int is_a_prime(int num);
int count_primes(int const arr[], int arr_sz, int low_i, int high_i);



int
main(int argc, char *argv[])
{
    // Data = huge arr with int numbers
    // Size = its size
    int start_num,  s_pos;
    int finish_num, f_pos;

    if(argc % 2) /* we require even number of arguments */
    {
        for (int i = 1; i < argc; i += 2)
        {
            start_num  = std::atoi(argv[i]);
            finish_num = std::atoi(argv[i + 1]);
            s_pos = binary_search(Data, Size, start_num);
            f_pos = binary_search(Data, Size, finish_num);

            if((s_pos == -1) || (f_pos == -1))
                printf("0: couldn't find one of specified numbers in array\n");
            else
            {
                s_pos = find_alike(Data, Size, s_pos, -1);
                f_pos = find_alike(Data, Size, f_pos, 1);
                if((s_pos == -1) || (f_pos == -1))
                    printf("ERROR: couldnt find alike (shouldnt see this error, probs wrong args)\n");
                else
                    count_primes(Data, Size, s_pos, f_pos);
            }
        }
    }
    else
        printf("-1: Wrong number of arguments\n");
    

/*
    size_t const NUM_ROWS = 100;
    int arr[NUM_ROWS];
    for (int i = 1; i < NUM_ROWS; i++)
        arr[i] = arr[i-1] + rand() % 5;




    for (int i=2; i<=1000; i++)
        if(is_a_prime(i)) std::cout << i << std::endl;*/
    return 0;
}




/* ========================OK=======================
 * Binary search.
 * Returns needed element's index in arr.
 * If doesn't find needed element, returns -1.
 * 
 * Takes - 1D sorted array(arr[]) + its size(arr_sz),
 *       - search borders(low, high),
 *       - number to search(needed).
 */
int
binary_search(int const arr[], int arr_sz, int needed_num)
{
    int mid, low = 0, high = arr_sz - 1;
    int curr_num;
    while(1)
    {
        mid = (low + high) / 2;
        curr_num = arr[mid];
        if(needed_num > curr_num)
            low  = mid + 1;
        else if(needed_num < curr_num)
            high = mid - 1;
        else return mid;

        if(low > high) return -1;
    }
}


/* ========================OK=======================
 * If dir  =  1, finds last element
 * equal to arr[pos] in arr[] and returns its index.
 * If dir  = -1, finds the first element
 * equal to arr[pos] in arr[] and returns its index.
 * arr[] must be a sorted array.
 */
int
find_alike(int const arr[], int arr_sz, int pos, int dir)
{
    int needed = arr[pos];
    if(pos >= arr_sz) return -1;
    do
        pos += dir;
    while ((pos < arr_sz) && (pos >= 0) && (arr[pos] == needed));
    return (pos - dir);
}

/* ========================OK=======================
 * Returns 1 if num is prime, 0 if num is NOT prime.
 * (checks from 2 to sqrt(num))
 */
int
is_a_prime(int num)
{
    if(num < 2)
        return 0;
    for(int i = 2; i*i <= num; i++)
       if(num % i == 0)
          return 0;
    return 1;
}



/* ========================OK=======================
 * Returns number of primes in interval of indexes
 * [low_i, high_i] for array arr[] of size arr_sz.
 */
int
count_primes(int const arr[], int arr_sz, int low_i, int high_i)
{
    int rez = 0;
    int curr = -1;
    int curr_is_prime;
    if((high_i >= arr_sz) || (low_i > high_i) || (low_i < 0)) {
        printf("ERROR in indexes: 0 <= %d <= %d < %d\n", low_i, high_i, arr_sz);
        return -1;
    }

    for(int i = low_i; i <= high_i; i++)
    {
        if(arr[i] != curr)
        {
            curr = arr[i];
            curr_is_prime = is_a_prime(curr);
        }
        rez += curr_is_prime;
        //if(curr_is_prime)
            //std::cout << arr[i] << std::endl;
    }
    printf("TOTAL: %d\n", rez);
    return rez;
}