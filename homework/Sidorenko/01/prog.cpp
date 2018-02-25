#include<iostream>
#include<cstdlib>
#include"Timer.h"
#include"my_exception.h"
#include<new>

class My_mat
{
private:
    int **dat;
    size_t size;
    int iter_max;
public:
    My_mat(int _size, int _iter_max): size(_size), iter_max(_iter_max)
    {
        
        dat = new int* [size];
        if(dat == nullptr) 
        {
            throw my_exception(MEMORY_ERROR, "Memory error");
        }
        for(size_t i = 0; i<size; i++) 
        {
            dat[i] = new int [size];
            if(dat[i] == nullptr)
            {
                throw my_exception(MEMORY_ERROR, "Memory error");

            }
        }
        for(size_t i = 0; i<size; i++) 
        {
            for(size_t j = 0; j<size; j++) 
            {
                dat[i][j] = 1;
            }
        }
        
    }
    ~My_mat()
    {
        for(size_t i = 0; i<size; i++) delete [] dat[i];
        delete [] dat;
    }
    
    void quick_sum()
    {
        Timer t;
        for(int iter = 0; iter < iter_max; iter++) {
            volatile int sum = 0;
            for(size_t i = 0; i<size; i++)
            {
                for(size_t j = 0; j<size; j++)
                {
                    sum += dat[i][j];
                }
            }
        }
    }
    
    void slow_sum()
    {
        
        Timer t;
        for(int iter = 0; iter < iter_max; iter++) {
            volatile int sum = 0;
            for(size_t i = 0; i<size; i++)
            {
                for(size_t j = 0; j<size; j++)
                {
                    sum += dat[j][i];
                }
            }
        }
    }
};


void warm_up() 
{
    const int warming_iters = 1000*1000;
    for(int i = 0; i<warming_iters; i++)
    {
        volatile int a = i/3;
    }
}

int main() 
{
    const int mat_size = 10000;
    const int iter_max = 2;
    warm_up();
    {
        My_mat g(mat_size, iter_max);
        std::cout<<"\nslow_sum(): spent time = ";
        g.slow_sum();
        std::cout<<"\nquick_sum(): spent time = ";
        g.quick_sum();
    }
    std::cout<<"\n";
    return 0;
}

        
    
