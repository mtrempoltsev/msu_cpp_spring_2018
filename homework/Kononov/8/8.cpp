// Kononov Sergey BD-11

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

bool Comparator(std::pair<std::string, int> a, 
				std::pair<std::string, int> b)
{
	return a.second > b.second;
};

int main(int argc,  char* argv[])
{
	try
	{
		if (argc !=2)
			throw std::invalid_argument("Error, program should use run with one parametr!");
		
		std::string filepath = argv[1];
	
		std::ifstream file(filepath);
		if (!file.good())
			throw std::invalid_argument("Error, invalid file path!");

		std::string word;
		std::map <std::string, int> dict;

		while (file >> word){
			auto  position = dict.find(word);
			if (position == dict.end())
				dict.emplace(word, 1);
			else
				(position -> second)++;
		};

		std::vector <std::pair <std::string, int>> vec(0);

		for (auto it = dict.begin(); it != dict.end(); it++)
			vec.push_back(std::make_pair(it -> first, it -> second));

		std::sort(vec.begin(), vec.end(), Comparator);

		for (auto it = vec.begin(); (it != vec.end()) && (it != vec.begin() + 10); it++)
			std::cout << it -> second << " " << it -> first << "\n";

	}
	catch (const std::exception & Error){
		std::cout << Error.what();
		return 1;
	};

	return 0;
};
