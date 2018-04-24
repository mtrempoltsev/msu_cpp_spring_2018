#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

int main(int argc, const char * argv[])
{
	if (argc != 2)
		return 1;
	std::string f = argv[1];
	std::ifstream file(f);
	if (!file) { std::cout << "can't open file";  return 1; }
	std::unordered_map<std::string,std::uint32_t> map;
	while (file.good())
	{
		std::string s;
		file >> s;
		map[s]++;
	}
	std::vector<std::pair<std::string, std::uint32_t>> words(map.begin(),map.end());
	std::size_t min = std::min((std::size_t)10, words.size());
	std::partial_sort(words.rbegin(), words.rbegin()+ min, words.rend(), 
       		[](const std::pair<std::string, std::uint32_t> &first, const std::pair<std::string, std::uint32_t> &second)->bool 
        		{return first.second > second.second; });
	for (size_t it=words.size()-1; it>=words.size()-min; --it)
		std::cout << words[it].second << " " << words[it].first << std::endl;
	return 0;
}
