#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 7

int* inserare_cheie_Heap(int* strHeap, int& nMax, int &capacitate, int cheie)
{
	if (nMax == capacitate)
	{
		// nu exista zona disponibila in vector --> relocare vector pe + DIM elemente
		capacitate += DIM; // DIM - chunk de elemente suplimentare 
		// alocare noua structura vector 
		int* new_strHeap = (int*)malloc(capacitate * sizeof(int));
		// copiere elemente din strHeap in noua structura
		for (int i = 0; i < nMax; i++)
			new_strHeap[i] = strHeap[i];

		// dezalocare structura strHeap
		free(strHeap);

		// actualizare structura Heap pe noul vector
		strHeap = new_strHeap;
	}

	nMax += 1;
	strHeap[nMax - 1] = cheie; // noua cheie este inserata la sfarsitul vectorului (prima pozitie disponibila din arborele Heap)

	int offset_cheie, offset_parinte;
	offset_cheie = nMax - 1;
	offset_parinte = (offset_cheie - 1) / 2;

	while (strHeap[offset_cheie] > strHeap[offset_parinte])
	{
		// relatia de ordine nu este respectata pentru strHeap ca max-heap

		// interschimb elemente
		int aux = strHeap[offset_cheie];
		strHeap[offset_cheie] = strHeap[offset_parinte];
		strHeap[offset_parinte] = aux;

		// recalculare offset-i pentru cheie si noul parinte cheie
		offset_cheie = offset_parinte;
		offset_parinte = (offset_cheie - 1) / 2;
	}

	return strHeap;
}

// TEMA 
// operatia de extragere/stergere din structura max-heap
int stergere_cheie_heap(int* strHeap, int& strSize)
{
	int key;
	int offs_key = 0; // offset nod curent pentru care se aplica op de filtrare top-down
	int max = -1; // offset descendent cu cheia maxima (max(left_key, right_key); pentru offs_key
	//preiau ultimul element din structura
	int lastElement = strHeap[strSize - 1];
	key = strHeap[0];
	strHeap[0] = lastElement; //ultimul element devine primul

	strSize -= 1; //numarul de chei scade cu 1

	int Left = 2 * offs_key + 1;
	int Right = 2 * offs_key + 2;

	if (Left < strSize && Right < strSize) // exista ambii descendenti
	{
		if (strHeap[Left] > strHeap[Right])
		{
			max = Left;
		}
		else
		{
			max = Right;
		}
	}
	else
	{
		if (Left < strSize)
		{
			max = Left;
		}
	}

	while (strSize > 1 && max != -1 && strHeap[max] > strHeap[offs_key]) //nu se respecta relatia de ordine 
	{
		// strSize > 0 - exista cel putin 2 elemente in structura
		// max != -1 - exista cel putin 1 descendent pentru nodul curent strHeap[offs_key]
		// strHeap[max] > strHeap[offs_key] - nu se respecta relatia de ordine pentru un max-heap
		//interschimbare key-parinte
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[max];
		strHeap[max] = aux;

		// actualizare offset key in vector
		offs_key = max;

		//calcul offset pentru noul key
		Left = 2 * offs_key + 1;
		Right = 2 * offs_key + 2;
		if (Left < strSize && Right < strSize)
		{
			if (strHeap[Left] > strHeap[Right])
			{
				max = Left;
			}
			else
			{
				max = Right;
			}
		}
		else
		{
			if (Left < strSize)
			{
				max = Left;
			}
			else
			{
				max = -1;
			}
		}
	}

	return key;
}

// creare vector cu jumatate din nr efective de chei stocate de structura max-heap
// functie
// [in] strHeap - vector suport pentru structura max-heap
// [in,out] strSize - nr efectiv de chei din structura max-heap

int* creare_vector_chei(int* strHeap, int& strSize)
{

}

int main()
{
	FILE* f;
	f = fopen("HeapKeys.txt", "r");

	int nMax, capacitate, *sHeap, cheie;
	capacitate = DIM; // capacitate intiala de stocare
	nMax = 0; // nr efectiv de noduri din arborele Heap (val initiala)

	// alocare vector suport structura Heap
	sHeap = (int*)malloc(sizeof(int) * capacitate);

	fscanf(f, "%d", &cheie); // citire initiala din fisier (cheie)

	while (!feof(f)) {
		// prelucrare continut citit din fisier (prelucrare cheie)
		sHeap = inserare_cheie_Heap(sHeap, nMax, capacitate, cheie);

		// citire element urmator din fisier
		fscanf(f, "%d", &cheie);
	}

	printf("Structura Heap initiala: ");
	for (int i = 0; i < nMax; i++)
		printf(" %d ", sHeap[i]);

	sHeap = inserare_cheie_Heap(sHeap, nMax, capacitate, 28);

	printf("\nStructura Heap dupa inserare cheie 28: ");
	for (int i = 0; i < nMax; i++)
		printf(" %d ", sHeap[i]);

	printf("\n\n");

	if (nMax > 0)
	{
		cheie = stergere_cheie_heap(sHeap, nMax);
		printf("Cheie extrasa din max-heap: %d\n", cheie);

		printf("\nStructura Heap dupa extragere/stergere: ");
		for (int i = 0; i < nMax; i++)
			printf(" %d ", sHeap[i]);

		printf("\n\n");
	}

	// dezalocare vector
	free(sHeap);

	fclose(f);

	return 0;
}