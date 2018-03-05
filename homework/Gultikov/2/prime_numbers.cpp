#include <iostream>
#include "numbers.dat"

int binary_s(int val, const int *m, int Size)
{
    int left = 0, right = Size - 1;
    while(1)
    {
        if (left >= right)
        {
            return m[left] == val ? left : -1;
        }

        int mid = (left + right) / 2;
        if (m[mid] == val)
            return mid;
        if (m[mid] < val)
            left = mid + 1;
        else
            right = mid -1;
    }
}

void Eratosthenes_sieve(int Size, bool* sieve)
{
    sieve[0] = sieve[1] = false;
	for (int i = 0; i <= Size; i++)
	{
		if (sieve[i])
		{
			if (i * 1ll * i <= Size)
			{
				for (int j = i * i; j <= Size; j += i)
					sieve[j] = false;
			}
		}
	}
}

int main(int argc, char* argv[])
{
    if( argc % 2 == 0 || argc == 1)
    {
        return -1;
    }

    int num = (argc - 1)/2;
    int *left = new int[num];
    int *right = new int[num];

    bool *sieve = new bool[Data[Size - 1] + 1];
    for(int i = 0; i <= Data[Size - 1]; ++i)
    {
        sieve[i] = true;
    }
    Eratosthenes_sieve(Data[Size - 1], sieve);

    for (int i = 0; i < num; ++i)
    {
        left[i] = std::atoi(argv[2*i + 1]);
        right[i] = std::atoi(argv[2*i + 2]);
        int left_ind = binary_s(left[i], Data, Size);
        int right_ind = binary_s(right[i], Data, Size);

        if(left_ind == -1 || right_ind == -1 )
        {
            return 0;
        }

        while(left_ind > 0 && Data[left_ind - 1] == left[i])
			left_ind--;
		while(right_ind < Size - 1 && Data[right_ind + 1] == right[i])
			right_ind++;

        int c = 0;
        for(int i = left_ind; i<= right_ind; ++i)
        {
            if(sieve[Data[i]])
                ++c;
        }
        std::cout<<c<<std::endl;
    }
return 0;
}
