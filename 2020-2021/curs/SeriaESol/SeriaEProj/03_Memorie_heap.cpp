#include <stdio.h>
#include <malloc.h>

int main()
{
	int ** pMat;
	int m = 2; // numar de linii
	int n = 3; // numar de coloane

	pMat = (int**)malloc(m * sizeof(int*)); // alocare spatiu pentru m pointeri de linii, continut arbitrar (nici o adresa valida de heap)

	for (int i = 0; i<m; i++) {
		pMat[i] = (int*)malloc(n * sizeof(int)); // alocare spatiu pentru n elemente pe linie (elemente int cu continut arbitrar)		
	}

	printf("\nCont(pMat) = %p\n", pMat);
	for (int i = 0; i<m; i++)
		printf("Cont(pMat[%d]) = %p  ", i + 1, pMat[i]); // afisare adrese de inceput ale liniilor


	for (int i = 0; i<m; i++) {
		for (int j = 0; j<n; j++) {
			pMat[i][j] = i * 10 + j; // initializare valoare element matrice
		}
	}

	for (int i = 0; i<m; i++) {
		printf("\n\n");
		for (int j = 0; j<n; j++) {
			//printf("Adr(pMat[%d][%d]) = %p  ", i+1, j+1, &pMat[i][j]); // afisare adrese de inceput ale liniilor
			printf("Adr(pMat[%d][%d]) = %p  ", i + 1, j + 1, *(pMat + i) + j); // afisare adrese de inceput ale liniilor
		}
	}

	// operatii matrice
	int suma = 0;
	for (int i = 0; i<m; i++) {
		for (int j = 0; j<n; j++) {
			suma = suma + pMat[i][j];
		}
	}
	printf("\nSuma este = %d \n", suma);

	// dealocare matrice in heap
	for (int i = 0; i < m; i++)
		free(pMat[i]);
	free(pMat);
	pMat = NULL;


	return 0;
}