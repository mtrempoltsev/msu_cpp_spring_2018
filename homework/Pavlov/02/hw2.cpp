	#include <iostream>
	#include "numbers.dat"

	int Search_Binary (const int arr[], int left, int right, int key)
	{
		int midd = 0;
		while (1)
		{
			midd = (left + right) / 2;

			if (key < arr[midd])
				right = midd - 1;
			else if (key > arr[midd])
				left = midd + 1;
			else
				return midd;

			if (left > right)
				return -1;
		}
	}



	int main(int argc, char* argv[])
	{
		if (!(argc & 1) || argc == 1) return -1;

		bool a[Data[Size-1]];
		a[0] = false;
		a[1] = false;

		for(int i = 2; i < Data[Size-1]; i++) {
			a[i] = true;
	    }

		for(int i = 2; i*i <= Data[Size-1]; i++) {
	        if(a[i] == true) {
	            for(int j = i*i; j < Data[Size-1]; j = j + i)
	            {
	                a[j] = false;
	            }
	        }
	    }

		for (int i = 1; i < argc; i += 2) {

			int b = std::atoi(argv[i]);
			int c = std::atoi(argv[i+1]);
			int p = 0;

			b = Search_Binary(Data, 0, Size, b);
			c = Search_Binary(Data, b, Size, c);

			for(int i = b; i <= c; i++) {
				if(a[Data[i]]) {
					p++;
				}
			}

			std::cout<<p<<"\n";
		}
	    return 0;
	}
