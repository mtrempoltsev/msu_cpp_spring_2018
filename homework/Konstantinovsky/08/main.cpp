#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]) {

	if (argc != 2) {
		return 1;
	}

	std::fstream file;
	file.open(argv[1], std::fstream::in);
	//std::ifstream file("input.txt");

	if (!file) {
		return 1;
	}

	std::string word;
	std::map <std::string, int> words_map;
	std::vector<std::pair<std::string, int>> words_vector;

	while (file >> word) {
		++words_map[word];
	}
	file.close();

	auto i1 = words_map.begin();
	while (i1 != words_map.end()) {
		words_vector.emplace_back(i1->first, i1->second);
		++i1;
	}

	std::sort(words_vector.begin(), words_vector.end(),
		[](std::pair<std::string, int> &left, std::pair<std::string, int> &right) { return left.second > right.second; });

	auto i2 = words_vector.begin();
	int ii = 0;
	while (i2 != words_vector.end()) {
		if (ii >= 10) {
			break;
		}
		std::cout << i2->second << " " << i2->first << "\n";
		++i2;
		++ii;
	}

	return 0;
}