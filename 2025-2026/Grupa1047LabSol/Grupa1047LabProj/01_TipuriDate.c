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
	printf("Adresa(pc) = 0x%p\n", &pc);

	pc = &y;
	printf("pc = 0x%p\n", pc);
	printf("Adresa(pc) = 0x%p\n", &pc);
	*pc = y + 15;
	printf("y = %d\n", y);

	char v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	printf("Adresa(v) = 0x%p\n", &v);
	printf("Dimensiune(v) = %d\n", sizeof(v));
	printf("Dimensiune(pc) = %d\n", sizeof(pc));

	pc = malloc(sizeof(v)); // alocare mem heap pe sizeof(v) bytes
	unsigned char dim_vpc_bytes = sizeof(v); // nr de elemente; fiecare element ocupa 1 byte

	for (unsigned char i = 0; i < dim_vpc_bytes - 1; i++)
		pc[i] = 'A' + v[i];
	pc[dim_vpc_bytes - 1] = 0; // scrie byte cu valoare 0 pe ultima pozitie din vector in heap

	printf("\n\n");
	for (unsigned char i = 0; i < dim_vpc_bytes; i++)
		printf(" %c -> %d \n", pc[i], pc[i]);
	printf("\n\n");

	printf(" %s ", pc);
	printf("\n\n");

	char m[][3] = { {9,9,9}, {3,2,1} };

	char** pm = NULL;

	pm = malloc(2 * sizeof(char*)); // alocare structura intermediara cu adrese de linii
	for (unsigned char i = 0; i < 2; i++)
		pm[i] = malloc(3 * sizeof(char)); // alocare linie i; adresa obtinuta se pune pe structura intermediara alocata mai sus

	for (unsigned char i = 0; i < 2; i++)
		for (unsigned char j = 0; j < 3; j++)
			pm[i][j] = m[i][j] + 1;


	// dezalocare vector pc
	free(pc); // dezalocare mem heap
	pc = NULL;

	/* // acces la memoria heap dupa dezalocare
	printf("\n\n");
	for (unsigned char i = 0; i < dim_vpc_bytes; i++)
		printf(" %c -> %d \n", pc[i], pc[i]);
	printf("\n\n");

	printf(" %s ", pc);
	printf("\n\n");
	*/

	// dezalocare matrice pm
	// ordine inversa fata de alocare
	for (unsigned char i = 0; i < 2; i++)
		free(pm[i]); // dezalocare linie i a carei adresa de inceput se afla in structura intermediara
	free(pm); // dezalocare structura intermediara

	pm = NULL;

	return 0;
}