#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>

const int N = 1000000;

std::mutex mutex;
std::condition_variable condition;
int i = 0, j = 0;
bool p = true;

void ping() {
	while (i < N/2) {
		std::unique_lock<std::mutex> lock(mutex);

		if (!p) {
			condition.wait(lock);
		}

		std::cout << "ping\n";
		i++;
		p = false;

		condition.notify_one();
	}

}

void pong() {
	while (j < N/2) {

		std::unique_lock<std::mutex> lock(mutex);

		if (p) {
			condition.wait(lock);
		}

		std::cout << "pong\n";
		j++;
		p = true;

		condition.notify_one();
	}
}

int main(void) {
	std::thread pin(ping);
	std::thread pon(pong);
	pin.join();
	pon.join();

	return 0;
}
