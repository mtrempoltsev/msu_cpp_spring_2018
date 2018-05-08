#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <iostream>

class printer{
private:
  std::atomic<bool> ind { true };
public:
  void ping(){
    std::cout<< "ping"<<std::endl;
    ind = false;
  }
  void pong(){
    std::cout<< "pong"<<std::endl;
    ind = true;
  }
  bool true_ping(){
    return ind;
  }
};

std::mutex m;
std::condition_variable oneReady;

printer p;

void thread1() // thread 1
{
  for(int i = 0; i<4; i++){
      std::unique_lock<std::mutex> lock(m);

      while ( !p.true_ping() ) //1
        oneReady.wait(lock);

      p.ping();
  }
}

void thread2() // thread 2
{
  for(int i = 0; i<5; i++){
    {
        std::lock_guard<std::mutex> lk(m);
        p.pong();
    }
    oneReady.notify_one();
  }
}

int main() {
  std::thread t1(thread1);
  std::thread t2(thread2);
  t1.join();
  t2.join();

  return 0;
}
