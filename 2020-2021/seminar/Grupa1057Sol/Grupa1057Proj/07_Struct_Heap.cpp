#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 9

int* inserare_cheie_heap(int* strHeap, int &nrNoduri, int &capacitate, int cheie)
{
	if (nrNoduri == capacitate)
	{
		// nu exista nici un element disponibil la inserare in struct Heap
		int* new_strHeap;
		capacitate += DIM; // noua capacitate de stocare e vectorului suport pt struct Heap

		new_strHeap = (int*)malloc(capacitate * sizeof(int)); // alocare nou vector suport (mai mare cu DIM elem fata de cel primit in strHeap)

		// copiere elemente struct Heap in noul vector suport
		for (int i = 0; i < nrNoduri; i++)
			new_strHeap[i] = strHeap[i];

		// dezalocare vector primit in strHeap
		free(strHeap);

		// comutare parametru strHeap pe noul vector suport
		strHeap = new_strHeap;
	}

	nrNoduri += 1;
	int offset_cheie = nrNoduri - 1;
	strHeap[offset_cheie] = cheie;
	int offset_parinte = (offset_cheie - 1) / 2;

	while (strHeap[offset_cheie] > strHeap[offset_parinte])
	{
		// relatia de ordine nu este indeplinita

		// 1. interschimbare nod inserat cu parintele sau
		int aux = strHeap[offset_cheie];
		strHeap[offset_cheie] = strHeap[offset_parinte];
		strHeap[offset_parinte] = aux;

		// 2. recalculare offset-i pentru cheie si parinte cheie
		offset_cheie = offset_parinte;
		offset_parinte = (offset_cheie - 1) / 2;
	}

	return strHeap;
}

// TEMA
// operatie de stergere/extragere nod din structura Heap

int main()
{
	FILE* f;
	f = fopen("HeapKeys.txt", "r");

	int* sHeap, nrNoduri, capacitate, cheie;
	nrNoduri = 0; // initial, 0 noduri in structura Heap
	capacitate = DIM;

	sHeap = (int*)malloc(capacitate * sizeof(int)); // alocare vector la capacitate de stocare

	fscanf(f, "%d", &cheie);
	while (!feof(f))
	{
		// prelucrare cheie citita anterior din fisier
		sHeap = inserare_cheie_heap(sHeap, nrNoduri, capacitate, cheie);

		// citire cheie urmatoare din fisier
		fscanf(f, "%d", &cheie);
	}

	printf("Structura Heap initiala: ");
	for (int i = 0; i < nrNoduri; i++)
		printf(" %d ", sHeap[i]);
	printf("\n\n");

	sHeap = inserare_cheie_heap(sHeap, nrNoduri, capacitate, 28);
	printf("Structura Heap dupa inserare cheie 28: ");
	for (int i = 0; i < nrNoduri; i++)
		printf(" %d ", sHeap[i]);
	printf("\n\n");

	// dezalocare vector suport structura Heap
	free(sHeap);

	fclose(f);

	return 0;
}