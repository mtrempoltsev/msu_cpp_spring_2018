#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

bool cmp(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) 
{
	return a.second > b.second;
}

int main(int argc, char* argv[])
{
	const int top_n = 10;
	std::map<std::string, int> dict;
	if (argc != 2)
		return 1;
	std::ifstream fin(argv[1]);
	if (!fin)
		return 1;
	while (fin.good())
	{
		std::string word;
		fin >> word;
		if (dict.find(word) != dict.end())
			dict[word]++;
		else
			dict[word] = 1;
	}
	std::vector<std::pair<std::string, int>> hist{ dict.begin(), dict.end() };
	std::partial_sort(hist.begin(), hist.begin() + top_n, hist.end(), cmp);
	auto stop_it = hist.begin() + top_n;
	for (auto it = hist.begin(); it != stop_it; it++)
		std::cout << it->second << ' ' << it->first << std::endl;
	return 0;
}