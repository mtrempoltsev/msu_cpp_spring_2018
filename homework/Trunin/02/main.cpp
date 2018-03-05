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

int binarySearch(int value){
    int min = 0;
    int max = Size;
    int middle;
    while(min < max){
        middle = (min + max) >> 1;
        if(value > Data[middle])
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
    
    int first_index = 0;
    int first_value = 0; 
    int second_value = 0;
    int second_index = 0; 
    
    for (int i = 0; i < argc - 1; i +=2)
    {
        first_value = std::atoi(argv[i + 1]);
        first_index = binarySearch(first_value);
        if(Data[first_index] != first_value){
            std::cout << 0 << std::endl;
            return 0;
        }
        
        second_value = std::atoi(argv[i + 2]);
        second_index = binarySearch(second_value);
        if(Data[second_index] != second_value){
            std::cout << 0 << std::endl;
            return 0;
        }
        std::cout << findPrimes(first_index, second_value) << std::endl;
    }
    
    return 0;
}
