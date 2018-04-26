#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>


int main(int argc, char* argv[]) {
	if (argc != 2) {
		return 1;
	}
	std::string str;
	std::map<std::string, int> dict;

	std::fstream file;
	file.open(argv[1], std::fstream::in);

	if (!file) {
		std::cerr << "file error" << std::endl;
		return 1;
	}

	while (file >> str)
		dict[str]++;

	file.close();

	std::multimap<int, std::string> m;
	for (auto it = dict.begin(); it != dict.end(); it++) {
		m.insert(std::pair<int, std::string>(it->second, it->first));
	}
	int count = 0;
	
	for (auto it = m.rbegin(); it != m.rend() && count++ < 10; it++) {
		std::cout << it->first << ' ' << it->second << std::endl;
	}

	return 0;
}