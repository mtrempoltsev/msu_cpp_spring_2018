#include "huff.h"
int main(int argc, char **argv)
{
	int32_t res;
	uint64_t *w, sum=0, *sw;
	uint8_t *sv;
	Wbyte *tab;
	if(argc!=3)
	{
		std::cout << "Usage: " << argv[0] << " <file_name> <archive_name>\n";
		return -1;
	}
	w=new uint64_t[Const::buflen];
	sw=new uint64_t[Const::buflen];
	sv=new uint8_t[Const::buflen];
	tab=new Wbyte[Const::buflen];
	res=TableGen(argv[1], w);
	if(res==0)
	{
		for(uint32_t i=0; i<Const::buflen; i++)
		{
			//std::cout << i << " " << w[i] << std::endl;
			sum+=w[i];
			tab[i].w=w[i];
			tab[i].v=i;
		}
		//std::cout << "read:  " << sum << std::endl;
	}
	else
	{
		return -1;
	}
	qsort(tab, Const::buflen, sizeof(Wbyte), Cmp);
	for(uint32_t i=0; i<Const::buflen; i++)
	{
		sw[i]=tab[i].w;
		sv[i]=tab[i].v;
		//std::cout << i << " " << sw[i] << " " << sv[i] << std::endl;
	}
	HuffTree t(sw, sv);
	res=t.WCode(argv[1], argv[2], w);
	//std::cout << "write: "<< res << std::endl;
	delete[] w;
	delete[] sw;
	delete[] sv;
	delete[] tab;
	return 0;
}
