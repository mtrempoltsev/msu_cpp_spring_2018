#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include "numbers.dat"

bool prime(int);
int lower(int);
int upper(int);
bool check(int, int);

int _size = sizeof(Data) / sizeof(int);
int counter = 0;

bool check(int a, int b)
{
    return (a > b || std::min(a,b) < 0 || std::max(a,b) > 100000 );
}

bool prime(int a)
{
   int i;
   if (a == 2)  return 1;
   if (a == 0 || a == 1 || a % 2 == 0)  return 0;
   for(i = 3; i*i <= a && a % i; i += 2) ;
   return i*i > a;
}

int lower(int a)
{
    int l = 0, r = _size - 1;

    while (l < r)
    {
        int m = l + (r-l)/2;
        if (Data[m] >= a)
            r = m;
        else
            l = m + 1;
    }
    return Data[l] == a ? l : -1;
}

int upper(int a)
{
      int l = 0, r = _size - 1;
      while (l < r)
      {
        int m = r - (r - l)/2;
        if (Data[m] <= a)
          l = m;
        else
          r = m - 1;
      }
      return Data[l] == a ? l : -1;
}

void process(int l, int r)
{
    while (l <= r)
    {
        if (prime( Data[l] ) )
        {
            do
            {
                counter++;
                l++;
            }
            while (l <= r && Data[l] == Data[l-1]);
        }
        else
        {
            do
            {
                l++;
            }
            while (l <= r && Data[l] == Data[l-1]);
        }
    }
}



int main(int argc, char* argv[])
{
    int i, a_index, b_index;

    if (argc == 1 || (argc % 2 == 0) ) return -1;

    std::vector<std::pair<int, int> > v(1);

    for (i = 0; i < (argc - 1) / 2; ++i)
    {
        v[i].first = std::atoi(argv[2*i+1]);
        v[i].second = std::atoi(argv[2*i+2]);

        if (check(v[i].first, v[i].second)) return -1;
    }

    for (i = 0; i < (argc - 1) / 2; ++i)
    {
        a_index = lower(v[i].first);
        b_index = upper(v[i].second);
        if ( a_index == -1 || b_index == -1)
            std::cout << 0 << ' ';
        else
        {
            process(a_index, b_index);
            std::cout << counter << std::endl;
            counter = 0;
        }
    }
    return 0;
}
