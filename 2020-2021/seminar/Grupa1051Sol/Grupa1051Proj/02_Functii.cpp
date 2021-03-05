#include <stdio.h>
#include <malloc.h>

short int suma(unsigned char x, unsigned char y) // x si y sunt transferati prin valoare
{
	short int s = 0;

	x += 3;
	s = x + y;

	return s;
}


short int suma_adr(unsigned char *x, unsigned char y) // x transferat prin adresa, y transferat prin valoare
{
	short int s = 0;

	*x += 3; // se acceseaza indirect continutul de la adresa stocata de x
	s = *x + y;

	return s;
}


short int suma_ref(unsigned char &x, unsigned char y) // x "transferat" prin referinta, y transferat prin valoare
{
	short int s = 0;

	x += 3; // se acceseaza direct continutul x
	s = x + y;

	return s;
}


void suma_pointer_val(short int *x, unsigned char y) // x transferat prin adresa, y transferat prin valoare
{
	y += 5;

	x = (short int*)malloc(sizeof(short int));
	*x = y;
}

void suma_pointer_ref(short int *&x, unsigned char y) // x "transferat" prin referinta, y transferat prin valoare
{
	y += 5;

	x = (short int*)malloc(sizeof(short int));
	*x = y;
}

void suma_pointer_adr(short int* *x, unsigned char y) // x transferat prin adresa, y transferat prin valoare
{
	y += 5;

	*x = (short int*)malloc(sizeof(short int)); // acces indirect la ps (adresa stocata de ps in functia main)
	**x = y; // acces indirect la ps + acces indirect din ps catre mem heap
}

short int* suma_pointer_scalar(unsigned char y) 
{
	y += 5;

	short int *x = (short int*)malloc(sizeof(short int)); 
	*x = y; 

	return x;
}


int main()
{
	unsigned char a = 10, b = 14;
	short int sum = 0;

	// transfer prin valoare a si b
	sum = suma(a, b);
	printf(" a = %d, b = %d, sum = %d\n", a, b, sum); // a si b isi pastreaza valorile; a nu este modificat prin functia suma

	// transfer prin adresa a si transfer prin valoare b
	sum = suma_adr(&a, b);
	printf(" a = %d, b = %d, sum = %d\n", a, b, sum); // a isi modifica valoarea; b isi pastreaza continutul/valoare 

	// "transfer" prin referinta a si transfer prin valoare b
	a = 10;
	sum = suma_ref(a, b);
	printf(" a = %d, b = %d, sum = %d\n", a, b, sum); // a isi modifica valoarea; b isi pastreaza continutul/valoare 

	short int * ps = NULL;
	// transfer prin valoare ps si b
	// suma_pointer_val(ps, b);
	// printf(" *ps = %d, b = %d\n", *ps, b); // ps nu se modifica; exceptie pt nullptr in ps

	// "transfer" prin referinta ps, prin valoare b
	suma_pointer_ref(ps, b);
	printf(" *ps = %d, b = %d\n", *ps, b); // ps se modifica
	
	//dezalocare mem heap
	free(ps);
	ps = NULL;

	// transfer prin adresa ps, prin valoare p
	suma_pointer_adr(&ps, b);
	printf(" *ps = %d, b = %d\n", *ps, b); // ps se modifica indirect din functie

	//dezalocare mem heap
	free(ps);
	ps = NULL;

	ps = suma_pointer_scalar(b);
	printf(" *ps = %d, b = %d\n", *ps, b); // ps se modifica indirect din functie

	//dezalocare mem heap
	free(ps);
	ps = NULL;

	return 0;
}