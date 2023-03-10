#include <stdio.h>


void add1(char x, char y, short int z)
{
	x += 1;
	y -= 2;
	z = x + y + 1;
}

short int add2(char x, char y)
{
	x += 1;
	y -= 2;
	short int z = x + y + 1;

	return z;
}

int main()
{
	char a, b;
	short int c = 0;

	a = 11;
	b = 12;

	add1(a, b, c);
	printf("c = %d\n", c);
	printf("add2 = %d\n", add2(a, b));

	return 0;
}