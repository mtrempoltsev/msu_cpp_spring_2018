
CPPC = g++
CPPFLAGS = -O2 -std=c++14
COMPILECPP = $(CPPC) $(CPPFLAGS) $^ -o $@

%PHONY: all clean

all : slow normal fast

slow : slow.cpp
	$(COMPILECPP)

normal : normal.cpp
	$(COMPILECPP)

fast : fast.cpp
	$(COMPILECPP)

clean : 
	rm -f slow normal fast

