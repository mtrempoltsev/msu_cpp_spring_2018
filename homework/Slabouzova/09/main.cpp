#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

std::condition_variable condVar;
int count = 1000000-1;
std::mutex m;
int i = 0;

void pingpong(const std::string& str, int check_val)
{
	std::unique_lock<std::mutex> lock(m);
	while(i < count) {
		while(i%2 == check_val) {
			condVar.wait(lock);	
		}
		std::cout << str << std::endl;
		i++;
		condVar.notify_one();		
	}
}

int main()
{
	std::thread thread1(pingpong, "ping", 1);
	std::thread thread2(pingpong, "pong", 0);
	thread1.join();
	thread2.join();
	return 0;
}