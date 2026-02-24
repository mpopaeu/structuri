#include <stdio.h>
#include <malloc.h>

int main()
{
	char x = 13;
	char y = -13;

	printf("x = %d\n", x);
	printf("y = %d\n", y);

	printf("Adresa(x) = 0x%p\n", &x);
	printf("Adresa(y) = 0x%p\n", &y);

	char* pc = NULL;
	printf("pc = 0x%p\n", pc);
	printf("adresa(pc) = 0x%p\n", &pc);

	pc = &x;
	printf("---------------------------\n");
	printf("pc = 0x%p\n", pc);
	printf("adresa(pc) = 0x%p\n", &pc);

	*pc = x + 1; // pc[0] = x + 1;
	printf("x = %d\n", x);
	printf("Adresa(x) = 0x%p\n", &x);

	char v[] = {1, 2, 3, 4, 5, 6, 7};
	printf("Dimensiune v = %d bytes\n", sizeof(v));
	printf("Dimensiune pc = %d bytes\n", sizeof(pc));

	// &x = &y + 1; // nu se pot modifica adresele constante de staick seg

	pc = v;
	printf("Dimensiune v = %d bytes\n", sizeof(v));
	printf("Dimensiune pc = %d bytes\n", sizeof(pc));


	pc = (char*)malloc(sizeof(v) * sizeof(char));

	for (unsigned char i = 0; i < sizeof(v); i++)
		pc[i] = v[i] + 1;

	char m[][3] = { {1, 2, 3}, {3, 2, 1} };

	char** pm = NULL;
	pm = malloc(2 * sizeof(char*)); // alocare structura intermediara cu pointeri catre linii (2 linii)
	for (unsigned char i = 0; i < 2; i++)
		pm[i] = malloc(3 * sizeof(char)); // alocare linie i (3 elem per linie -> 3 coloane)
										  // adresa obtinuta este stocata pe struct intermdiara


	for (unsigned char i = 0; i < 2; i++)
		for (unsigned char j = 0; j < 3; j++)
			pm[i][j] = m[i][j] + 1; // acces la elementele [i,j] din ambele matrice


	// dezalocare vector in heap
	free(pc);
	pc = NULL;

	//printf("Acces la heap dupa dezalocare -> pc[0] = %d\n", pc[0]); // eroare de run-time deoarece pc este NULL
	
	// dezalocare matrice in heap
	// are loc invers alocarii pentru a evita aparitia de memory leaks
	for (unsigned char i = 0; i < 2; i++)
		free(pm[i]); // dezalocare linie i
	free(pm); // dezalocare structura intermediara (adrese de inceput de linii)
	pm = NULL;
	
	return 0;
}