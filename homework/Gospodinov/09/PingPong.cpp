#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable condition;

bool ping_ready(true);
const size_t count = 500000;

void ping()
{
	for (size_t i = 0; i < count; i++)
	{
		std::unique_lock<std::mutex> lk(m);
		condition.wait(lk, []() { return ping_ready; });
		std::cout << "ping" << std::endl;
		ping_ready = false;
		condition.notify_one();
	}
}

void pong()
{
	for (size_t i = 0; i < count; i++)
	{
		std::unique_lock<std::mutex> lk(m);
		condition.wait(lk, []() { return !ping_ready; });
		std::cout << "pong" << std::endl;
		ping_ready = true;
		condition.notify_one();
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