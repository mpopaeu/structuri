#include <malloc.h>
#include <stdio.h>

#define INSERARE 1
#define STERGERE 2

// implementare Dulgheru Mihai
int** op_elem_matrice(int** pMat, char &m, char * &dim_linii, char op_linie, int val_elem, char op_tip)
{
	// pMat - adresa matrice alocate in heap
	// m - nr de linii al matricei
	// dim_linii - vector cu dimensiuni reale/concrete la runtime ale liniilor
	// op_linie - linia pt care se aplica operatia op_tip; 
	//				INSERARE: op_linie < m + 1
	//				STERGERE: op_linie < m
	// val_elem - valoare element pentru care se aplica operatia op_tip INSERARE / STERGERE
	// op_tip - tip operatie: INSERARE / STERGERE

	if (--op_linie < 0)
	{
		printf("Nu s-a efectuat nicio modificare. Linie invalida.\n");
		return pMat;
	}
	if (op_tip == INSERARE)
	{
		if (op_linie < m + 1)
		{
			if (op_linie == m)
			{
				m++;
				char* temp = (char*)malloc(m * sizeof(char));
				for (char i = 0; i < m - 1; i++)
				{
					temp[i] = dim_linii[i];
				}
				temp[m - 1] = 1;
				free(dim_linii);
				dim_linii = temp;
				int** matriceNoua = (int**)malloc(m * sizeof(int*));
				for (char i = 0; i < m; i++)
				{
					matriceNoua[i] = (int*)malloc(dim_linii[i] * sizeof(int));
				}
				for (char i = 0; i < m - 1; i++)
				{
					for (char j = 0; j < dim_linii[i]; j++)
					{
						matriceNoua[i][j] = pMat[i][j];
					}
				}
				matriceNoua[m - 1][dim_linii[m - 1] - 1] = val_elem;
				for (char i = 0; i < m - 1; i++) {
					free(pMat[i]);
					//pMat[i] = NULL;
				}
				free(pMat);
				pMat = matriceNoua;
			}
			else
			{
				dim_linii[op_linie]++;
				int** matriceNoua = (int**)malloc(m * sizeof(int*));
				for (char i = 0; i < m; i++)
				{
					matriceNoua[i] = (int*)malloc(dim_linii[i] * sizeof(int));
				}
				for (char i = 0; i < m; i++)
				{
					for (char j = 0; j < dim_linii[i]; j++)
					{
						if (i == op_linie && j == dim_linii[i] - 1)
						{
							matriceNoua[i][j] = val_elem;
						}
						else
						{
							matriceNoua[i][j] = pMat[i][j];
						}
					}
				}
				for (char i = 0; i < m; i++) {
					free(pMat[i]);
					// pMat[i] = NULL;
				}
				free(pMat);
				pMat = matriceNoua;
			}
		}
		else
		{
			printf("Nu s-a efectuat nicio modificare. Linie invalida.\n");
		}
	}
	if (op_tip == STERGERE)
	{
		if (op_linie < m)
		{
			if (pMat[op_linie][dim_linii[op_linie] - 1] == val_elem)
			{
				if (dim_linii[op_linie] - 1 == 0)
				{
					m--;
					char* temp = (char*)malloc(m * sizeof(char));
					char i = 0;
					while (i < op_linie)
					{
						temp[i] = dim_linii[i];
						i++;
					}
					i++;
					while (i < m + 1)
					{
						temp[i - 1] = dim_linii[i];
						i++;
					}
					free(dim_linii);
					dim_linii = temp;
					int** matriceNoua = (int**)malloc(m * sizeof(int*));
					for (i = 0; i < m; i++)
					{
						matriceNoua[i] = (int*)malloc(dim_linii[i] * sizeof(int));
					}
					for (i = 0; i < op_linie; i++)
					{
						for (char j = 0; j < dim_linii[i]; j++)
						{
							matriceNoua[i][j] = pMat[i][j];
						}
					}
					for (i = op_linie + 1; i < m + 1; i++)
					{
						for (char j = 0; j < dim_linii[i - 1]; j++)
						{
							matriceNoua[i - 1][j] = pMat[i][j];
						}
					}
					for (i = 0; i < m; i++) {
						free(pMat[i]);
						// pMat[i] = NULL;
					}
					free(pMat);
					pMat = matriceNoua;
				}
				else
				{
					dim_linii[op_linie]--;
					int** matriceNoua = (int**)malloc(m * sizeof(int*));
					for (char i = 0; i < m; i++)
					{
						matriceNoua[i] = (int*)malloc((dim_linii[i]) * sizeof(int));
					}
					for (char i = 0; i < m; i++)
					{
						for (char j = 0; j < dim_linii[i]; j++)
						{
							matriceNoua[i][j] = pMat[i][j];
						}
					}
					for (char i = 0; i < m; i++) {
						free(pMat[i]);
						// pMat[i] = NULL;
					}
					free(pMat);
					pMat = matriceNoua;
				}
			}
			else
			{
				printf("Nu s-a efectuat nicio modificare. Elementul pe care doriti sa-l stergeti nu exista.\n");
			}
		}
		else
		{
			printf("Nu s-a efectuat nicio modificare. Linie invalida.\n");
		}
	}
	return pMat;
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