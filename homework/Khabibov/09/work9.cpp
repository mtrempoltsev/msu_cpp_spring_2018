#include<thread>
#include<mutex>
#include<iostream>
#include<condition_variable>

namespace options
{
	constexpr int N = 500000;
}
class Semaphore
{
	std::mutex mutex_;
	std::condition_variable condition_;
	int counter_;
public:
	Semaphore(int initialValue = 1)
		: counter_(initialValue)
	{
	}

	void enter()
	{
		std::unique_lock<std::mutex> lock(mutex_);
		condition_.wait(lock, [this]() { return counter_ > 0; });
		counter_--;
	}

	void leave()
	{
		std::unique_lock<std::mutex> lock(mutex_);
		counter_++;
		condition_.notify_one();
	}
};

Semaphore ping(1);
Semaphore pong(0);

void printPing()
{
	for (int i = 0; i < options::N; ++i)
	{
		ping.enter();
		printf("ping\n");
		pong.leave();
	}
}

void printPong()
{
	for (int i = 0; i < options::N; ++i)
	{
		pong.enter();
		printf("pong\n");
		ping.leave();
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
