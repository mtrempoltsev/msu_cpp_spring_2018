#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		return 1;
	}
	std::string filename = argv[1];
	std::map<std::string, int>a;
	std::ifstream file(filename);
	if (!file)
	{
		return 1;
	}
	while (file.good())
	{
		std::string s;
		file >> s;
		std::map<std::string, int>::iterator it = a.find(s);
		if (it != a.end())
		{
			it->second+=1;
		}
		else
		{
			a.insert(std::pair<std::string, int>(s, 1));
		}
	}
	file.close();
	std::multimap<int, std::string>a_inversed;
	for (auto it = a.begin(); it != a.end(); it++)
	{
		a_inversed.insert(std::pair<int, std::string>(it->second, it->first));
	}
	int counter = 0;
	for (auto it = a_inversed.rbegin(); it != a_inversed.rend() && counter<10;counter++,it++)
	{
		std::cout << it->first << ' ' << it->second << std::endl;
	}
}