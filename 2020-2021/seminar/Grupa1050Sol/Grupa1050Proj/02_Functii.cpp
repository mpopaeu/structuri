#include <stdio.h>
#include <malloc.h>

short int add(unsigned char x, unsigned char y) // transfer prin valoare x si y
{
	short int s = 0;

	x += 3;
	s = x + y;

	return s;
}

short int add_ref(unsigned char &x, unsigned char y) // "transfer" prin referinta x si transfer prin valoare y
{
	short int s = 0;

	x += 3;
	s = x + y;

	return s;
}

short int add_adr(unsigned char *x, unsigned char y) // transfer prin adresa x si transfer prin valoare y
{
	short int s = 0;

	*x += 3;
	s = *x + y;

	return s;
}

/////////////////////////////////////////////

void add_pval(short int *x, unsigned char y) // transfer pointer x prin valoare, transfer y prin valoare
{	
	x = (short int *)malloc(sizeof(short int));
	*x = y + 5;
}

void add_pref(short int *&x, unsigned char y) // "transfer" pointer x prin referinta, transfer y prin valoare
{
	x = (short int *)malloc(sizeof(short int));
	*x = y + 5;
}

void add_padr(short int * *x, unsigned char y) // transfer pointer x prin adresa, transfer y prin valoare
{
	*x = (short int *)malloc(sizeof(short int)); // accesez argumentul in mod indirect (px alocat in stack seg in main())
	**x = y + 5; // salt 1 pt acces la px, salt 2 pt acces la mem heap
}

short int* add_pret(unsigned char y) // transfer pointer x prin adresa, transfer y prin valoare
{
	short int * x = NULL;
	x = (short int *)malloc(sizeof(short int)); 
	*x = y + 5; 

	return x;
}


int main()
{
	unsigned char a = 0x12, b = 0x1A; // a = 18, b = 26
	short int sum = 0;

	///////////////// transfer variabila non-pointer in functie
	sum = add(a, b);
	printf(" a = %d, b = %d, suma = %d\n", a, b, sum); // a nemodificat

	sum = add_ref(a, b);
	printf(" a = %d, b = %d, suma = %d\n", a, b, sum); // a modificat direct din functie

	a = 0x12;
	sum = add_adr(&a, b);
	printf(" a = %d, b = %d, suma = %d\n", a, b, sum); // a modificat indirect din functie

	a = 0x12;
	///////////////// transfer variabila pointer in functie
	short int *px = NULL;
	add_pval(px, b); // generare de mem leak
	// printf(" *px = %d, b = %d\n", *px, b); // px nu se modifica, contine NULL la terminarea lui add_pval

	add_pref(px, b);
	printf(" *px = %d, b = %d\n", *px, b); // px se modifica prin acces direct la px

	free(px);
	px = NULL;

	add_padr(&px, b);
	printf(" *px = %d, b = %d\n", *px, b); // px se modifica prin acces indirect la px 

	free(px);
	px = NULL;

	px = add_pret(b);
	printf(" *px = %d, b = %d\n", *px, b); // px rescrie cu adresa returnata de functie

	free(px);
	px = NULL;

	return 0;
}