
CPPC = g++
CPPFLAGS = -O2 -std=c++14 
CPPCOMPILE = $(CPPC) $^ $(CPPFLAGS) -o $@

%PHONY: all clean

all : sum_by_rows sum_by_cols

sum_by_rows : sum_by_rows.cpp
	$(CPPCOMPILE)

sum_by_cols : sum_by_cols.cpp
	$(CPPCOMPILE)

clean : 
	rm -f sum_by_rows sum_by_cols

