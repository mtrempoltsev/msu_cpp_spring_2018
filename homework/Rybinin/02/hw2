#include <iostream>
#include "numbers.dat"
#define fr first
#define sc second

int main(int argc, char* argv[])
{
    //if (argc % 2 == 0 || argc == 1) return -1;
    std::pair<int, int> index[100010];
    int prost[100010] = {0,};
    for(int i = 0; i < 100000; ++i)
        index[i] = std::make_pair(0,0);
    for(int i = 0; i < Size; ++i){
        if(!index[Data[i]].fr)
            index[Data[i]].fr = i;
        index[Data[i]].sc = i;
    }
    for(long long i = 3; i < 100000; i += 2)
        for(long long j = i * i; j < 100000; j += 2 * i){
            prost[j] = 1;
        }
    for(int i = 2; i < 100000; i += 2)
        prost[i] = 1;
    for (int i = 1; i < argc; i += 2)
    {
        int start = std::atoi(argv[i]);
        int endd = std::atoi(argv[i+1]);
        if(!index[start].fr || !index[endd].sc)
        {
            return -1;
        }
        int cnt = 0;
        for(int j = index[start].fr; j <= index[endd].sc; ++j)
            if(!prost[Data[j]])
                ++cnt;
        std::cout << cnt << std::endl;
    }
    return 0;
}
