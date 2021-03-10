#include <malloc.h>

#define INSERARE 1
#define STERGERE 2

int** op_elem_matrice(int** pMat, char &m, char * &dim_linii, char op_linie, int val_elem, char op_tip)
{
	// pMat - adresa matrice alocate in heap
	// m - nr de linii al matricei
	// dim_linii - vector cu dimensiuni reale/concrete la runtime ale liniilor
	// op_linie - linia pt care se aplica operatia op_tip
	// val_elem - valoare element pentru care se aplica operatia op_tip
	// op_tip - tip operatie: INSERARE / STERGERE
}

int main()
{
	int ** pMat;
	char m = 3, n = 2;	

	// alocare matrice heap
	pMat = (int**)malloc(m * sizeof(int*));
	for (char i = 0; i < m; i++)
		pMat[i] = (int*)malloc(n * sizeof(int));

	// stocare valori semnificative
	for (char i = 0; i < m; i++)
		for (char j = 0; j < n; j++)
			pMat[i][j] = i * 10 + (j + 1);

	/*
	pMat
	1   2 3 4 5
	11
	31 32 33
	*/

	char * dim_linii = (char*)malloc(m * sizeof(char));
	for (char i = 0; i < m; i++)
		dim_linii[i] = n;

	char linie = 1;
	int val_elem = 101;
	char tip_operatie = INSERARE;

	// INSERARE - noul element va fi adaugat la sfarsitul liniei
	// STERGERE - se elimina elementul de pe ultima pozitie pe linia specificata de var linie
	// TEMA !!! 17 Martie 2021
	pMat = op_elem_matrice(pMat, m, dim_linii, linie, val_elem, tip_operatie);

	int Mat[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

	// dezalocare matrice heap
	for (char i = 0; i < m; i++)
		free(pMat[i]); // dezalocarea liniilor cu valori intregi semnificative pt implementare
	free(pMat);
}