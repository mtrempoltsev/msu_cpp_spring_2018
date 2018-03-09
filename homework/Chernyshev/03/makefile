CPPC = g++
CPPFLAGS = -O2 -std=c++14

%PHONY: all clean

all: game

game: game.cpp
	$(CPPC) $(CPPFLAGS) $^ -o $@

clean: 
	rm -f game
