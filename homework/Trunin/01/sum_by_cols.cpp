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

int main(){
	int size_y = 10000;
	int size_x = 10000;
	
	int** tdarray = new int*[size_y]; 
	
	for(int i = 0; i < size_y; i++){
		tdarray[i] = new int[size_x];
	}
	
	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			tdarray[i][j] = 2;
		}
	}
	
	int sum = 0;
	Timer* t = new Timer();
	for(int i = 0; i < size_y; i++){
		for(int j = 0; j < size_x; j++){
			sum += tdarray[j][i];
		}
	}
	delete t;
	cout << sum << endl;

}
