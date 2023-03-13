#include <stdio.h>

void suma1(char a, char b, short int c)
{
	a += 1;
	b -= 2;
	c = a + b + 1;
}

short int suma2(char a, char b)
{
	a += 1;
	b -= 2;
	return (a + b + 1);
}

void suma3(char a, char b, short int *c)
{
	a += 1;
	b -= 2;
	*c = a + b + 1;
}

void suma4(char a, char b, short int* c)
{
	a += 1;
	b -= 2;
	c = (short int*)malloc(sizeof(short int));
	*c = a + b + 1;
}

short int* suma5(char a, char b)
{
	a += 1;
	b -= 2;
	short int *c = (short int*)malloc(sizeof(short int));
	*c = a + b + 1;
	return c;
}

void suma6(char a, char b, short int* *c)
{
	a += 1;
	b -= 2;
	*c = (short int*)malloc(sizeof(short int));
	**c = a + b + 1;
}

int main()
{
	char x, y;
	short int z = 0;

	x = 11;
	y = 13;

	suma1(x, y, z);
	printf("z = %d\n", z);
	
	printf("suma = %d\n", suma2(x, y));

	suma3(x, y, &z);
	printf("z = %d\n", z);


	short int* pz = NULL;
	suma4(x, y, pz);
	// printf("pz suma4 = %d\n", *pz);

	pz = suma5(x, y);
	printf("pz suma5 = %d\n", *pz);
	free(pz);
	pz = NULL;

	suma6(x, y, &pz);
	printf("pz suma6 = %d\n", *pz);
	free(pz);

	return 0;
}