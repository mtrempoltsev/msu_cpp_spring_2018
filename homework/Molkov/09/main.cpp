#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>

const int N = 999999;

std::mutex mutex;
std::condition_variable dataReady;
int i = 0;
void pingThread() {
	while(i < N) {
		std::unique_lock<std::mutex> lock(mutex);

		//dataReady.notify_one();
		
		if (i % 2 == 1) {
			dataReady.wait(lock);
		}
		std::cout << "ping\n";
		i++;
		dataReady.notify_one();
		
	}
	//dataReady.notify_one();
	
}

void pongThread() {
	while (i < N) {

		std::unique_lock<std::mutex> lock(mutex);
		
		if (i % 2 == 0) {
			dataReady.wait(lock);	
		}
		std::cout << "pong\n";
		i++;
		dataReady.notify_one();
		
	}
}

int main() {
	std::thread t1(pingThread);
	std::thread t2(pongThread);
	t1.join();
	t2.join();

	return 0;
}