#include <stdio.h>

#define IMPL_VERSION 1

int main()
{

	int x = 7, y = 9, z;
	z = x + y;
	double a, c;


#if (IMPL_VERSION == 1)
	a = 7.8;
	c = a + z;
#else
	a = -9.2;
	c = a - z;
#endif

	printf("c = %lf\n", c);

	return 0;
}