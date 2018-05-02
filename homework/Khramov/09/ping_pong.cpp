#include <thread>
#include <atomic>
#include <iostream>

std::atomic<int> ind { 0 };

void thread1() // thread 1
{
  int count = 1;
  while (true)
  {
      if (count==1000000){return;}
      if ( ind == 0)
      {
        std::cout<< "ping"<<std::endl;
        ind = 1;
        count++;
      }
  }
}

void thread2() // thread 2
{
  int count = 1;
  while (true)
  {
      if (count==1000000){return;}
      if ( ind == 1)
      {
        std::cout<< "pong"<<std::endl;
        ind = 0;
        count++;
      }

  }
}

int main() {
  std::thread t1(thread1);
  std::thread t2(thread2);
  t1.join();
  t2.join();

  return 0;
}
