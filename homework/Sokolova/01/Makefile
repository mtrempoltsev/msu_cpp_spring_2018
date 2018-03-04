run: build
	./sum_by_rows
	./sum_by_cols
build: sum_by_rows sum_by_cols
matrix.o: matrix.h matrix.cpp
	g++ --std=c++11 -c matrix.cpp -o matrix.o -O2
sum_by_rows: sum_by_rows.cpp timer.h matrix.o
	g++ --std=c++11 sum_by_rows.cpp matrix.o -o sum_by_rows -O2
sum_by_cols: sum_by_cols.cpp timer.h matrix.o
	g++ --std=c++11 sum_by_cols.cpp matrix.o -o sum_by_cols -O2
rows: sum_by_rows
	./sum_by_rows
cols: sum_by_cols
	./sum_by_cols
clean:
	rm -f sum_by_rows
	rm -f sum_by_cols
	rm -f matrix.o