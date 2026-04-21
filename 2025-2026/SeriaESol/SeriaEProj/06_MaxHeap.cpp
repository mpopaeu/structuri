#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 20

// inserare cheie
void inserare_cheie_heap(int* strHeap, int* strSize, int key)
{
	*strSize += 1;
	int offs_key = *strSize - 1;
	strHeap[offs_key] = key; // inserare intiala cheie in structura Heap

	int offs_parinte = (offs_key - 1) / 2; // offset element/nod parinte pentru key

	while (offs_key > 0 && // offs_key 0 inseamna ca noua cheie key este radacina de arbore max-heap
		strHeap[offs_key] > strHeap[offs_parinte]) // nu se respecta relatia de ordine pentru un max-heap
	{
		// interschimbare key-parinte
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[offs_parinte];
		strHeap[offs_parinte] = aux;

		// actualizare offset key in vector
		offs_key = offs_parinte;

		// calcul offset parinte nou pentru key
		offs_parinte = (offs_key - 1) / 2;
	}
}

int main()
{
	int* strHeap = NULL; // vector suport structura Heap

	strHeap = (int*)malloc(DIM * sizeof(int));
	int capacitate_stocare = DIM;

	int nKeys = 0, cheie; // numarul de chei disponibile in structura Heap la un moment dat

	FILE* f;
	f = fopen("HeapKeys.txt", "r");

	fscanf(f, "%d", &cheie);
	while (!feof(f))
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

		inserare_cheie_heap(strHeap, &nKeys, cheie);

		fscanf(f, "%d", &cheie);
	}

	fclose(f);

	printf("\n Structura Heap initiala: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);

	// inserare cheie 32 in structura max-heap
	inserare_cheie_heap(strHeap, &nKeys, 32);

	printf("\n Structura Heap dupa inserarea cheii 32: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);

}