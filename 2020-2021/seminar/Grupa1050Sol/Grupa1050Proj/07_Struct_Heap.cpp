#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 20

// procedura filtrare bottom-up
void inserare_cheie_heap(int* strHeap, int &strSize, int key)
{
	strSize += 1;
	int offs_key = strSize - 1;
	strHeap[offs_key] = key; // inserare intiala cheie in structura Heap
	
	int offs_parinte = (offs_key - 1) / 2; // offset element/nod parinte pentru key

	while (strHeap[offs_key] > strHeap[offs_parinte]) // nu se respecta relatia de ordine pentru un max-heap
	{
		// interscimbare key-parinte
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[offs_parinte];
		strHeap[offs_parinte] = aux;

		// actualizare offset key in vector
		offs_key = offs_parinte;

		// calcul offset parinte nou pentru key
		offs_parinte = (offs_key - 1) / 2;
	}
}

// procedura filtrare top-down
// TEMA
// apelata pentru operatia de stergere cheie in structura Heap
//////

int main()
{
	int* strHeap = NULL; // vector suport structura Heap

	strHeap = (int*)malloc(DIM * sizeof(int));
	int capacitate_stocare = DIM;

	int nKeys = 0, cheie; // numarul de chei disponibile in structura Heap la un moment dat

	FILE* f;
	f = fopen("HeapKeys.txt", "r");

	fscanf(f, "%d", &cheie);
	while (!feof(f)) // testare sfarsit de fisier
	{
		if (nKeys == capacitate_stocare)
		{
			// realocare vector cu + DIM elemente
			// se copiaza elementele din vechea structura in noua structura pe exact aceleasi pozitii
			capacitate_stocare += DIM;
			int* new_strHeap = (int*)malloc(capacitate_stocare * sizeof(DIM));
			for (int i = 0; i < nKeys; i++)
				new_strHeap[i] = strHeap[i];

			// dezalocare vector la capacitate maxima
			free(strHeap);
			// comutare pointer pe noua locatie extinsa
			strHeap = new_strHeap;
		}

		inserare_cheie_heap(strHeap, nKeys, cheie);

		fscanf(f, "%d", &cheie);
	}

	// afisare structura Heap (vector) - situatie initiala
	printf("\n Structura Heap initiala: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);

	// inserare cheie 26 in structura Heap
	inserare_cheie_heap(strHeap, nKeys, 26);

	// afisare structura Heap (vector) - dupa inserare cheie 26
	printf("\n\n Structura Heap dupa inserare cheie 26: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);
	printf("\n");

	fclose(f);
	return 0;
}