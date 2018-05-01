#include<thread>
#include<iostream>
#include <mutex>
#include <condition_variable>
std::mutex m;
std::condition_variable cond_var;
bool notified = true;
void thread(bool first)
{
	for (int i = 0; i < 500000; i++)
	{
		std::unique_lock<std::mutex> lock(m);
		cond_var.wait(lock, [first]() {return first ? notified == true : notified != true; });
		first ? std::cout << "ping" << std::endl : std::cout << "pong" << std::endl;
		notified = first ? false : true;
		cond_var.notify_one();
	}
}
int main()
{
	std::thread t1(thread, true);
	std::thread t2(thread, false);
	t1.join();
	t2.join();
}
