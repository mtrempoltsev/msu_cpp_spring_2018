#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> ping_ready(true);
const size_t count = 500000;

void ping()
{
	for (size_t i = 0; i < count; i++)
	{
		while (!ping_ready);
		std::cout << "ping" << std::endl;
		ping_ready = false;
	}
}

void pong()
{
	for (size_t i = 0; i < count; i++)
	{
		while (ping_ready);
		std::cout << "pong" << std::endl;
		ping_ready = true;
	}
}

int main()
{
	std::thread ping_thread(ping);
	std::thread pong_thread(pong);
	ping_thread.join();
	pong_thread.join();
	return 0;
}