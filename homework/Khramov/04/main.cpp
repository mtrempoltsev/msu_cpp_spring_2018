#include "Matrix.h"

int main()
{
    int n = 0;

    Matrix m1(3, 2);
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            m1[j][i] = ++n;
        }
    }

	Matrix m(3,3);
	return 0;
}

