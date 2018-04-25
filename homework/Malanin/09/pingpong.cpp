#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>



namespace ourdata
{
	constexpr int max = 1000000;
}

std::mutex mutex;
std::condition_variable f;
bool flag_is_already_ping = false;

void printPing()
{
	std::unique_lock<std::mutex> lock(mutex);	
	for (int i = 0; i < ourdata::max; i++)
	{
		std::cout << "ping" << std::endl;
		flag_is_already_ping = true;
		f.notify_one();
		f.wait(lock);		
	}
}

void printPong()
{
	std::unique_lock<std::mutex> lock(mutex);	
	for (int i = 0; i < ourdata::max; i++)
	{			
        if (flag_is_already_ping)
		std::cout << "pong" << std::endl;		
		f.notify_one();
		f.wait(lock);
	}
}

int main()
{
	std::thread t1(printPing);	
	std::thread t2(printPong);
	t1.join();
	t2.join();
	return 0;
}
