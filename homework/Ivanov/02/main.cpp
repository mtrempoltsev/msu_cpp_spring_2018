#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include "numbers.dat"

bool prime(int n){ 
	if(n == 1) {
		return false;
	}
	for(int i = 2; i <= std::sqrt(n); i++) {
		if(n % i == 0) {
			return false;
		}
	}
	return true;
}

int count_index(int value) {
	int idx = 0;
	while(idx < Size) {
		if(Data[idx] == value) {
			break;
		}
		idx++;
	}
	if(idx == Size) {
		return -1;
	}
	return idx;
}

int main(int argc, char const *argv[])
{
    if(argc % 2 == 0 || argc == 1) {
    	return -1;
    }
    int index_left, index_right, count;
	std::vector<int> ans;
	for(int i = 1; i < argc; i += 2) {
    	count = 0;
    	index_left = count_index(std::atoi(argv[i]));
    	index_right = count_index(std::atoi(argv[i + 1]));
    	if(index_left == -1 || index_right == -1 || index_left > index_right) {
    		std::cout << 0 << std::endl;
    		continue;
    	}
    	for(int j = index_left; j <= index_right; j++) {
    		if(prime(Data[j])) {
    			count++;
    		}
    	}
    	ans.push_back(count);
    }
    for(int i = 0; i < ans.size(); i++) {
    	std::cout << ans[i] << std::endl;
    }
	return 0;
}