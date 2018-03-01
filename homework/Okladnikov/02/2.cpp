//
//  main.cpp
//  HW-2-C++
//
//  Created by Сергей Окладников on 28/02/2018.
//  Copyright © 2018 Сергей Окладников. All rights reserved.
//

#include <iostream>
#include "numbers.dat"

const int MAX_N = 100005;
bool spl[MAX_N]; //массив простых чисел

void find_prime_nums()
{
    spl[0] = spl[1] = true;
    for (int i = 2; i <= MAX_N; i++)
    {
        if (!spl[i]) {
            for (int j = 2 * i; j < MAX_N; j += i)
                spl[j] = true;
        }
    }
}

int find_l(int x)
{
    int l = 0, r = Size, m;
    while (r - l > 1)
    {
        m = (l + r) / 2;
        
        if (Data[m] >= x)
            r = m;
        else
            l = m;
    }
    if (Data[l] == x)
        return l;
    if (Data[r] == x)
        return r;
    return -1;
}

int find_r(int x)
{
    int l = 0, r = Size, m;
    while (r - l > 1)
    {
        m = (l + r) / 2;
        
        if (Data[m] <= x)
            l = m;
        else
            r = m;
    }
    if (Data[l] == x)
        return l;
    if (Data[r] == x)
        return r;
    return -1;
}

int main(int argc, char* argv[])
{
    if (!(argc & 1) || argc == 1)
        return -1;
    
    find_prime_nums();
    
    int l, r, l_pos, r_pos, ans;
    for (int i = 1; i < argc; i += 2)
    {
        l = std::atoi(argv[i]);
        r = std::atoi(argv[i + 1]);
        
        l_pos = find_l(l);
        r_pos = find_r(r);
        
        if (l_pos == -1 || r_pos == -1)
            continue;
        
        ans = 0;
        for (int j = l_pos; j <= r_pos; ++j)
            ans += !spl[Data[j]];
        
        std::cout << ans << std::endl;
    }
    
    return 0;
}
