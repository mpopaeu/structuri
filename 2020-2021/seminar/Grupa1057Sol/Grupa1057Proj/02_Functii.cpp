#include <stdio.h>
#include <malloc.h>

short int suma(unsigned char x, unsigned char y) // x si y transferati prin valoare
{
	short int s = 0;

	x += 2;
	s = x + y;

	return s;
}

short int suma_adr(unsigned char *x, unsigned char y) // x transferat prin adresa, y transferat prin valoare
{
	short int s = 0;

	*x += 2; // continut modificat prin acces indirect la locatie de mem pe baza adresei stocate de x
	s = *x + y;

	return s;
}

short int suma_ref(unsigned char &x, unsigned char y) // x "transferat" prin referinta, y transferat prin valoare
{
	short int s = 0;

	x += 2; // continut modificat prin acces direct la locatie de mem aferenta argumentului de functie
	s = x + y;

	return s;
}

////////////////////////////////////

void suma_pointer(short int *x, unsigned char y) // x transferat prin adresa, y transferat prin valoare
{
	x = (short int*)malloc(sizeof(short int));
	*x = y + 4;
}

void suma_pointer_adr(short int* *x, unsigned char y) // x transferat prin adresa, y transferat prin valoare
{
	*x = (short int*)malloc(sizeof(short int));
	**x = y + 4;
}

void suma_pointer_ref(short int* &x, unsigned char y) // x "transferat" prin referinta, y transferat prin valoare
{
	x = (short int*)malloc(sizeof(short int));
	*x = y + 4;
}

////////////////////////////////////////////////////

short int* suma_pointer_ret(unsigned char y) 
{
	short int *x = NULL;
	x = (short int*)malloc(sizeof(short int));
	*x = y + 4;

	return x;
}


int main()
{
	unsigned char a, b;
	a = 0x11; // a = 17;
	b = 0x12; // b = 18;

	short int sum = 0;
	sum = suma(a, b);
	printf(" a = %d, b = %d, sum = %d\n", a, b, sum); // a nu este modificat

	sum = suma_adr(&a, b);
	printf(" a = %d, b = %d, sum = %d\n", a, b, sum); // a este modificat indirect in suma_adr

	a = 17;
	sum = suma_ref(a, b);
	printf(" a = %d, b = %d, sum = %d\n", a, b, sum); // a este modificat direct in suma_ref

	//////////////////////////
	
	// &sum = (short int*)malloc(sizeof(short int)); // &sum nu este modificabila; adresele de stack seg nu pot fi rescrise la runtime
	short int *ps = NULL;
	//suma_pointer(ps, b);
	//printf(" *ps = %d, b = %d\n", *ps, b); // ps nu este modificat; transfer ps prin valoare

	suma_pointer_adr(&ps, b);
	printf(" *ps = %d, b = %d\n", *ps, b); // ps este modificat indirect; transfer ps prin adresa

	free(ps);
	ps = NULL;

	suma_pointer_ref(ps, b);
	printf(" *ps = %d, b = %d\n", *ps, b); // ps este modificat direct; "transfer" ps prin referinta

	free(ps);
	ps = NULL;

	ps = suma_pointer_ret(b);
	printf(" *ps = %d, b = %d\n", *ps, b); // ps rescris cu rezultat return-at de functie

	free(ps);
	ps = NULL;

	return 0;
}