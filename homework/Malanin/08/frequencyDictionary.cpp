#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>


namespace ourdata
{
	constexpr size_t max = 10;
}


int main(int argc, char* argv[])
{
	if (argc != 2)
		return 1;
	std::ifstream file(argv[1]);
	if (!file)
		return 1;
	std::unordered_map<std::string, size_t> Dict;
	std::string word;
	while (file.good())
	{
		file >> word;		
		auto it = Dict.find(word); //получим итератор
		if (it == Dict.end()) //если такого слова не было, то оно первое
			Dict[word] = 1;
		else
			it->second++; //иначе увеличиваем на 1
	}
		
	std::vector<std::pair<std::string, size_t>> list{Dict.begin(), Dict.end()};	
	const bool b = list.size() > ourdata::max;	//в булеву константу b сохраним информацию о том, более ли чем max у нас различных слов
	
	std::partial_sort(list.begin(), list.begin() + ((b) ? ourdata::max : list.size()), list.end(),
		[](const std::pair<std::string, size_t>& x, const std::pair<std::string, size_t>& y) { return x.second > y.second;});
	
	auto itstop = b ? list.begin() + ourdata::max : list.end(); //определяем конечный итератор
	for (auto it = list.begin(); it != itstop; it++)
	{
		std::cout << it->second<< " "<< it->first << std::endl;
	} 


	return 0;
}
