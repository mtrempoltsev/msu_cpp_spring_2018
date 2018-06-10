#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

bool Comparator(const std::pair<std::string, int> & a, const std::pair<std::string, int> & b)
{
	return a.second > b.second;
};

int main(int argc,  char* argv[])
{
		if (argc !=2)
			return 1;
		
		std::string filepath = argv[1];
	
		std::ifstream file(filepath);
		if (!file.good())
			return 1;

		std::string word;
		std::map <std::string, int> dict;

		while (file >> word){
			if (dict.count(word))
				dict[word]++;
			else
				dict.emplace(word, 1);
		};

		std::vector <std::pair <std::string, int>> vec(0);

		for (auto it = dict.begin(); it != dict.end(); it++)
			vec.emplace_back(std::move(*it));

		std::sort(vec.begin(), vec.end(), Comparator);

		for (auto it = vec.begin(); (it != vec.end()) && (it != vec.begin() + 10); it++)
			std::cout << it -> second << " " << it -> first << "\n";

	return 0;
};
