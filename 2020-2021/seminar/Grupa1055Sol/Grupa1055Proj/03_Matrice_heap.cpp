#include <malloc.h>
#include <stdio.h>

#define TOP		1
#define BOTTOM	2
#define LEFT	3
#define RIGHT	4

int** concatenare_matrice(int **pMat, unsigned char m, unsigned char, int** pCat, unsigned char mc, unsigned char nc,
							char tip_operatie_concatenare)
{
	// pMat - adresa matrice alocata in mem heap
	// m - nr de linii matrice pMat
	// n - nr de coloane matrice pMat
	// pCat - adresa matrice alocata in mem heap
	// mc - nr de linii matrice pCat
	// nc - nr de coloane matrice pCat
	// tip_operatie_concatenare - tipul de concatenare: TOP (pCat peste pMat), BOTTOM (pMat peste pCat), LEFT (pCat la stanga lui pMat),
	//													RIGHT (pCat la dreapta lui pMat)
	//
	// return: adresa matrice obtinuta prin concatenare, NULL daca nu s-au indeplinit conditiile 
}

int main()
{
	int ** pCat; // matrice alocata in mem heap
	int ** pMat; // matrice alocata in mem heap
	unsigned char m = 3, n = 2; // m nr de linii, n nr de coloane
	unsigned char mc, nc; // mc nr linii pCat, nc nr coloane pCat

	// int Mat[3][3] ---> Mat[i][j]

	// alocare matrice pMat in mem heap 
	pMat = (int**)malloc(sizeof(int*) * m); // alocare vector de adrese de inceput de linii
	for (unsigned char i = 0; i < m; i++)
		pMat[i] = (int*)malloc(sizeof(int) * n); // alocare vector de elemente aferent liniei i

	// "initializare" elemente
	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			pMat[i][j] = i * 10 + j + 1;

	// alocare si initializare elemente matrice pCat
	printf("Nr linii pCat: ");
	scanf("%ud", &mc);
	printf("Nr coloane pCat: ");
	scanf("%ud", &nc);

	// alocare matrice pCat in mem heap 
	pCat = (int**)malloc(sizeof(int*) * mc); 
	for (unsigned char i = 0; i < mc; i++)
		pCat[i] = (int*)malloc(sizeof(int) * nc); 
	// "initializare" elemente pCat
	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			pCat[i][j] = (i + 1) + (j + 1);

	// TEMA
	int ** pRez;
	unsigned char mr = 0, nr = 0; // 
	pRez = concatenare_matrice(pMat, m, n, pCat, mc, nc, BOTTOM);

	if (pRez == NULL)
	{
		// Matricea rezultat nu s-a creat
		printf("Operatia nu a avut loc!!!\n");
	}
	else
	{
		// Se calculeaza mr si nr ca dimensiuni ale matrice rezultat pRez din concatenare

		// Afisare matrice rezultat

	}


	// dezalocare matrice pMat in mem heap
	for (unsigned char i = 0; i < m; i++)
		free(pMat[i]); // dezalocare vector cu elemente de pe linia i
	free(pMat); // dezalocare vector de adrese de inceput de linii


	// dezalocare matrice pCat
	for (unsigned char i = 0; i < mc; i++)
		free(pCat[i]); // dezalocare vector cu elemente de pe linia i
	free(pCat);

	// dezalocare matrice pRez
	for (unsigned char i = 0; i < mr; i++)
		free(pRez[i]); // dezalocare vector cu elemente de pe linia i
	free(pRez);
}