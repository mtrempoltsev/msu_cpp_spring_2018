INCLUDE=include
SRC=src

COMPILE=g++ main.cpp -std=c++11 -I$(INCLUDE) -I$(SRC) -Wall -pedantic -Wconversion -o main.x


all:
	$(COMPILE)

vg:
	$(COMPILE)
	valgrind --leak-check=full ./main.x

clean:
	@ rm main.x 2>/dev/null || true
