#include <iostream>
#include <string>
#include <map>
#include <fstream>

int main(int argc, char* argv[]) {
	if (argc != 2)
		return 1;

	std::fstream file;
	file.open(argv[1], std::fstream::in);

	if (!file)
		return 1;

	std::map<std::string, int> string_int;
	std::string word;
	while (file >> word)
		string_int[word]++;

	std::multimap<int, std::string> int_string;
	for (auto elem : string_int) {
		int_string.insert(std::pair<int, std::string>(elem.second, elem.first));
	}

	auto elem = int_string.rbegin();
	for (int i = 0 ; i < 10; i++) {
		std::cout << elem->first << ' ' << elem->second << std::endl;
    	elem++;
    	if(elem==int_string.rend())
        	break;
	}

	return 0;
}
