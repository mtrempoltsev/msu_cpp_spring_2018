#include <iostream>
#include <thread>
#include<atomic>
#include <mutex>
const std::uint32_t MAX = 1000000;
std::atomic<int> i(0);
std::mutex mutex;
std::condition_variable ready;

void ping()
{
	std::unique_lock<std::mutex> lock(mutex);
	while (i < MAX)
	{
		while (i % 2 == 1)
			ready.wait(lock);
		std::cout << "ping" << std::endl;
		i++;
		ready.notify_one();
	}
}


void pong()
{
	std::unique_lock<std::mutex> lock(mutex);
	while (i < MAX+1)//чтобы красиво на pong заканчивалось
	{
		while (i % 2 == 0)
			ready.wait(lock);
		std::cout << "pong" << std::endl;
		i++;
		ready.notify_one();
	}
}

int main() 
{
	std::thread t1(ping);
	std::thread t2(pong);
	t1.join();
	t2.join();
	return 0;
}
