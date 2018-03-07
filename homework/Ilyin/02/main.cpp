#include <iostream>
#include <vector>
#include <cstdlib>
#include "numbers.dat"

std::vector<bool> eratosphene_sieve(int b){
    std::vector<bool> indic_array;
    indic_array.resize(b+1);

    indic_array[0] = 0;
    indic_array[1] = 0;

    for (int i = 2; i < b + 1; i++){
        indic_array[i] = 1;
    }

    for (int64_t i = 2; i < b + 1; i++){

        if (indic_array[i] != 1){
            continue;
        }

        int64_t j = i * i;

        while( j < b + 1 ){
            indic_array[j] = 0;
            j += i;
        }

    }

    return indic_array;
    
}

int bin_search(const int * numbers, const int size, int a, bool right_border){
    int first = 0;
    int last = size;

    while (first < last){
        int mid = (first + last) / 2;
        if (a <= numbers[mid]){
            last = mid;
        }
        else{
            first = mid + 1;
        }
    }

    if (right_border){

        if (numbers[last] == a){

            while (numbers[last + 1] == a){
                last++;
            }

            return last;
        }

        else{
            return -1;
        }
    }
    else{

        if (numbers[last] == a){

            while(numbers[last - 1] == a){
                last--;
            }
            
            return last;
        
        }

        else{
            return -1;
        }
    }
}

int main(int argc, char **argv){

    if (argc % 2 == 0 || argc == 1){
        std::cout<<"-1"<<std::endl;
        return -1;
    }

    for (int i = 1; i < (argc + 1) / 2; i++){
        int a = atoi(argv[2 * i - 1]);
        int b = atoi(argv[2 * i]);

        std::vector<bool> primes = eratosphene_sieve(b);

        int first = bin_search(Data, Size, a, false);
        int last = bin_search(Data, Size, b, true);
        
        if (first == -1|| last == -1){
            std::cout<<0;
            return 0;
        }

        int count = 0;

        for (int j = first; j < last; j++ ){
            if (primes[Data[j]]){
                count++;
            }
        }

        std::cout<<count<<std::endl;
    }

    return 0;
}
