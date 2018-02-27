#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer ()
        : start_ (std::chrono::high_resolution_clock::now ())
    {
    }

    ~Timer ()
    {
        const auto finish = std::chrono::high_resolution_clock::now ();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds> (finish - start_).count () << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int main () {
	int rows = 10000;
	int col = 10000;
	
	int** ary = (int**)malloc((rows * sizeof(int*)));
	for (int i = 0; i < rows; i++)
	  {
	    ary[i] = (int*)malloc(col * sizeof(int));
	  }  
	
	for (int i = 0; i < rows; i++)
	  {
		for (int j = 0; j < col; j++){
		  ary[i][j] = i+j;
		}
	  }
		
	long long sum = 0;
	{
		
        std::cout << "time - sum by rows: " << "\n";
		Timer time;
	    for (int i = 0; i < rows; i++){
		    for (int j = 0; j < col; j++){
			    sum +=ary[i][j];
		    }
		}
	}
	std::cout << "sum = " <<  sum <<"\n";
	
	{
		sum = 0;
		std::cout << "time - sum by rows: " << "\n";
		Timer time;
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < col; j++){
				sum +=ary[j][i];
			}
		}	
    }
    std::cout << "sum = " << sum << "\n";
    
    for (int i = 0; i < rows; i++) {
		free(ary[i]);
	}
	free(ary);
		
	
    system("pause");
    return 0;
}

