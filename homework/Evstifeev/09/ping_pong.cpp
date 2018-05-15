#include<iostream>
#include<thread>
#include <mutex>
#include <condition_variable>

std::mutex mut;
std::condition_variable cond_var;

constexpr size_t max_iter = 1000000;
bool flag = true;

void ping_pong_thread(const bool to_ping)
{
  std::string out = to_ping ? "ping" : "pong";
  for (size_t i = 0; i < max_iter / 2; i++) {
    std::unique_lock<std::mutex> lock(mut);
    cond_var.wait(lock, [to_ping](){ return to_ping == flag;});
    std::cout << out << std::endl;
    flag = !to_ping;
    cond_var.notify_one();
  }
}
int main(int argc, char const *argv[]) {
  std::thread t1(ping_pong_thread, false);
  std::thread t2(ping_pong_thread, true);
  t1.join();
  t2.join();
  return 0;
}
