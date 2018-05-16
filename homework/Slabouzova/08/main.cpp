#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <vector>

int main(int argc, char const **argv)
{

	if (argc != 2) {
	    return 1;
	}

	std::ifstream file(argv[1]);
	if (!file) {
	    return 1;
	}

	std::unordered_map<std::string, int> filemap;
    std::string s;
	while (file >> s) {
		filemap[s]++;
	}

	size_t size = filemap.size() <= 10 ? filemap.size() : 10;

	std::vector<std::pair<std::string, int>> tmp_vec(filemap.begin(), filemap.end());
	
	std::partial_sort(tmp_vec.begin(), tmp_vec.begin() + size, tmp_vec.end(), 
								[](auto& p1, auto& p2){ return p1.second > p2.second; });

	for (int i = 0; i < size; i++) {
		std::cout << tmp_vec[i].second << " " << tmp_vec[i].first << std::endl; 
    }
	return 0;
}

