#include <stdio.h>
#include <malloc.h>

int main()
{
	char x = 70; // tipuri standard: [char, int,] [float, double, long double]
				// dim: sizeof(char) = 1 byte; variabila locala, alocare la compilare in stack seg
				// char x = 'F'; char x = 0x46;

	char vx[10]; // vector de elemente de tip char; dim = 10 * sizeof(char) = 10 bytes
				// alocare la compilare, variabila vx este locala in main(), rezervare 10 bytes in stack seg
				// 0xcc --- valoare arbitrare

	char * px = NULL; // variabila pointer; dim: sizeof(px) = 4 bytes; pointer de tip FAR seg : off, NEAR off
				// variabila locala, alocata la compilare in stack seg

	// incarc adresa de memorie in pointerul px
	// adresa stack seg a lui x
	px = &x; // exista 2 puncte de acces la locatia x: direct (x), indirect (px)
	*px = x + 2; // x se modifica in mod indirect prin utilizare variabile pointer px

	// incarc adresa de vector in var pointer px
	px = vx;
	for (char i = 0; i < sizeof(vx); i++)
		px[i] = x + 1; // px[i] <--> *(px + i)

	// alocare la run-time
	char n = sizeof(vx) - 3;

	px = (char*)malloc(n * sizeof(char));

	for (char i = 0; i < n; i++)
		px[i] = vx[i] + i;


	// dezalocare mem heap
	free(px);

	return 0;
}