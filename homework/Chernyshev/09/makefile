CPPC = g++
CPPFLAGS = -O2 -std=c++14

%PHONY: all clean

all: ping_pong ping_pong_without_condition_variable

ping_pong: ping_pong.cpp
	$(CPPC) $(CPPFLAGS) $< -o $@

ping_pong_without_condition_variable: ping_pong_without_condition_variable.cpp
	$(CPPC) $(CPPFLAGS) $< -o $@

clean:
	rm -f ping_pong ping_pong_without_condition_variable
