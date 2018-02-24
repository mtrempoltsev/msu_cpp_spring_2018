#include <iostream>
#include <chrono>
using namespace std;


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

int counter(int** data, const size_t N)
{

    int res1 = 0, res2 = 0;

    cout << "sum of columns:"<<endl;
    {
        Timer t1;
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < N; j++)
                res1 += data[i][j];
    }

    cout<<"sum of rows:"<<endl;
    {
        Timer t2;
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < N; j++)
                res2 += data[j][i];
    }
    return (res1 + res2)/2;
}

int** alloc2d_first(const size_t N)
{
    int** vector_2d;
    vector_2d = new int*[N];
    for (size_t i = 0; i < N; i++)
        vector_2d[i] = new int[N];
    for(size_t i = 0; i < N; i++)
        for(size_t j = 0; j < N; j++)
            vector_2d[i][j] = 1;
    return vector_2d;
}

int** alloc2d_second(const size_t N)
{
    int** vector_2d;
    vector_2d = (int**)malloc(N*sizeof(int*));
    for(size_t i = 0; i < N; i++)
        vector_2d[i] = (int*)malloc(N*sizeof(int));
    for(size_t i = 0; i < N; i++)
        for(size_t j = 0; j < N; j++)
            vector_2d[i][j] = 1;
    return vector_2d;
}

int** alloc2d_third(const size_t N)
{
    int** vector_2d;
    int* buff;
    vector_2d = (int**)malloc(N*sizeof(int*) + N*N* sizeof(int));
    buff = (int*)(vector_2d + N);
    for(size_t i = 0; i < N; i++)
        vector_2d[i] = buff + i*N;
    for(size_t i = 0; i < N; i++)
        for(size_t j = 0; j < N; j++)
            vector_2d[i][j] = 1;
    return vector_2d;
}

int* alloc_vector(const size_t N)
{
    int* vector;
    vector = new int[N*N];
    for(size_t i = 0; i < N*N; i++)
        vector[i] = 1;
    return vector;
}

int count_vector(int* v, const size_t N)
{
    int res = 0;
    cout<<"sum of vector:"<<endl;
    Timer t;
    for(size_t i = 0; i < N*N; i++ )
        res += v[i];

    return res;
}

int main(){
    const size_t N = 10000;
    int** vector_2d;
    vector_2d = alloc2d_first(N);
    counter(vector_2d, N);
    for (size_t i = 0; i < N; i++)
        delete[] vector_2d[i];
    delete[] vector_2d;
    cout<<endl;

    vector_2d = alloc2d_second(N);
    counter(vector_2d, N);
    for (size_t i = 0; i < N; i++)
         free(vector_2d[i]);
    free(vector_2d);
    cout<<endl;

    vector_2d = alloc2d_third(N);
    counter(vector_2d, N);
    free(vector_2d);
    
    cout<<endl;
    int* vector;
    vector = alloc_vector(N);
    count_vector(vector, N);
    delete[] vector;


    return 0;
}
