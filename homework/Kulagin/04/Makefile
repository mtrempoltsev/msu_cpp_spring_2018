COMPILE=g++ main.cpp -std=c++11 -Wall -pedantic -Wconversion -o main.x

all:
	$(COMPILE)

vg:
	$(COMPILE)
	valgrind --leak-check=full ./main.x

clean:
	@ rm main.x 2>/dev/null || true
