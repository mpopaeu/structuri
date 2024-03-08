#include <stdio.h>

short int add1(char x, char y)
{
	short int z = 0;

	x += 1;
	y += x;

	z = x + y;

	return z;

}

short int add2(char x, char* y)
{
	short int z = 0;

	x += 1;
	*y += x;

	z = x + *y;

	return z;
}

int main()
{
	char a = 3, b = 6;
	short int c = 0;

	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = add1(a, b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = add2(a, &b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	return 0;
}