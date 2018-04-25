#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

static bool is_ping_turn;

static uint64_t N = 1e6;

std::condition_variable cond_var;

std::mutex m;

void print_ping() {
	for (uint64_t i = 0; i < N; i++) {
		std::unique_lock<std::mutex> lock(m);

		while (!is_ping_turn) {
			cond_var.wait(lock);
		}

		std::cout << "Ping!" << std::endl;

		is_ping_turn = false;

		cond_var.notify_one();
	}
}

void print_pong() {
	for (uint64_t i = 0; i < N; i++) {
		std::unique_lock<std::mutex> lock(m);

		while (is_ping_turn) {
			cond_var.wait(lock);
		}

		std::cout << "Pong!" << std::endl;

		is_ping_turn = true;

		cond_var.notify_one();
	}
}

int main(int argc, char** argv) {
	is_ping_turn = true;

	std::thread ping(print_ping);
	std::thread pong(print_pong);

	ping.join();
	pong.join();

	return 0;
}
