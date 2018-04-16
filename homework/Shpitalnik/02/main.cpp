#include <iostream>
#include "numbers.dat"

int to_int(char* str){
    int sum=0;
    int i = 0;
    do{
        sum*=10;
        sum +=(str[i] -'0');
        i++;
    } while(str[i]!= 0);
    return sum;
}


int* sieve(int* arr){
    int i = 1;
    while(i<100000){
        arr[i] = i;
        i++;
    }
    arr[1] = 0;
    i = 2;
    int n;
    while(i<100000){
        if(arr[i] != 0){
            n = 2;
            while(n*i<100000){
                arr[n*i] = 0;
                n++;
            }
        }
        i++;
    }
    return arr;
}


int count (const int* data, const int* arr, int start, int end){
    int sum = 0;
    int i = 0;
    while(data[i] < start)
        i++;
    while(data[i] <= end){
        if (arr[data[i]] != 0)
            sum++;
        i++;
    }
    return sum;
}


int main(int argc, char** argv) {
    if((argc % 2) != 1 || argc == 1)
        return -1;
    int* arr;
    int sum = 0;
    arr = new int [100000];
    arr = sieve(arr);
    for(int i =1; i<(argc-1); i+=2) {
        int start = to_int(argv[i]);
        int end = to_int(argv[i + 1]);
        if (end >= start)
            std::cout <<count(Data, arr, start, end)<<'\n';
        else
            std::cout << '0' <<'\n';
    }
    return 0;
}
