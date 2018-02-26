#include "matrix.hpp"
#include "timer.hpp"


int  main()
{

	int n = 2500;
	
	Matrix m(n);
	
	long long sum = 0;
	int n_iters = 200;
	Timer t(n_iters);
	for (int k = 0; k < n_iters; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				sum += m.getElement(i,j);
			}
		}
	}

	return 0;
}