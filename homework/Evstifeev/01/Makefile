all: sum_by_col sum_by_rows

sum_by_col: sum_by_columns.cpp
	g++ sum_by_columns.cpp -o sum_by_columns.o --std=c++11 -O2
	./sum_by_columns.o

sum_by_rows: sum_by_rows.cpp
	g++ sum_by_rows.cpp -o sum_by_rows.o --std=c++11 -O2
	./sum_by_rows.o

clean:
	rm -rf *.o
