#pragma once

#include <iostream>

using namespace std;

void Assert(bool expr, string err, string file, const int line) {
	if (!expr) {
		cout << "\033[1;31;1m" << "Error: " << "\033[1;32;0m" << err << endl;
		cout << "File: " << file << endl;
		cout << "Line: " << line << endl;

		exit(1);
	}
}

void is_ok(bool expr, string err, string file, const int line) {
	if (!expr) {
		cout << "\033[1;31;1m" << "Error: " << "\033[1;32;0m" << err << endl;
		cout << "File: " << file << endl;
		cout << "Line: " << line << endl;
	}
}