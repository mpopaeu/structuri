

#include <stdio.h>
#include <malloc.h>

void main() {
	int a, va[10], *pa;
	int m[10][20], **pm; // m[i][j] - element de pe linia i si coloana j
						 // pm[i][j] - element de pe linia i si coloana j

	// alocare matrice in heap
	pm = (int**)malloc(10 * sizeof(int*)); // vector de pointeri la linii (fiecare element este adresa de inceput de linie)
	for (int i = 0; i < 10; i++)
		pm[i] = (int*)malloc(20 * sizeof(int)); // vector de intregi ce reprezinta continutul liniei i

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 20; j++)
			pm[i][j] = i * 2 + j;

	// dezalocare matrice (de int) in heap
	// in ordine inversa alocarii
	// se pleaca de la linii
	for (int i = 0; i < 10; i++)
		free(pm[i]);
	// dezalocare vector de pointeri la linii
	free(pm);

}