#include <malloc.h>

#define TOP		1
#define BOTTOM	2
#define LEFT	3
#define RIGHT	4

// Andrei Ana Maria - actualizat
int** concatenare_matrice(int** pMat, unsigned char m, unsigned char n, int** pCat, unsigned char mc, unsigned char nc,
							char tip_operatie_concat)
{
	// pMat - matrice input in operatia de concatenare
	// m - nr linii pMat
	// n - nr coloane pMat
	// pCat - matrice input in operatia de concatenare
	// mc - nr linii pCat
	// nc - nr coloane pCat
	// tip_operatie_concat - tipul de concatenare: TOP (pCat peste pMat), BOTTOM (pMat peste pCat)
	//		LEFT (pCat la stanga lui pMat), RIGHT (pCat la dreapta lui pMat)
	//
	// return - Matrice rezultat cu elemente concatenate din pMat si pCat

	int** matFin;

	if (tip_operatie_concat == TOP) {
		//aloc spatiu pt MatFin
		matFin = (int**)malloc(sizeof(int*) * (m + mc));
		//aloc pt prima jumatate a matricii rezultate
		for (unsigned char i = 0; i < (m + mc); i++) {
			matFin[i] = (int*)malloc(sizeof(int) * n);
		}

		//populez matricea
		for (unsigned char i = 0; i < mc; i++) {
			for (unsigned char j = 0; j < nc; j++) {
				matFin[i][j] = pCat[i][j];
			}
		}
		for (unsigned char i = mc; i < m + mc; i++) {
			for (unsigned char j = 0; j < n; j++) {
				matFin[i][j] = pMat[i - mc][j];
			}
		}
		return matFin;
	}


	if (tip_operatie_concat == BOTTOM) {
		matFin = (int**)malloc(sizeof(int*)*(m + mc));
		for (unsigned char i = 0; i < (m + mc); i++) {
			matFin[i] = (int*)malloc(sizeof(int) * n);
		}

		for (unsigned char i = 0; i < m; i++) {
			for (unsigned char j = 0; j < n; j++) {
				matFin[i][j] = pMat[i][j];
			}
		}
		for (unsigned char i = m; i < m + mc; i++) {
			for (unsigned char j = 0; j < nc; j++) {
				matFin[i][j] = pCat[i - m][j];
			}
		}
		return matFin;
	}

	if (tip_operatie_concat == LEFT) {
		matFin = (int**)malloc(sizeof(int*) * m);
		for (unsigned char i = 0; i <m; i++) { //am alocat spatiu pt toata matricea
			matFin[i] = (int*)malloc(sizeof(int) * (n + nc));
		}
		
		for (unsigned char i = 0; i < mc; i++) {
			for (unsigned char j = 0; j <nc; j++) {
				matFin[i][j] = pCat[i][j];
			}
		}

		for (unsigned char i = 0; i < m; i++) {
			for (unsigned char j = nc; j < n + nc; j++) {			
				matFin[i][j] = pMat[i][j - nc];
			}
		}
		return matFin;
	}

	if (tip_operatie_concat == RIGHT) {
		matFin = (int**)malloc(sizeof(int*) * m);
		for (unsigned char i = 0; i < m; i++) { //am alocat spatiu pt toata matricea
			matFin[i] = (int*)malloc(sizeof(int) * (n + nc));
		}
		for (unsigned char i = 0; i < m; i++) {
			for (unsigned char j = 0; j < n; j++) {
				matFin[i][j] = pMat[i][j];
			}
		}

		for (unsigned char i = 0; i < mc; i++) {
			for (unsigned char j = n; j < n + nc; j++) {
				matFin[i][j] = pCat[i][j - n];
			}
		}
		return matFin;
	}
}

int main()
{
	int ** pCat, ** pRez;
	int ** pMat;
	unsigned char m = 3, n = 2; // m - nr linii pMat, n - nr coloane pMat
	unsigned char mc, nc; // mc - nr linii pCat, nc - nr coloane pCat

	// alocare pCat + initializare pCat
	// ......


	// alocare pMat
	pMat = (int**)malloc(sizeof(int*) * m); // vector de adrese de inceput de linii
	for (unsigned char i = 0; i < m; i++)
		pMat[i] = (int*)malloc(sizeof(int) * n);

	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			pMat[i][j] = i * 10 + (j + 1);

	// int Mat[3][3]; // Mat[i][j]

	// concatenare elemente matrice pMat si pCat
	// TEMA 
	pRez = concatenare_matrice(pMat, m, n, pCat, mc, nc, TOP);

	// afisre matrice rezultat

	// dezalocare pMat
	for (unsigned char i = 0; i < m; i++)
		free(pMat[i]);
	free(pMat);

	// dezalocare pCat
	// ....

	// dezalocare matrice cu elemente concatenate pRez

	return 0;
}