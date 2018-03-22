#include <chrono>
#include <iostream>

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
void sbr(int32_t **, int);
void sbc(int32_t **, int);
void sbr(int32_t **m, int size)
{
	int32_t res;
	Timer t;
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			res+=m[i][j];
		}
	}
	if(res)
	{
		res++;
	}
}
void sbc(int32_t **m, int size)
{
	int32_t res;
	Timer t;
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			res+=m[j][i];
		}
	}
	if(res)
	{
		res++;
	}
}

int main(int argc, char **argv)
{
	const int size=1000;
	int32_t res;
	int32_t *mat= new int32_t[size*size];
	int32_t **m= new int32_t*[size];
	for(int i=0; i<size; i++)
	{
		m[i]=mat+i*size;
	}
	sbr(m, size);
	sbc(m, size);
	delete []mat;
	delete []m;
	return 0;
}
