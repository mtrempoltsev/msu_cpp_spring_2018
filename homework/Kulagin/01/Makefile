COMPILE_ROWS=g++ sum_by_rows.cpp -o sum_by_rows --std=c++11 -O2
COMPILE_COLS=g++ sum_by_cols.cpp -o sum_by_cols --std=c++11 -O2

all:
	$(COMPILE_ROWS) && $(COMPILE_COLS) && bash cmp.sh

run_rows:
	$(COMPILE_ROWS) && ./sum_by_rows

run_cols:
	$(COMPILE_COLS) && ./sum_by_cols

valgrind_rows:
	$(COMPILE_ROWS) && valgrind --tool=cachegrind --log-file="valgrind_rows.out" ./sum_by_rows

valgrind_cols:
	$(COMPILE_COLS) && valgrind --tool=cachegrind --log-file="valgrind_cols.out" ./sum_by_cols

clean:
	@ [ ! -f sum_by_rows ] || rm sum_by_rows
	@ [ ! -f sum_by_cols ] || rm sum_by_cols

