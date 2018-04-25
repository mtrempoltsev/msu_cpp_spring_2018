#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace options
{
	constexpr int max = 500000;
}

std::mutex m;
std::condition_variable flag;

void printPing()
{
	std::unique_lock<std::mutex> lock(m);
	for (int i = 0; i < options::max; i++)
	{
		std::cout << "ping" << std::endl;
		flag.notify_one();
		flag.wait(lock);
	}
}

void printPong()
{
	std::unique_lock<std::mutex> lock(m);
	for (int i = 0; i < options::max; i++)
	{
		std::cout << "pong" << std::endl;
		flag.notify_one();
		flag.wait(lock);
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
