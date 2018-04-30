#include<thread>
#include<iostream>
#include <atomic>
std::thread::id* first = nullptr;
std::atomic<bool> checker(true);
void thread()
{
	std::thread::id this_id = std::this_thread::get_id();
	if (first == nullptr)
	{
		first = new std::thread::id();
		*first = this_id;
	}
	for (int i = 0; i < 500000; i++)
	{
		if (this_id == *first)
		{
			while (!checker);
			std::cout << "ping" << std::endl;
			checker = false;
		}
		else
		{
			while (checker);
			std::cout << "pong" << std::endl;
			checker = true;
		}
	}
	delete first;
	first = nullptr;
}
int main()
{
	std::thread t1(thread);
	std::thread t2(thread);
	t1.join();
	t2.join();
}