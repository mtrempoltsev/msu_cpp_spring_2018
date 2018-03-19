#pragma once

#define Assert(cond) if(!(cond)){ std::cout << "\033[1;31;1m" << "Error: " << "\033[1;32;0m" << #cond << " in \"" << __FILE__ << "\" at line " << __LINE__ << std::endl; }
