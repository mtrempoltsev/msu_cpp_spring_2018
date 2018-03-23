TARGET = main
CC = g++
OPTIONS = -std=c++14 -O2 -Wall

all: $(TARGET)

$(TARGET): main.o matrix.o
	$(CC) $(OPTIONS) -o $(TARGET) matrix.o main.o

main.o: main.cpp
	$(CC) $(OPTIONS) -c -o main.o main.cpp

matrix.o: matrix.cpp
	$(CC) $(OPTIONS) -c -o matrix.o matrix.cpp

clean:
	rm -rf $(TARGET) *.o
