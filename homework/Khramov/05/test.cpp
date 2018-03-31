#include <iostream>
#include "bigint.h"


class Test {
private:
  int _a;
  int _b;
public:
  Test(int a, int b){
    _a=a;
    this->_b=b;
  }

  friend std::ostream& operator<<(std::ostream& out, const Test& x);

};

std::ostream& operator<<(std::ostream& out, const Test& x) {
         out << std::setfill('*');
         out << std::setw(5) << x._a<<'\n';
         out << std::setw(5);
         out << x._b;

     return out;
 }

 int main(int argc, char const *argv[]) {
   BigInt t(111222333444);
   unsigned long long a = 111222333444;
   std::cout << a/1000000000<<std::endl;
   std::cout << t << '\n';
   return 0;
 }
