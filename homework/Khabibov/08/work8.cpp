#include<fstream>
#include<iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>

namespace options
{
	constexpr size_t top = 10;
}
int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1;
	std::ifstream file(argv[1]);
	if (!file)
		return 1;
	std::unordered_map<std::string, size_t> frequencyDictionary;
	std::string word;
	while (file.good())
	{
		std::string word;
		file >> word;
		auto it = frequencyDictionary.find(word);
		if (it == frequencyDictionary.end())
			frequencyDictionary[word] = 1;
		else
			it->second++;
	}
	std::vector<std::pair<std::string, size_t>> listOfWords{frequencyDictionary.begin(), frequencyDictionary.end()};
	std::partial_sort(listOfWords.begin(), listOfWords.begin() + options::top, listOfWords.end(),
		[](const std::pair<std::string, size_t>& x, const std::pair<std::string, size_t>& y) { return x > y; });
	for (auto it = listOfWords.begin(); it != listOfWords.begin() + options::top; it++)
		std::cout << it->second << ' ' << it->first << std::endl;
	return 0;
}
