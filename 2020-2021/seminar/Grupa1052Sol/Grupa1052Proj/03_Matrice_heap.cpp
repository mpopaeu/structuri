#include <malloc.h>
#include <stdio.h>

#define INSERARE 1
#define STERGERE 2

int** op_elem_matrice(int** pMat, char &m, char * &dim_linii, char op_linie, int val_elem, char op_tip)
{
	// pMat - adresa matrice alocate in heap
	// m - nr de linii al matricei
	// dim_linii - vector cu dimensiuni reale/concrete la runtime ale liniilor
	// op_linie - linia pt care se aplica operatia op_tip
	// val_elem - valoare element pentru care se aplica operatia op_tip; considerat doar la inserare
	// op_tip - tip operatie: INSERARE / STERGERE
	// INSERARE - val_elem se adauga la sfarsitul liniei op_linie
	// STERGERE - se elimina ultimul element de pe linia op_linie

	// decizie cu privire la tipul operatie
	if (op_tip == INSERARE)
	{
		// decizie cu privire la adaugare unei linii noi
		if (op_linie > m)
		{
			// pMat se extinde cu o linie (realocare)

			// realocare vector de dim_linii pe m+1 elemente
			char* ndim = (char*)malloc((m + 1) * sizeof(char));
			for (char i = 0; i < m; i++)
				ndim[i] = dim_linii[i]; // mutare dim_linii in noul vector de dimensiuni linii
			ndim[m] = 1; // dimensiuniunea noii linii care se adauga la matricea pMat

			free(dim_linii); // dezalocare vector (anterior) de dim de linii care s-a mutat in ndim

			dim_linii = ndim; // actualizare dim_linii catre nou vector de dim de linii

			// alocare noua matrice pe dim m + 1 (nr de linii); linia adaugata va avea dimensiune 1 elem
			int** nMat;
			nMat = (int**)malloc(((m + 1) * sizeof(int*)));
			for (char i = 0; i < (m + 1); i++)
				nMat[i] = (int*)malloc(dim_linii[i] * sizeof(int));

			// copierea elementelor din pMat in noua matrice
			for (char i = 0; i < m; i++)
				for (char j = 0; j < dim_linii[i]; j++)
					nMat[i][j] = pMat[i][j]; // copiere element din "vechea" matrice in noua matrice pe m linii

			// adaug noul elem val_elem pe linia m + 1 in noua matrice
			nMat[m][0] = val_elem;

			// dezalocare pMat
			for (char i = 0; i < m; i++)
				free(pMat[i]);
			free(pMat);

			// actualizez pMat, actualizez pe m
			pMat = nMat;
			m = m + 1; // noul nr de linii
		}
		else
		{
			// pastram pMat si actionam la nivelul liniei op_linie (fara realocare la nivel de linii)

			// alocare noua linie op_linie pe dim_linii[op_linie - 1] + 1 elemente
			int* nlin = (int*)malloc((dim_linii[op_linie - 1] + 1) * sizeof(int));

			// copierea elementelor din pMat[op_linie - 1] in noua linie
			for (char i = 0; i < dim_linii[op_linie - 1]; i++)
				nlin[i] = pMat[op_linie - 1][i];

			// inserare val_elem pe ultima pozitie in noua linie
			nlin[dim_linii[op_linie - 1]] = val_elem;

			// dezalocare linie pMat[op_linie - 1]
			free(pMat[op_linie - 1]);

			// actualizare pMat[op_linie - 1] catre noua linie cu noile valori
			pMat[op_linie - 1] = nlin;
			// actualizare dimensiune linie cu 1 elem mai mult decat linia anterioara
			dim_linii[op_linie - 1] = dim_linii[op_linie - 1] + 1;
		}
	}
	else
	{
		if (op_tip == STERGERE)
		{
			// STERGERE

			// decizie cu privire la existenta liniei in matrice
			if (op_linie <= m)
			{
				// decizie cu privire la ne de elemente
				if (dim_linii[op_linie] > 1)
				{
					// exista cel putin 2 elemente pe linia op_linie; 
					// nu se produc modificari la nivel de structura pMat (fara realocare)

					// alocare noua linie (cu 1 elem mai putin decat cea curenta)

					// copiere elemente de pe pMat[op_lini] pe noua linie pt primele dim_linii[op_linie] - 1 elemente

					// dezalocare pMat[op_linie]

					// actualizare pMat[op_linie] pe noua linie

					// actualizare dim_linii[op_linie] (scade cu 1 elem)
				}
				else
				{
					// scade nr de linii pt pMat (realocare)

					// realocare dim_linii pe o noua dim cu 1 elem mai putin (op_linie)

					// alocare noua matrice cu nr de linii m - 1

					// copiere pMat in noua matrice mai putin linia op_linie

					// dezalocare pMat

					// actualizare pMat

					// actualizare m
				}
			}
		}
	}

	return pMat;
}

void afisare_matrice(int** pMat, char m, char * dim_linii)
{
			for (char i = 0; i < m; i++)
			{
				for (char j = 0; j < dim_linii[i]; j++)
					printf(" %d ", pMat[i][j]);
				printf("\n");
			}
}

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
	21 22
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

	/* pMat
	1  2
	11 12
	21 22
	*/
	printf("\n");
	afisare_matrice(pMat, m, dim_linii);
	pMat = op_elem_matrice(pMat, m, dim_linii, 1, 55, INSERARE);
	printf("\n");
	afisare_matrice(pMat, m, dim_linii);
	pMat = op_elem_matrice(pMat, m, dim_linii, 5, 77, INSERARE);
	printf("\n");
	afisare_matrice(pMat, m, dim_linii);

	// dezalocare
	for (char i = 0; i < m; i++)
		free(pMat[i]);
	free(pMat);

	int Mat[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

	// TEMA - gestionare dinamca a matricei pMat prin adaugarea de valori pe linii si adaugarea de linii la matrice
	// intr-o functie

	return 0;
}