#include "numbers.dat"
#include <iostream>

int bin_search(const int Data[], int x, int left, int right);
bool isPrime(int n);

int main(int argc, char* argv[])
{
    int first = 0, last = 0, tmp = 0;
    if (argc < 3 || argc % 2 == 0) return -1;

    for (int k = 1; k < argc; k += 2)
    {
        int count = 0;
        first = bin_search(Data, std::atoi(argv[k]), 0, Size);
        last = bin_search(Data, std::atoi(argv[k + 1]), 0, Size);

        if (first == -1 || last == -1) return 0;

        for (int i = first; Data[i] == Data[first] && i >= 0; tmp = i, i--);
        first = tmp;
        for (int i = last; Data[i] == Data[last] && i <= Size; tmp = i, i++);
        last = tmp;

        for (int i = first; i <= last; i++)
            count += isPrime(Data[i]);
        std::cout << count << std::endl;
    }

    return 0;
}

bool isPrime(int n)
{
    if (n == 2 || n == 3) return true;
    if (n == 1 || n % 2 == 0 || n % 3 == 0) return false;

    int i = 5, c = 2;

    while (i * i <= n)
    {
        if (n % i == 0) return false;
        i += c;
        c = 6 - c;
    }

    return true;
}

int bin_search(const int Data[], int x, int left, int right)
{
    if (right >= left)
    {
        int mid = left + (right - left)/2;

        if (Data[mid] == x)
            return mid;

        if (Data[mid] > x)
            return bin_search(Data, x, left, mid-1);

        return bin_search(Data, x, mid + 1, right);
    }
    return -1;
}
