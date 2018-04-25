#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable ready;

void ping()
{
	std::unique_lock<std::mutex> lock(mutex);
	for (int i = 0; i < 10; i++)
	{
		std::cout << "ping" << std::endl;
		ready.notify_one();
		ready.wait(lock);
	}
	ready.notify_one();
}

void pong()
{
	std::unique_lock<std::mutex> lock(mutex);
	for (int i = 0; i < 10; i++)
	{
		std::cout << "pong" << std::endl;
		ready.notify_one();
		ready.wait(lock);
	}
	ready.notify_one();
}

int main() 
{
	std::thread t1(ping);
	std::thread t2(pong);
	t1.join();
	t2.join();
	return 0;
}
