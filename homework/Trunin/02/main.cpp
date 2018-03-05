#include <iostream>
#include <cmath>
#include "numbers.dat"

bool checkPrime(int number){
    if(number == 1) return false;
    for(int i = 2; i*i <= number; i++){
        if(number % i == 0){
            return false;
        }
    }
    return true;
}

int findStartIndex(int start){
    int min = 0;
    int max = Size;
    int middle;
    while(min < max){
        middle = (min + max) >> 1;
        if(start > Data[middle])
            min = middle + 1;
        else 
            max = middle; 
    }
    return min;
}

int findPrimes(int start_index, int end){
    int sum = 0;
    for(int i = start_index; Data[i] <= end && i < Size ; i++){
        if(checkPrime(Data[i])){
            sum++;
        }
    }
    return sum;
}


int main(int argc, char* argv[]){
    if (!(argc & 1) || argc == 1) return -1;
      
    for (int i = 0; i < argc - 1; i +=2)
    {
        std::cout << findPrimes(findStartIndex(std::atoi(argv[i + 1])), std::atoi(argv[i + 2])) << std::endl;
    }
    
    return 0;
}
