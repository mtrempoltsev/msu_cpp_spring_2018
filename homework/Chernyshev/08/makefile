CPPC = g++
CPPFLAGS = -O2 -std=c++14

%PHONY: all clean

all: count

count: count.cpp
	$(CPPC) $(CPPFLAGS) $< -o $@

clean:
	rm -f count
