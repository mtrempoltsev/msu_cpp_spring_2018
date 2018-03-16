all:
	g++ main.cpp -Wall -std=c++11 -o main.x

vg:
	valgrind --leak-check=full ./main.x

clean:
	@ rm main.x 2>/dev/null || true