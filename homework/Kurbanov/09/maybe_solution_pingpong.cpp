#include <iostream>
#include <thread>
#include<atomic>
const std::uint32_t MAX = 1000000;
std::atomic<int> i(0);
void ping()
{
	while (i != 2*MAX)
	{
		if (i % 2 == 0) 
		{
			std::cout << "ping" << std::endl;
			i++;
		}
	}
}


void pong()
{
	while (i != 2*MAX)
	{
		if (i % 2 == 1)
		{
			std::cout << "pong" << std::endl;
			i++;
		}
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
