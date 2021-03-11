#include <stdio.h>
#include <malloc.h>


////////// functii cu argumente non-pointer

short int add(unsigned char x, unsigned char y) // transfer prin valoare pt x si y
{
	short int s = 0;

	x += 4; // modificare locala functiei; nu este vizibila in afara functiei
	s = x + y;

	return s;
}

short int add_ref(unsigned char &x, unsigned char y) // "transfer" prin referinta pt x si transfer prin valoare pt y
{
	short int s = 0;

	x += 4; // modificare directa a argumentului folosit pt x; este vizibila in afara functiei
	s = x + y;

	return s;
}

short int add_adr(unsigned char *x, unsigned char y) // transfer prin adresa pt x si transfer prin valoare pt y
{
	short int s = 0;

	*x += 4; // acces indirect la argumentul folosit pt x; este vizibila in afara functiei
	s = *x + y;

	return s;
}

////////// functii cu argument pointer

void add_pval(short int *x, unsigned char y) // transfer prin valoare pt x si transfer prin valoare pt y
{
	x = (short int*)malloc(sizeof(short int)); // acces la copia continutului lui a
	*x = y + 2;
}

void add_pref(short int * &x, unsigned char y) // "transfer" prin referinta pt x si transfer prin valoare pt y
{
	x = (short int*)malloc(sizeof(short int)); // acces direct la a
	*x = y + 2;
}


void add_padr(short int * *x, unsigned char y) // transfer prin adresa pt x si transfer prin valoare pt y
{
	*x = (short int*)malloc(sizeof(short int)); // acces indirect la a
	*(*x) = y + 2;
}

/////////////////////////////////

short int* add_pret(unsigned char y) // transfer prin adresa pt x si transfer prin valoare pt y
{
	short int * x = NULL;

	x = (short int*)malloc(sizeof(short int)); 
	*x = y + 2;

	return x;
}

int main()
{
	unsigned char a, b;
	a = 0x06; // a = 6
	b = 0x19; // b = 25
	short int sum = 0;

	////////////////

	sum = add(a, b);
	printf(" a = %d, b = %d, sum = %d\n", a, b, sum); // a nu se modifica la transferul prin valoare

	sum = add_ref(a, b);
	printf(" a = %d, b = %d, sum = %d\n", a, b, sum); // a se modifica direct la "transferul" prin referinta

	a = 0x06;
	sum = add_adr(&a, b);
	printf(" a = %d, b = %d, sum = %d\n", a, b, sum); // a se modifica indirect la transferul prin adresa

	////////////////

	a = 0x06;
	short int* px = NULL;
	add_pval(px, b);
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

	return 0;
}


