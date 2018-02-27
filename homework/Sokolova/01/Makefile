run: build
	./sum_by_rows
	./sum_by_cols
build: sum_by_rows sum_by_cols
sum_by_rows: sum_by_rows.cpp matrix.h timer.h
	g++ --std=c++11 sum_by_rows.cpp -o sum_by_rows -O2
sum_by_cols: sum_by_cols.cpp matrix.h timer.h
	g++ --std=c++11 sum_by_cols.cpp -o sum_by_cols -O2
rows: sum_by_rows
	./sum_by_rows
cols: sum_by_cols
	./sum_by_cols
clean:
	rm -f sum_by_rows
	rm -f sum_by_cols