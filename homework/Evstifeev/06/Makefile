all: calc

calc: calc.hpp token.hpp calc.cpp
	g++ -pedantic -Wall calc.cpp -o calc --std=c++14

token: token.hpp
	g++ token.hpp -o token.o --std=c++14

clean:
	rm -rf *.o
	rm -rf *.gch
	rm calc
