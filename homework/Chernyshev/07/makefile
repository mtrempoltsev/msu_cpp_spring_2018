CPPC = g++
CPPFLAGS = -O2 -std=c++14

%PHONY: all clean

all: check

check: check.cpp vector.h
	$(CPPC) $(CPPFLAGS) $< -o $@

clean:
	rm -f check