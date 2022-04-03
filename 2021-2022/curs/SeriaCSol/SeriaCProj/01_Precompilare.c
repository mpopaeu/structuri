
#include <stdio.h>

#define BRANCH 1

void main()
{

	int x = 7, y = 9, z;
	z = x + y;

#if BRANCH == 1
	float a = 7.8f, c;
	c = a + z;
#else
	int a = -9, c;
	c = a - z;
#endif

#if BRANCH == 1
	printf("\n c = %f", c);
#else
	printf("\n c = %d", c);
#endif
}