#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 7

void inserare_cheie_Heap(int* vHeap, int &nKeys, int cheie)
{
	nKeys += 1; // noul  nr de chei stocate in vector
	int offs_cheie = nKeys - 1; // offsetul initial pe care se va stoca cheie

	vHeap[offs_cheie] = cheie; // stocare cheie la sfarsitul vectorului 
	int offs_parinte = (offs_cheie - 1) / 2; // offset parinte no. 1 pentru cheie
	while (vHeap[offs_cheie] > vHeap[offs_parinte])
	{
		// relatia de ordine pentru max-heap nu este indeplinita
		// interschimb nod cu parinte
		int aux = vHeap[offs_cheie];
		vHeap[offs_cheie] = vHeap[offs_parinte];
		vHeap[offs_parinte] = aux;

		// actualizare offset nod cheie
		offs_cheie = offs_parinte;

		// recalculez offset parinte pentru determinarea noului parinte a nodului cheie
		offs_parinte = (offs_cheie - 1) / 2;
	}
}

// TEMA
// implementare operatie de stergere in structura Heap

int main()
{
	FILE* f = fopen("HeapKeys.txt", "r");
	int capacitate_stocare, nKeys = 0;

	capacitate_stocare = DIM;
	int* vHeap = (int*)malloc(capacitate_stocare * sizeof(int)); // vector suport pentru structura Heap

	int cheie;
	fscanf(f, "%d", &cheie);
	while (!feof(f))
	{
		// prelucrare cheie
		// 1. asigurare spatiu in vector de chei (operatie de realocare vector)
		if (nKeys == capacitate_stocare)
		{
			// realocare pe dimensiune mai mare a vectorului suport Heap
			capacitate_stocare += DIM; // noua capacitate de stocare
			int* new_vHeap = (int*)malloc(capacitate_stocare * sizeof(int));
			for (int i = 0; i < nKeys; i++)
				new_vHeap[i] = vHeap[i];// copiere elemente/chei din vectorul initial in noul vector extins cu DIM elemente

			// dezalocare vector initial
			free(vHeap);

			// comutare va pointer pe noul vector
			vHeap = new_vHeap;
		}

		// 2. inserare propriu-zisa, inclusiv procedura de filtrare bottom-up pe Heap
		inserare_cheie_Heap(vHeap, nKeys, cheie);

		fscanf(f, "%d", &cheie);
	}

	printf("\n Structura Heap initiala cu dimensiune %d: ", capacitate_stocare);
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", vHeap[i]);
	printf("\n");

	if (nKeys == capacitate_stocare)
	{
		// realocare pe dimensiune mai mare a vectorului suport Heap
		capacitate_stocare += DIM; // noua capacitate de stocare
		int* new_vHeap = (int*)malloc(capacitate_stocare * sizeof(int));
		for (int i = 0; i < nKeys; i++)
			new_vHeap[i] = vHeap[i];// copiere elemente/chei din vectorul initial in noul vector extins cu DIM elemente

		// dezalocare vector initial
		free(vHeap);

		// comutare va pointer pe noul vector
		vHeap = new_vHeap;
	}
	inserare_cheie_Heap(vHeap, nKeys, 26);

	printf("\n Structura Heap dupa inserare cheie 26 cu dimensiune %d: ", capacitate_stocare);
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", vHeap[i]);
	printf("\n");

	// dezalocare vector suport structura Heap
	free(vHeap);


	fclose(f);
	return 0;
}
