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


void suma5(char a, char b, short int* *c)
{
	a += 2;
	b += 1;
	*c = (short int*)malloc(sizeof(short int));
	**c = a + b + 1;
}

int main()
{
	char x, y;
	short int z, *pi = NULL;
	x = 9;
	y = 11;
	z = 0;

	suma1(x, y, z); // parametrii trimisi prin valoare; retunr 0 rezultate

	printf("z = %d\n", z);
	printf("suma 2 z = %d\n", suma2(x, y)); // parameteri trimisi prin valoare; return rezultat

	z = 0;
	suma3(x, y, &z); // x si y trimisi prin valoare, z trimis prin adresa
	printf("suma 3 - z = %d\n", z);

	suma4(x, y, pi); // parametrii trimisi prin valoare, inclusiv c declarat ca adresa de short int
	//printf("suma 4 - *pi = %d\n", *pi);
	free(pi);

	suma5(x, y, &pi);
	printf("suma 5 - *pi = %d\n", *pi); // x si y trimisi prin valoare, pointer pi trimis prin adresa
	free(pi);
}