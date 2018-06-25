#include "huff.h"
int main(int argc, char **argv)
{
	if(argc!=3)
	{
		std::cout << "Usage: " << argv[0] << " <archive_name> <output_name>\n";
		return -1;
	}
	uint32_t res=RCode(argv[1], argv[2]);
	//std::cout << res <<std::endl;
	return 0;
}
