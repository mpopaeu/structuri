#include <stdio.h>
#include <malloc.h>

int main()
{
	// Tipuri de date standard: [char, int,] [float, double, long double]
	char x = 0x5f; // echiv cu val 95 in baza 10; x var locala in stack seg
	char vx[10];   // vx este var locala (vector); se aloca in stack; continut arbitrar pe cele 10 elem
	char *px = NULL; // px var locala (pointer FAR) se aloca in stack seg; 

	// incarc px cu adrese de stack seg
	px = &x; // adresa de stack seg pt x
	*px = x + 1; // modificare indirecta a lui x

	px = vx; // incarc px cu adresa de inceput a vectorului vx
	for (char i = 0; i < sizeof(vx); i++)
		px[i] = x + i; // elementul cu offset i este modificat in vector; echiv vx[i] = x + i;
						// px[i] este echiv cu *(px + i)

	// incarc px cu adrese de heap seg
	char n = sizeof(vx) - 2; // dimensiune vector alocat in heap seg

	px = (char*)malloc(sizeof(char) * n);
	for (char i = 0; i < n; i++)
		px[i] = vx[i] + i;

	// dezaloc heap mem
	free(px);
	px = NULL;
	// px[0] = vx[0] + 3;

	int z = 0x1122D178;
	px = (char*)&z;

	for (char i = sizeof(int) - 1; i >= 0 ; i--)
		printf(" %02X ", (unsigned char)px[i]);
	printf("\n");

	return 0;
}