#include <stdio.h>
#include <malloc.h>

int main()
{
	char x = 'B';		// locatie de memorie de tip char --> 1 byte lungime
	char vx[10];		// locatie de memorie de tip vector --> max 10 elem de tip char; accesul se face prin operator de index cu argument de tip offset
	char *px = NULL;	// locatie de memorie de tip pointer la char --> stocheaza adresa de memorie de tip char
						// adresa de mem sigur este Adr(char) si poate fi: adr de stack seg SAU adr de heap seg

	// incarc o adresa de stack seg in px
	px = &x; // adresa lui x este incarcata in px
	*px = x + 1; // modificare indirecta a variabilei x; echivalent ca rezultat cu x = x + 1;

	// incarc adresa de inceput a vectorului
	px = vx; 
	for (char i = 0; i < sizeof(vx); i++)
		px[i] = x + i; // echivalent ca rezultat cu vx[i] = x + i;
						// px[i] echivalent *(px + i)


	// incarc adresa de heap seg; alocare mem heap prin apel functie malloc
	char n = sizeof(vx) - 3; // nr elemente vector in heap mem
	px = (char*)malloc(n); // n elemente vor avea continut arbitrar

	for (char i = 0; i < n; i++)
		px[i] = vx[i] + i;

	// dezaloc memorie heap (apel functie free() )
	free(px);
	px = NULL;

	int z = 0x01A54567; // implicit long int, 4 bytes; variabila locala in stack seg
	unsigned char *pz = (unsigned char*)&z; // declarat unsigned pentru a evita conversiile implicite

	for (char i = sizeof(int) - 1; i >= 0; i--)
		printf(" %02X ", pz[i]); // memoria la nivel de byte se afiseaza intocmai cu continutul binar la nivel fizic al memoriei
	printf("\n");

	pz[0] = 0x89;
	printf(" %02X ", z);


	return  0;
}