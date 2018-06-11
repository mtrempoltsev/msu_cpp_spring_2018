#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
std::mutex mtx;
std::condition_variable cv;
constexpr size_t MAX_ITER = 500000;
bool ping=true;

void Ping()
{
	for(int i=0; i<MAX_ITER; i++)
	{
		std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() {return ping;});
		std::cout << "ping" << std::endl;
		ping=false;
		cv.notify_one();
	}
}
void Pong()
{
	for(int i=0; i<MAX_ITER; i++)
	{
		std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() {return !ping;});
		std::cout << "pong" << std::endl;
		ping=true;
		cv.notify_one();
	}
}
int main()
{
    std::thread t1(Ping);
    std::thread t2(Pong);
    
    t1.join();
    t2.join();
    return 0;
}
