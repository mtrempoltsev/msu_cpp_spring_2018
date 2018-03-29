#include <iostream>
#include <cmath>

#include "numbers.dat"

using namespace std;

bool is_prime_number(int num) {

    if (num == 1)
    {
        return false;
    }
    else if (num == 2)
    {
        return true;
    }
    else if(num % 2 == 0)
    {
        return false;
    }

    int sqrt_num = (int)sqrt(num) + 1;

    for (int i = 3; i <= sqrt_num; i=i+2)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

int find_prime_numbers(int start, int end) {

    int n = 0, c = -1, i = start;

    while (i <= end) {

        if (c == Data[i])
        {
            ++i;
            ++n;
            continue;
        }
        else if (is_prime_number(Data[i]))
        {
            ++n;
            c = Data[i];
        }

        ++i;
    }

    return n;
}

int index_start(int start)
{
    int i = 0;

    while(i < Size)
    {
        if(Data[i] >= start)
        {
            return i;
        }
        ++i;
    }

    return -1;
}

int index_end(int end)
{
    int i = 0;

    if(end == Data[Size-1])
    {
        return Size-1;
    }

    while(i < Size)
    {
        if(Data[i] > end)
        {
            return i-1;
        }
        ++i;
    }

    return -1;
}

int main(int argc, char* argv[])
{

    int start = 0, end = 0;

    if (argc < 3 || !(argc & 1))
    {
        return -1;
    }

    for (int i = 1; i < argc; i = i + 2)
    {

        if(atoi(argv[i]) > atoi(argv[i+1]))
        {
            cout << 0 << endl;
            continue;
        }

        start = index_start(atoi(argv[i]));
        end = index_end(atoi(argv[i+1]));

        if (start >= 0 && end >= 0)
        {
            cout << find_prime_numbers(start, end) << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }

    return 0;
}
