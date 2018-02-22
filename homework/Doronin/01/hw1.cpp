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

int counter(int** data)
{

    int res1 = 0, res2 = 0;

    cout << "sum of columns:"<<endl;
    Timer t1;
    for(int i = 0; i < 10000; i++)
        for(int j = 0; j < 10000; j++)
            res1 += data[i][j];


    cout<<"sum of rows:"<<endl;
    Timer t2;
    for(int i = 0; i < 10000; i++)
        for(int j = 0; j < 10000; j++)
            res2 += data[j][i];

    return (res1 + res2)/2;
}

int** alloc2d_first()
{
    int** vector_2d;
    vector_2d = new int*[10000];
    for (int i = 0; i < 10000; i++)
        vector_2d[i] = new int[10000];
    for(int i = 0; i < 10000; i++)
        for(int j = 0; j < 10000; j++)
            vector_2d[i][j] = 1;
    return vector_2d;
}

int** alloc2d_second()
{
    int** vector_2d;
    vector_2d = (int**)malloc(10000*sizeof(int*));
    for(int i = 0; i < 10000; i++)
        vector_2d[i] = (int*)malloc(10000*sizeof(int));
    for(int i = 0; i < 10000; i++)
        for(int j = 0; j < 10000; j++)
            vector_2d[i][j] = 1;
    return vector_2d;
}

int** alloc2d_third()
{
    int** vector_2d;
    int* buff;
    vector_2d = (int**)malloc(10000*sizeof(int*) + 10000*10000* sizeof(int));
    buff = (int*)(vector_2d + 10000);
    for(int i = 0; i < 10000; i++)
        vector_2d[i] = buff + i*10000;
    for(int i = 0; i < 10000; i++)
        for(int j = 0; j < 10000; j++)
            vector_2d[i][j] = 1;
    return vector_2d;
}

int* alloc_vector()
{
    int* vector;
    vector = new int[10000*10000];
    for(int i = 0; i < 10000*10000; i++)
        vector[i] = 1;
    return vector;
}

int count_vector(int* v)
{
    int res = 0;
    cout<<"sum of vector:"<<endl;
    Timer t;
    for(int i = 0; i < 10000*10000; i++ )
        res += v[i];
    return res;
}
int main(){

    int** vector_2d;
    vector_2d = alloc2d_first();
    counter(vector_2d);
    delete[] vector_2d;
    cout<<endl;

    vector_2d = alloc2d_second();
    counter(vector_2d);
    free(vector_2d);
    cout<<endl;

    vector_2d = alloc2d_third();
    counter(vector_2d);
    free(vector_2d);
    cout<<endl;

    count_vector(alloc_vector());

    return 0;
}
