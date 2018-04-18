CPPC = g++
CPPFLAGS = -O2 -std=c++11

%PHONY: all clean

all: calc

calc: calc.cpp
	$(CPPC) $(CPPFLAGS) $< -o $@

clean:
	rm -f calc
