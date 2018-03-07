#include <iostream>
#include "numbers.dat"

int main(int argc, char* argv[])
{
    if (argc % 2 == 0 || argc == 1) return -1;
    int index[100010] = {0,};
    int prost[100010] = {0,};
    for(int i = 0; i < Size; ++i)
        if(!index[Data[i]])
            index[Data[i]] = i + 1;
    for(long long i = 3; i * i <= 100000; i += 2)
        for(long long j = i * i; j <= 100000; j += 2 * i)
            prost[j] = 1;
    for(int i = 4; i <= 100000; i += 2)
        prost[i] = 1;
    prost[1] = 1;
    for (int i = 1; i < argc; i += 2)
    {
        int start = std::atoi(argv[i]);
        int endd = std::atoi(argv[i+1]);
        if(!index[start] || !index[endd] || index[start] > index[endd]){
            std::cout << 0 << std::endl;
            continue;
        }
        int cnt = 0;
        for(int j = index[start] - 1; j < index[endd]; ++j)
            if(!prost[Data[j]])
                ++cnt;
        std::cout << cnt << std::endl;
    }
    return 0;
}
