#include <malloc.h>

int main()
{
	int ** pMat;
	char m = 3, n = 2;

	// alocare
	pMat = (int**)malloc(m * sizeof(int*)); // vector cu adrese de inceput a liniilor
	for (char i = 0; i < m; i++)
		pMat[i] = (int*)malloc(n * sizeof(int));


	for (char i = 0; i < m; i++)
		for (char j = 0; j < n; j++)
			pMat[i][j] = i * 10 + (j + 1);

	/* pMat
	1  2 
	11 12
	21 22 23
	*/

	/*
	1   2  3
	11 12 13
	21 22 23 24 25
	31
	41 42
	*/

	char * dim_linii = (char*)malloc(m * sizeof(char));
	for (char i = 0; i < m; i++)
		dim_linii[i] = n;



	// dezalocare
	for (char i = 0; i < m; i++)
		free(pMat[i]);
	free(pMat);

	int Mat[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

	// TEMA - gestionare dinamca a matricei pMat prin adaugarea de valori pe linii si adaugarea de linii la matrice
	// intr-o functie

	return 0;
}