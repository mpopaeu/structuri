
#include <stdio.h>
#include <malloc.h>

short int add(unsigned char x, unsigned char y) // transfer prin valoare pt x si y
{
	short int s = 0;

	x += 3; // modificare locala functiei
	s = x + y;

	return s;
}


short int add_ref(unsigned char &x, unsigned char y) // "transfer" prin referinta x si transfer prin valoare y
{
	short int s = 0;

	x += 3; // modificare directa argument; modificare vizibila in apelator
	s = x + y;

	return s;
}

short int add_adr(unsigned char *x, unsigned char y) // transfer prin adresa x si transfer prin valoare y
{
	short int s = 0;

	*x += 3; // modificare indirecta argument; modificare vizibila in apelator
	s = *x + y;

	return s;
}


void add_pval(short int *x, unsigned char y) // transfer prin valoare pt x si y
{
	x = (short int *)malloc(sizeof(short int));
	*x = y + 2;
}

void add_pref(short int * &x, unsigned char y) // "transfer" prin referinta pt x si prin valoare pt y
{
	x = (short int *)malloc(sizeof(short int));
	*x = y + 2;
}

void add_padr(short int * *x, unsigned char y) // transfer prin adresa pt x si prin valoare pt y
{
	*x = (short int *)malloc(sizeof(short int)); // modificare indirecta a argumentului (rescriere)
	**x = y + 2;
}

short int* add_pret(unsigned char y) // adresa de heap alocata in functie se returneaza in apelator unde se salveaza in locatie destinatie
{
	short int * x;
	x = (short int *)malloc(sizeof(short int));
	*x = y + 2;

	return x;
}


int main()
{
	unsigned char a = 13, b = 19;
	short int sum = 0;

	sum = add(a, b);
	printf(" a = %d, b = %d, suma = %d\n", a, b, sum);

	sum = add_ref(a, b);
	printf(" a = %d, b = %d, suma = %d\n", a, b, sum);

	a = 13;
	sum = add_adr(&a, b);
	printf(" a = %d, b = %d, suma = %d\n", a, b, sum);

	/////////

	short int * px = NULL;
	//add_pval(px, b);
	//printf(" *px = %d, b = %d\n", *px, b);

	add_pref(px, b);
	printf(" *px = %d, b = %d\n", *px, b);

	free(px);
	px = NULL;

	add_padr(&px, b);
	printf(" *px = %d, b = %d\n", *px, b);

	free(px);
	px = NULL;

	px = add_pret(b);
	printf(" *px = %d, b = %d\n", *px, b);

	free(px);
	px = NULL;

	//short int vsum[10];
	//vsum = (short int*)malloc(sizeof(short int));

	return 0;
}