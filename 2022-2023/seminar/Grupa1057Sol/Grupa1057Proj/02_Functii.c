#include <stdio.h>
#include <malloc.h>

void suma1(char a, char b, short int c)
{
	a += 2;
	b += 1;
	c = a + b + 1;
}

short int suma2(char a, char b)
{
	short int c;
	a += 2;
	b += 1;
	c = a + b + 1;

	return c;
}

void suma3(char a, char b, short int *c)
{
	a += 2;
	b += 1;
	*c = a + b + 1;
}

void suma4(char a, char b, short int* c)
{
	a += 2;
	b += 1;
	c = (short int*)malloc(sizeof(short int));
	*c = a + b + 1;
}

int main()
{
	char x, y;
	short int z, *pi = NULL;
	x = 9;
	y = 11;
	z = 0;

	suma1(x, y, z);

	printf("z = %d\n", z);
	printf("Suma = %d\n", suma2(x, y));

	z = 0;
	suma3(x, y, &z);
	printf("z = %d\n", z);

	suma4(x, y, pi);
	printf("*pi = %d\n", *pi);
}