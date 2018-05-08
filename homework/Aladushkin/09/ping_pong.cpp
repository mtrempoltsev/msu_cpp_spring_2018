#include <thread>
#include <iostream>
#include <atomic>
#include <string>

std::atomic_bool turn(true);
std::atomic_int counter(0);

const int count = 1000000;

void out(const std::string& str, const bool a)
{
	while (counter < count)
	{
		if (turn == a)
		{
			std::cout << str;
			counter++;
			turn = !turn;
		}
	}
}

auto ping = std::bind(out, "ping\n", true);
auto pong = std::bind(out, "pong\n", false);

int main()
{
	std::thread t1(ping);
	std::thread t2(pong);

	t1.join();
	t2.join();

	return 0;
}