#include <stdio.h>
#include <malloc.h>

int suma(unsigned char x, unsigned char y) // transfer prin valoare a parametrilor
{
	int s;

	x += 2; // modificare locala 
	s = x + y;

	return s;
}

int suma_ref(unsigned char &x, unsigned char y) // transfer prin referinta a parametrului x
{
	int s;

	x += 2; // modificare x/a 
	s = x + y;

	return s;
}

int suma_adr(unsigned char *x, unsigned char y) // transfer prin adresa a parametrului x
{
	int s;

	*x += 2; // modificare indirecta a prin *x 
	s = *x + y;

	return s;
}

void suma_scalar(int *x, unsigned char y) // transfer prin valoare a parametrului x
{
	x = (int*)malloc(sizeof(int));
	*x = y + 3;
}

void suma_scalar_ref(int * &x, unsigned char y) // "transfer" prin referinta a parametrului x
{
	x = (int*)malloc(sizeof(int));
	*x = y + 3;
}

void suma_scalar_adr(int * *x, unsigned char y) // transfer prin adresa a parametrului x
{
	*x = (int*)malloc(sizeof(int));
	**x = y + 3;
}

int* suma_scalar_ret(unsigned char y) // transfer prin valoare a parametrului x
{
	int * x = (int*)malloc(sizeof(int));
	*x = y + 3;

	return x;
}

int main()
{
	unsigned char a = 0x10, b = 0x17; // a = 16, b = 23
	int sum = 0;

	// transfer prin valoare a si b
	sum = suma(a, b);
	printf(" a = %d, b = %d, suma = %d \n", a, b, sum); // a nu este modificat dupa apelul lui suma

	// "transfer" prin referinta a si transfer prin valoare pt b
	sum = suma_ref(a, b); // a este obligatoriu unsigned char
	printf(" a = %d, b = %d, suma = %d \n", a, b, sum); // a este modificat dupa apelul lui suma

	a = 0x10;
	// transfer prin adresa a si transfer prin valoare pt b
	sum = suma_adr(&a, b); // x este obligatoriu adresa (&a)
	printf(" a = %d, b = %d, suma = %d \n", a, b, sum); // a este modificat dupa apelul lui suma

	int *pz = NULL;
	suma_scalar(pz, b);
	// printf(" *pz = %d, b = %d \n", *pz, b); // pz NU este modificat dupa apelul lui suma_scalar

	suma_scalar_ref(pz, b);
	printf(" *pz = %d, b = %d \n", *pz, b); // pz este modificat dupa apelul lui suma_scalar_ref
	// dezalocare mem heap
	free(pz);
	pz = NULL;

	suma_scalar_adr(&pz, b);
	printf(" *pz = %d, b = %d \n", *pz, b); // pz este modificat dupa apelul lui suma_scalar_adr

	// dezalocare mem heap
	free(pz);
	pz = NULL;

	pz = suma_scalar_ret(b);
	printf(" *pz = %d, b = %d \n", *pz, b); // pz este modificat dupa atribuire cu adresa returnata de suma_scalar_ret

	// dezalocare mem heap
	free(pz);
	pz = NULL;

	return 0;

}