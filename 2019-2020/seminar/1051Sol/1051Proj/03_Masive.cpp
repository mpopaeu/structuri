#include <stdio.h>
#include <malloc.h>

#define VECTOR_SIZE 20
#define MAT_LINE_SIZE 10
#define MAT_CLM_SIZE 10

void modificaVector(int v[], int size) {
	for (int i = 0; i < size; i++)
		v[i] += i;
}

int** allocMatrice(int linii, int coloane) {
	int ** pm;		// pm[i][j]
	int m[10][20];	// m[i][j]

	pm = (int**)malloc(linii * sizeof(int*)); // structura intermediara - vector de adrese de inceput de linii

	for (int i = 0; i < linii; i++)
		pm[i] = (int*)malloc(coloane * sizeof(int)); // alocare spatiu mem heap pentru linia i

	for (int i = 0; i < linii; i++)
		for (int j = 0; j < coloane; j++)
			pm[i][j] = 0;

	return pm;
}


void main() {
	int m, v[20];

	for (int i = 0; i < VECTOR_SIZE; i++)
		v[i] = i * 10 + 1;

	
	for (int i = 0; i < VECTOR_SIZE; i++)
		printf(" %d ", v[i]);
	printf("\n");

	modificaVector(v, VECTOR_SIZE);
	for (int i = 0; i < VECTOR_SIZE; i++)
		printf(" %d ", v[i]);
	printf("\n");

	int ** pMat = allocMatrice(MAT_LINE_SIZE, MAT_CLM_SIZE);


	// dezalocare matrice pMat
	// in ordine inversa alocarii
	for (int i = 0; i < MAT_LINE_SIZE; i++)
		free(pMat[i]); // dezalocare linie i
	free(pMat); // dezalocare vector de pointeri catre linii

}