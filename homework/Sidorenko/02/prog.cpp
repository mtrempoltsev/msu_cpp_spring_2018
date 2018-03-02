#include<iostream>
#include"numbers.dat"
// Data - массив
// Size - размер массива

int binsearch(int g)
{
    
    int left = 0;
    int right = Size - 1;
    int med = (left+right)/2;
    while(left<right-1)
    {
        if(Data[med]<g) 
        {
            left = med;
        }
        else
        {
            right = med;
        }
         med = (left+right)/2;
    }
    if(Data[left]==g) return left;
    if(Data[right]==g) return right;
    return -1;
    /*
    for(int i = 0; i<Size; i++) {
        if(Data[i] == g) return i;
        if(Data[i] > g) return -1;
    }
    return -1;
    */

}

bool isprime(int k)
{
    if(k < 2) return false;
    if(k==2) return true;
    bool flag = (k%2);
    for(int i = 3; ((i*i)<=k) && flag; i+=2)
    {
        flag = (k%i);
    }
    return flag;
}

int Doit(int v,int w)
{
    const int left = binsearch(v);
    const int right = binsearch(w);

    if((left<0)||(right<0)) return 0;
    int count = 0;
    for(int i = left; i<=right; i++)
    {
        if(isprime(Data[i])) count++;

    }
    return count;

}


int main(int argc, char* argv[])
{
    //there is odd non-zero amount of numbers
    if(argc < 2) return -1;
    if((argc - 1)%2 !=0) return -1;
    for (int i = 1; i < argc; i+=2)
    {
        int v = std::atoi(argv[i]);
	int w = std::atoi(argv[i+1]);
        std::cout<<Doit(v, w)<<" ";
    }
    std::cout<<"\n";
    return 0;
}
