all: tests
	./tests.o

tests: matrix.hpp
	g++ tests.cpp -o tests.o --std=c++14

clean:
	rm -rf *.o
