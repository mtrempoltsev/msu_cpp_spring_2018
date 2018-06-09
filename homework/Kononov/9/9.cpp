// Kononov Sergey BD-11

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const int iteration_count = 500000;
int  current_iteration = 0;

std::mutex mutex;
std::condition_variable cond_var;

void Ping() {
	while (current_iteration < 2 * iteration_count - 1) {
	{
		std::unique_lock<std::mutex> lock(mutex);
		while (current_iteration % 2 == 1)
			cond_var.wait(lock);
		std::cout << "ping\n";
		current_iteration++;
	}
	cond_var.notify_one();
	}
};

void Pong() {
	while (current_iteration < 2 * iteration_count) {
	{
		std::unique_lock<std::mutex> lock(mutex);
		while (current_iteration % 2 == 0)
			cond_var.wait(lock);
		std::cout << "pong\n";
		current_iteration++;
	}
	cond_var.notify_one();
	}
};

int main()
{
	std::thread thread1(Ping);
	std::thread thread2(Pong);
	
	thread1.join();
	thread2.join();
	
	return 0;
};
