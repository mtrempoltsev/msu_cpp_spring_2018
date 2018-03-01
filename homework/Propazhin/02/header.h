#pragma once

int bin_search(const int Data[], int x, int left, int right);
bool IsPrime(int n);

bool IsPrime(int n)
{
    if (n <= 2) return false;
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return false;
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

