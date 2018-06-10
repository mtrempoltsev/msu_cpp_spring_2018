//count primes in range [a,b], if no such range ret 0, if fail or internal error return 0
#include "numbers.dat"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//numbers array lies in numbers.dat and is called Data (and contains Size elements)
void pfill(int *, const int *, int);
int bget(const int *, int, int);
int eget(const int *, int, int); //
int pcount(const int *data, int size, int beg, int end, int mode, int *fill=NULL); //counts primes, has filled mode TODO
int primes(int *prim, const int *data, int sz);
int primes(int *prim, const int *data, int sz)
{
	int i, j;
	int count=1, tmp, flag;
	const int max=data[sz-1];
	if(sz<=0)
	{
		return 0;
	}
	prim[0]=2;
	for(i=3; i<=max; i+=2)
	{
		tmp=sqrt(i);
		flag=0;
		for(j=0; j<count && prim[j]<tmp; j++)
		{
			if(i%prim[j]==0)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			prim[count]=i;
			count++;
		}
	}
	return count; //finish it
}
int pcount(const int *dt, int sz, int beg, int end, int mode, int *fill)
{
	int i;
	//mode==0 -- no fill
	int ret=0;
	const int b=bget(dt, sz, beg), e=eget(dt, sz, end);
	if(b==-1 || e==-1)
	{
		return -1;
	}
	for(i=b; i<=e; i++)
	{
		ret+=fill[i];
	}
	return ret;
}
int bget(const int *dt, int sz, int d)
{
	//search in beginning
	int i=0;
	while(i<sz && dt[i]<d)
	{
		i++;
	}
	if(dt[i]==d)
	{
		return i;
	}
	return -1;
}
int eget(const int *dt, int sz, int d)
{
	int i=sz-1;
	while(i>0 && dt[i]>d)
	{
		i--;
	}
	if(dt[i]==d)
	{
		while(dt[i]==d)
		{
			d--;
		}
		return i;
	}
	return -1;
}
void pfill(int *fl, const int *dt, int sz)
{
	int *pr, pc=3, flag=1;
	double tmp;
	pr=new int[sz];
	pc=primes(pr, dt, sz);
	for(int i=0; i<sz; i++)
	{//for each integer in dt
		if(dt[i]==1)
		{
			fl[i]=0;
			continue;
		}
		flag=1;
		tmp=sqrt(dt[i]);
		for(int j=0; j<pc; j++)
		{
			if(pr[j]>tmp)
			{
				break; //isprime
			}
			if(dt[i]%pr[j]==0)
			{
				flag=0;
				break;
			}
		}
		fl[i]=flag;
	}
	delete []pr;
}

int main(int argc, char **argv)
{
	int i=1;
	int flag=0;
	int t1, t2;
	int res;
	int *pflags;
	pflags= new int[Size];
	if(argc<2 || argc%2==0)
	{
		return -1;
	}
	while(i<argc)
	{//getting pairs from argv, think 'bout it
		pfill(pflags, Data, Size);
		t1=atoi(argv[i]);
		t2=atoi(argv[i+1]);
		if(t1==0 || t2==0)
		{
			return -1;
		}
		res=pcount(Data, Size, t1, t2, 1, pflags);
		if(res==-1)
		{
			return -1;
		}
		printf("%d\n", res);
		i+=2;
	}
	//printf("%d\n", argc);
	delete []pflags;
	return 0;
}
