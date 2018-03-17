#pragma once

#include <iostream>

using namespace std;

#define Assert(cond) do { if (!(cond)) cout << "\033[1;31;1m" << "Error: " << "\033[1;32;0m" << #cond << " in \"" << __FILE__ << "\" at line " << __LINE__ << endl; exit(1); } while(0)
