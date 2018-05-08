all: bigint
	./bigint.o

test:
	g++ test.cpp -o test.o --std=c++17
	./test.o

bigint: bigint.hpp
	g++ -x c++ bigint.hpp  -o bigint.o --std=c++14

clean:
	rm -rf *.o
