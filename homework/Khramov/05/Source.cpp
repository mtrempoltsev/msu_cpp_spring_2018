#include"Mvector.h"

#define D_SCL_SECURE_NO_WARNINGS
class Tst {
public:
	int _a;
	int _b;
	Tst(int a, int b) : _a(a), _b(b) {};
	Tst() : _a(0), _b(0) {};
};

int main() {
	//Mvector<int> v;
	Mvector<char> c;
	c.push_back('f');
	//Mvector<Tst> s;
	//for (int i = 0; i < 2; i++) {
	//	int a;
		//v.push_back(i);
		//c.push_back('a' + i);
		//Tst t(i, 2 * i);
		//s.push_back(t);
	//}
	//Mvector<int> vv = v;
	//Mvector<Tst> ss = s;
	//for (int i = 0; i < 10; i++) {
	//	std::cout << vv[i] << '\t'<<c[i]<<'\t'<<ss[i]._a<<'-'<< ss[i]._b<<'\n';
	//}
	//int a;
	//std::cin >> a;
	return 0;
}
