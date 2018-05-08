#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>

const int N = 1000000;

std::mutex mutex;
std::condition_variable dataReady;

void pingThread() {
	for (int i = 0; i < N/2; i++) {		
		std::unique_lock<std::mutex> lock(mutex);

		dataReady.notify_one();	
		std::cout << "ping\n";	
		dataReady.wait(lock);

		if (i == (N / 2 - 1)) {
			dataReady.notify_one();
			return;
		}
	}
	
}

void pongThread() {
	for (int i = 0; i < N; i++) {
		if (i == (N - 1))
			return;
		std::unique_lock<std::mutex> lock(mutex);
		if (i % 2 == 0) {
			std::cout << "pong\n";
			dataReady.notify_one();
			dataReady.wait(lock);
			if (i == (N - 2))
				return;
		}
	}
}

int main() {
	std::thread t1(pingThread);
	std::thread t2(pongThread);
	t1.join();
	t2.join();

	return 0;
}