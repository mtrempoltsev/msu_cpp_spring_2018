#include <iostream>
#include "numbers.dat"

int binary_search(int const arr[], int arr_sz, int needed_num);
int find_alike(int const arr[], int arr_sz, int pos, int dir);
void init_eratosthenes_mask(bool mask[], int mask_sz);

int
main(int argc, char *argv[])
{
    /* Note: Data[] and Size loaded from "numbers.dat" */
    int start_num,  s_pos;
    int finish_num, f_pos;

    /* Create and init mask that will tell us which numbers are prime */
    const int max_num = Data[Size - 1];
    bool * primes_mask = new bool[max_num];
    if (!primes_mask)
        return -1;
    init_eratosthenes_mask(primes_mask, max_num);

    /* we require an even number of arguments */
    if ((argc % 2) && (argc > 1))
    {
        /* looping through pairs of arguments */
        for (int i = 1; i < argc; i += 2)
        {
            start_num  = std::atoi(argv[i]);
            finish_num = std::atoi(argv[i + 1]);
            /* if impossible interval, print 0 and skip */
            if (start_num > finish_num)
            {
                printf("0\n");
                continue;
            }

            /* searching indexes of specified numbers */
            s_pos = binary_search(Data, Size, start_num);
            f_pos = binary_search(Data, Size, finish_num);

            /* if indexes don't meet this: 0 <= s_pos <= f_pos < Size,
               then print out 0 and don't do any further calculations */
            if ((f_pos >= Size) || (s_pos > f_pos) || (s_pos < 0))
                printf("0\n");
            else
            {
                /* widening the interval */
                s_pos = find_alike(Data, Size, s_pos, -1);
                f_pos = find_alike(Data, Size, f_pos, 1);
                int rez = 0;
                for (int i = s_pos; i <= f_pos; i++)
                    rez += primes_mask[Data[i]];
                printf("%d\n", rez);
            }
        }
        delete [] primes_mask;
        return 0;
    }
    else
    {
        delete [] primes_mask;
        return -1;
    }
}

/* binary_search()
 * Returns needed element's index in arr.
 * If doesn't find needed element, returns -1.
 * Takes - 1D sorted array(arr[]) + its size(arr_sz),
 *       - number to search(needed_num).
 */
int
binary_search(int const arr[], int arr_sz, int needed_num)
{
    int mid, low = 0, high = arr_sz - 1;
    int curr_num;
    while (1)
    {
        mid = (low + high) / 2;
        curr_num = arr[mid];
        if (needed_num > curr_num)
            low  = mid + 1;
        else if (needed_num < curr_num)
            high = mid - 1;
        else
            return mid;

        if (low > high) return -1;
    }
}

/* find_alike()
 * If dir  =  1, finds LAST element equal to arr[pos]
 * If dir  = -1, finds FIRST element equal to arr[pos]
 * in 1D sorted array arr[] and returns its index.
 */
int
find_alike(int const arr[], int arr_sz, int pos, int dir)
{
    if ((pos >= arr_sz) || (pos < 0))
        return -1;

    int needed_num = arr[pos];
    do
        pos += dir;
    while ((pos < arr_sz) && (pos >= 0) && (arr[pos] == needed_num));
    return (pos - dir);
}

/* init_eratosthenes_mask()
 * mask[i] = true  if i is a prime
 * mask[i] = false if i is NOT a prime
 * mask_sz should be >= 2
 * 
 * NOTE: idea to use it was taken from BD-11 TELEGRAM CHAT
 * For my original solution see the following commit:
 * 377121ee00611f781ddf3725a08b9f303a93d2f4
 */
void init_eratosthenes_mask(bool mask[], int mask_sz)
{
    for (int i = 0; i < mask_sz; i++)
        mask[i] = true;
    mask[0] = mask[1] = false;
    for (int i = 2; i <= mask_sz; i++)
        if (mask[i] && (i * 1ll * i <= mask_sz))
            for (int j = i*i; j <= mask_sz; j += i)
                mask[j] = false;
}
