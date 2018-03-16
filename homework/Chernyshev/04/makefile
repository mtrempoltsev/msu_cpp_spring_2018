
CPPC = g++
CPPFLAGS = -O2 -std=c++14

%PHONY: all clean

all: check

check: check.o
	$(CPPC) $(CPPFLAGS) $^ -o $@

check.o: check.cpp matrix.h
	$(CPPC) $(CPPFLAGS) -c $<

clean:
	rm -f check check.o
