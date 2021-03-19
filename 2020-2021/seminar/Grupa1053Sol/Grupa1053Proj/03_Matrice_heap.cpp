#include <malloc.h>

#define TOP		1
#define BOTTOM	2
#define LEFT	3
#define RIGHT	4

// TEMA
// Iordache Denisa - actualizat
int** concatenare_matrice(int **pMat, unsigned char m, unsigned char n, int **pCat, unsigned char mc, unsigned char nc,
							char tip_operatie_concatenare)
{
	// pMat - pointer la matrice in heap
	// m - nr linii pMat
	// n - nr coloane pMat
	// pCat - pointer la matrice in heap
	// mc - nr linii pCat
	// nc - nr coloane pCat
	// tip_operatie_concatenare: TOP (pCat peste pMat), BOTTOM (pMat peste pCat), LEFT (pCat la stanga lui pMat),
	//							RIGHT (pCat la dreapta lui pMat)
	//
	// return: adresa de matrice obtinuta dupa concatenare, NULL daca matricele pMat si pCat nu au fost validate 
	//			dpv al operatiei de concatenare

	int** pRez = NULL;

	switch (tip_operatie_concatenare)
	{
	case TOP:
		if (n == nc)
		{
			pRez = (int**)malloc((m + mc) * sizeof(int*));
			for (unsigned char i = 0; i < m + mc; i++)
			{
				pRez[i] = (int*)malloc((n) * sizeof(int));
			}

			for (unsigned char i = 0; i < mc; i++)
			{
				for (unsigned char j = 0; j < nc; j++)
				{
					pRez[i][j] = pCat[i][j];
				}
			}

			for (unsigned char i = 0; i < m; i++)
			{
				for (unsigned char j = 0; j < n; j++)
				{
					pRez[i + mc][j] = pMat[i][j];
				}
			}
		}
		break;

	case BOTTOM:
		if (n == nc)
		{
			pRez = (int**)malloc((m + mc) * sizeof(int*));
			for (unsigned char i = 0; i < m + mc; i++)
			{
				pRez[i] = (int*)malloc((n) * sizeof(int));
			}

			for (unsigned char i = 0; i < m; i++)
			{
				for (unsigned char j = 0; j < n; j++)
				{
					pRez[i][j] = pMat[i][j];
				}
			}

			for (unsigned char i = 0; i < mc; i++)
			{
				for (unsigned char j = 0; j < nc; j++)
				{
					pRez[i + m][j] = pCat[i][j];
				}
			}
		}
		break;

	case LEFT:
		if (m == mc)
		{
			pRez = (int**)malloc((m) * sizeof(int*));
			for (unsigned char i = 0; i < m; i++)
			{
				pRez[i] = (int*)malloc((n + nc) * sizeof(int));
			}

			for (unsigned char i = 0; i < mc; i++)
			{
				for (unsigned char j = 0; j < nc; j++)
				{
					pRez[i][j] = pCat[i][j];
				}
			}

			for (unsigned char i = 0; i < m; i++)
			{
				for (unsigned char j = 0; j < n; j++)
				{
					pRez[i][j + nc] = pMat[i][j];
				}
			}
		}
		break;

	case RIGHT:
		if (m == mc)
		{
			pRez = (int**)malloc((m) * sizeof(int*));
			for (unsigned char i = 0; i < m; i++)
			{
				pRez[i] = (int*)malloc((n + nc) * sizeof(int));
			}

			for (unsigned char i = 0; i < m; i++)
			{
				for (unsigned char j = 0; j < n; j++)
				{
					pRez[i][j] = pMat[i][j];
				}
			}

			for (unsigned char i = 0; i < mc; i++)
			{
				for (unsigned char j = 0; j < nc; j++)
				{
					pRez[i][j + n] = pCat[i][j];
				}
			}
		}
		break;
	}

	return pRez;
}

int main()
{
	int ** pCat;
	int ** pMat; // pointer la masiv bi-dimensional (matrice)
	unsigned char m = 3, n = 2; // m - nr linii pMat, n - nr coloane pMat
	unsigned char mc, nc; // specificate de la tastatura; mc - nr linii pCat, nc - nr coloane pCat
	// int Mat[3][2]; -----> Mat[i][j]

	// alocare pMat
	pMat = (int**)malloc(m * sizeof(int*)); // alocare de vector cu adrese de inceput de linii (continut arbitrar)
	for (unsigned char i = 0; i < m; i++)
		pMat[i] = (int*)malloc(n * sizeof(int)); // alocare linie i cu elemente de tip int

	// "initializare" elemente pMat
	/*
	pMat
		1   2
		11 12
		21 22
	*/
	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			pMat[i][j] = i * 10 + j + 1;
	
	// alocare matrice pCat
	// ...

	// populare cu data pCat
	// ...

	// apel operatie de concatenare matrice
	int** pRez = concatenare_matrice(pMat, m, n, pCat, mc, nc, BOTTOM);

	unsigned char mr, nr; // mr nr linii pRez, nr - nr coloane pRez

	if (pRez == NULL)
	{
		// operatia de concatenare a esuat
	}
	else
	{
		// calculez mr si nr ca dimensiuni ale matricei
		// afisare matrice rezultate
	}

	// dezalocare pMat
	for (unsigned char i = 0; i < m; i++)
		free(pMat[i]); // dezalocare linie i cu elemente de tip int
	free(pMat); // dezalocare vector cu adrese de inceput de linii 

	// dezalocare pCat
	// ...

	// dezalocare pRez
	// ...

}