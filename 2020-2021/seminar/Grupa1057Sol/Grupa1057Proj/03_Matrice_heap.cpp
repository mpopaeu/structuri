#include <malloc.h>

#define INSERARE 1
#define STERGERE 2

unsigned char op_mat_elem(int ** &pMat, unsigned char * &dim_linii, unsigned char nr_linii, 
							int val_elem, unsigned char op_linie, char op_tip)
{
	// pMat - matricea cu date care are o evolutie dinamica la nivel de structura (linii/coloane)
	// dim_linii - vector cu dimensiuni efective de linii din matricea pMat
	// nr_linii - nr de linii al matricei; identici cu nr de elemenete din dim_linii
	// val_elem - valoare element care se insereaza in matrice; este ignorat in cazul operatiei de STERGERE
	// op_linie - nr de linie pe care se aplica operatia de INSERARE / STERGERE
	// op_tip - tipul operatiei: INSERARE / STERGERE
	// return: posibila nou nr de linii pMat si elemente in dim_linii, pMat modificat la nivel de linii, dim_linii modificat ca nr de elemente
}

int main()
{
	int ** pMat;
	unsigned char m = 3, n = 2; // m linii, n coloane

	// alocare matrice in mem heap
	pMat = (int**)malloc(m * sizeof(int*)); // alocare vector de adrese de inceput a liniilor
	for (unsigned char i = 0; i < m; i++)
		pMat[i] = (int*)malloc(n * sizeof(int)); // alocare vector cu valori ale liniei i

	// incarcare matrice cu valori
	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			pMat[i][j] = i * 10 + (j + 1);

	/*
	pMat
		1   2
		11 12 13
		31
	*/
	unsigned char* dim_linii = (unsigned char*)malloc(m * sizeof(unsigned char)); // fiecare element i corespunde unei linii i din pMat
	for (unsigned char i = 0; i < m; i++)
		dim_linii[i] = n; // nr initial de elemente pe fiecare linie

	int Mat[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

	// TEMA - implementare operatii de INSERARE si STERGERE

	// dezalocare matrice
	for (unsigned char i = 0; i < m; i++)
		free(pMat[i]);
	free(pMat);

}