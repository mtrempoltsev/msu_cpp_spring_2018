#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

#include <algorithm>

#include <string>
#include <unordered_map>
#include <vector>

bool res_predicat(const std::pair<std::string, int>& s1, const std::pair<std::string, int>& s2)
{
	return s1.second > s2.second;
}

class Dictionary
{
public:

	Dictionary(const std::string& input_file_name, const std::string& output_file_name)
	{
		input_f = std::ifstream(input_file_name);
		output_f = std::ofstream(output_file_name, std::ofstream::trunc);
	}

	~Dictionary()
	{
		input_f.close();
		output_f.close();
	}

	void make_dictionary()
	{
		std::string word;

		if (!input_f)
			throw std::runtime_error("Could not open file");

		while (input_f >> word)
			dictionary[word]++;

		vec_dictionary.reserve(dictionary.size());
		for (auto it = dictionary.begin(); it != dictionary.end(); it++)
			vec_dictionary.push_back(*it);
	}

	void out_results(const int n)
	{
		int sort_size = n;

		if (n > vec_dictionary.size())
			sort_size = vec_dictionary.size();

		std::partial_sort(vec_dictionary.begin(), vec_dictionary.begin() + n, vec_dictionary.end(), res_predicat);

		for (auto it = vec_dictionary.begin(); it != vec_dictionary.begin() + n; it++)
		{
			std::cout << it->second << ' ' << it->first << std::endl;
			output_f << it->second << ' ' << it->first << std::endl;
		}
			
	}

private:
	std::ifstream input_f;
	std::ofstream output_f;

	std::unordered_map<std::string, int> dictionary;
	std::vector<std::pair<std::string, int>> vec_dictionary;
};

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			throw std::invalid_argument("There is no input file name!");
			return 1;
		}

		if (argc == 2)
		{
			Dictionary dict(argv[1], "output.txt");
			dict.make_dictionary();
			dict.out_results(10);
		}
	}
	catch (...)
	{
		return 1;
	}

	return 0;
}