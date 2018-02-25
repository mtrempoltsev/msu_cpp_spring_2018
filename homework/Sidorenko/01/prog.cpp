#include<iostream>
#include<chrono>
#include<cstdlib>

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


class My_mat
{
private:
    int **dat;
    size_t size;
public:
    My_mat(int _size)
    {
        size = _size;
        dat = (int**)malloc(sizeof(int*)*size);
        if(dat == nullptr) 
        {
            throw "Memory error";
        }
        for(size_t i = 0; i<size; i++) 
        {
            dat[i] = (int*)malloc(sizeof(int)*size);
            if(dat[i] == nullptr)
            {
                throw "Memory error";
            }
        }
        for(size_t i = 0; i<size; i++) 
        {
            for(size_t j = 0; j<size; j++) 
            {
                dat[i][j] = 0;
            }
        }
        
    }
    ~My_mat()
    {
        for(size_t i = 0; i<size; i++) free(dat[i]);
        free(dat);
    }
    
    void quick_sum()
    {
        Timer t;
        for(int iter = 0; iter < 1000; iter++) {
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
        for(int iter = 0; iter < 1000; iter++) {
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
    for(int i = 0; i<1000*1000; i++)
    {
        volatile int a = i/3;
    }
}

int main() 
{
    warm_up();
    My_mat g(1000);
    std::cout<<"\nslow_sum(): spent time = ";
    g.slow_sum();
    std::cout<<"\nquick_sum(): spent_time = ";
    g.quick_sum();
    std::cout<<"\n";
    
    return 0;
}

        
    