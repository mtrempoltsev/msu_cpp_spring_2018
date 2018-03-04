//
//  main.cpp
//  HW-1-C++
//
//  Created by Сергей Окладников on 24/02/2018.
//  Copyright © 2018 Сергей Окладников. All rights reserved.
//

#include <iostream>
#include <chrono>

class Timer
{
public:
    Timer()
    : start_(std::chrono::high_resolution_clock::now())
    {
    }
    
    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }
    
private:
    const std::chrono::high_resolution_clock::time_point start_;
};

void cnt_string(int **a, int N)
{
    std::cout << "Summuring by rows: ";
    int s = 0;
    
    Timer t;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            s += a[i][j];
        }
    }
}

void cnt_colomn(int **a, int N)
{
    std::cout << "Summuring by colomn: ";
    int s = 0;
    
    Timer t;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            s += a[j][i];
        }
    }
}

int main()
{
    const int N = 10000;
    
    int **a = new int *[N];
    for (int i = 0; i < N; i++)
    {
        a[i] = new int [N];
    }
    
    cnt_string(a, N);
    cnt_colomn(a, N);
    
    for (int i = 0; i < N; i++)
        delete []a[i];
    
    delete []a;
    
    return 0;
}
