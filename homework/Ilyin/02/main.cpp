#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

std::vector<bool> eratosphene_sieve(int b){
    std::vector<bool> indic_array;
    indic_array.resize(b+1);

    indic_array[0] = 0;
    indic_array[1] = 0;

    for (size_t i = 2; i < b + 1; i++){
        indic_array[i] = 1;
    }

    for (int64_t i = 2; i < b+1; i++){

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

size_t bin_search(std::vector<int> numbers, int a, bool right_border){
    size_t first = 0;
    size_t last = numbers.size();

    while (first < last){
        size_t mid = (first + last) / 2;
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
            std::cout<<0;
            return 0;
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
            std::cout<<0;
            return 0;
        }
    }
}

/*std::vector<int> atkin_sieve(int a, int b){

}

std::vector<int> primes_int_union(int a, int b, std::vector<int> f_arg, int f_arg_a, int f_arg_b, std::vector<int> s_arg, int s_arg_a, int s_arg_b){

}*/

int main(int argc, char **argv){
    std::vector<int> data;

    size_t N = 1024;

    data.resize(N);

    std::ifstream file_f;
    file_f.open("numbers.dat");
    
    char buf[256];

    size_t i = 0;

    if (file_f.is_open() && !file_f.eof()){
        file_f.ignore(256, '\n');
        file_f.ignore(256, '\n');
    }
    else{
        return -1;
    }

    while (!file_f.eof()){
        
        file_f.getline(buf, 256, ',');

        data[i] = atoi(buf);

        if (i == N - 1){
            N *= 2;
            data.resize(N);
        }

        i++;

    }

    N = i;

    data.resize(N);

    if (argc % 2 == 0 || argc == 1){
        std::cout<<"-1"<<std::endl;
        return -1;
    }

    
    for (size_t i = 1; i < (argc + 1) / 2; i++){
        int a = atoi(argv[2 * i - 1]);
        int b = atoi(argv[2 * i]);

        std::vector<bool> primes = eratosphene_sieve(b);

        int count = 0;

        size_t first = bin_search(data, a, 0);
        size_t last = bin_search(data, b, 1);

        for (size_t j = first; j < last; j++ ){
            if (primes[data[j]]){
                count++;
            }
        }

        std::cout<<count<<std::endl;
    }

    return 0;
}
