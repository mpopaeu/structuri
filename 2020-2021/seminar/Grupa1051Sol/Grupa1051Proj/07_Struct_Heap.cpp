#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 8

int* inserare_cheie_Heap(int* strHeap, int &nrNoduri, int &capacitate, int cheie)
{
	if (nrNoduri == capacitate)
	{
		// nu exista loc in vector pentru cheie
		capacitate += DIM; // capacitate de stocare marita 
		int* new_sHeap = (int*)malloc(capacitate * sizeof(int)); // alocare vector nou pe capacitate marita

		// copiere elemente in noul vector
		for (int i = 0; i < nrNoduri; i++)
			new_sHeap[i] = strHeap[i];

		// dezalocare strHeap (fara capacitate de stocare)
		free(strHeap);

		// mutare strHeap pe noul vector
		strHeap = new_sHeap;
	}

	nrNoduri += 1;
	int offset_cheie, offset_parinte;
	offset_cheie = nrNoduri - 1;

	strHeap[offset_cheie] = cheie; // se insereaza noul nod pe prima pozitie disponibila in struct Heap
	offset_parinte = (offset_cheie - 1) / 2;

	while (strHeap[offset_cheie] > strHeap[offset_parinte])
	{
		// nu se respecta relatia de ordine specifica unui max-heap

		// 1. intreschimb elemente
		int aux = strHeap[offset_cheie];
		strHeap[offset_cheie] = strHeap[offset_parinte];
		strHeap[offset_parinte] = aux;

		// 2. actualizare offset cheie, offset parinte
		offset_cheie = offset_parinte; // noul offset pt cheia de inserat
		offset_parinte = (offset_cheie - 1) / 2; // offset pt noul parinte al cheii de inserat
	}

	return strHeap;
}

// TEMA
// stergere/extragere nod din structura Heap

int main()
{
	FILE* f;
	f = fopen("HeapKeys.txt", "r");

	int* sHeap, nrNoduri, capacitate;
	int cheie;

	capacitate = DIM;
	nrNoduri = 0;

	sHeap = (int*)malloc(capacitate * sizeof(int));

	fscanf(f, "%d", &cheie); // citire prima cheie din fisier

	while (!feof(f))
	{
		// prelucrare continut preluat in cheie
		sHeap = inserare_cheie_Heap(sHeap, nrNoduri, capacitate, cheie);

		fscanf(f, "%d", &cheie); // citire cheie urmatoare din fisier
	}

	printf("Structura Heap initiala: ");
	for (int i = 0; i < nrNoduri; i++)
		printf(" %d ", sHeap[i]);
	printf("\n");

	sHeap = inserare_cheie_Heap(sHeap, nrNoduri, capacitate, 28);
	printf("Structura Heap dupa inserare cheie 28: ");
	for (int i = 0; i < nrNoduri; i++)
		printf(" %d ", sHeap[i]);
	printf("\n");

	// dezalocare vector suport
	free(sHeap);

	fclose(f);
	return 0;
}