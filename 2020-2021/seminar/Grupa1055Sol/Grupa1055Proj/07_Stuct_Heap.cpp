#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 10

void inserare_cheie_Heap(int* vHeap, int &nKeys, int cheie)
{
	nKeys += 1; // crestere nr chei efective in vector cu 1 element
	int offs_cheie = nKeys - 1;
	vHeap[offs_cheie] = cheie; // stocare cheie de inserat pe ultima pozitie in vector (struct Heap)

	int offs_parinte = (offs_cheie - 1) / 2; // offset parinte intial pt nodul nou inserat in struct Heap

	while (vHeap[offs_cheie] > vHeap[offs_parinte])
	{
		// nu este respectata relatia de ordine dintre cheie si parintele sau

		// interschimb cheie cu parintele sau
		int aux = vHeap[offs_cheie];
		vHeap[offs_cheie] = vHeap[offs_parinte];
		vHeap[offs_parinte] = aux;

		// actualizare offset cheie
		offs_cheie = offs_parinte;

		// recalculare offset parinte nou pentru cheie
		offs_parinte = (offs_cheie - 1) / 2;
	}

}

int extragere_cheie_Heap(int* vHeap, int &nKeys)
{
	// salvare cheie din offset 0

	// interschimb cheie offset 0 cu cheie offset nKeys-1

	// actualizare nKeys -= 1

	// calcul descendenti stanga, dreapta pentru cheie curenta offset 0
	// determinare max(cheie_stanga, cheie_dreapta)

	// iterativ
	while ()
	{
		// interschimb cheie curenta cu cheie_max descendenti

		// actualizare offset cheie curenta

		// calcul descendenti stanga, dreapta pentru cheie curenta
		// determinare max(cheie_stanga, cheie_dreapta)
	}

}

int main()
{
	int* vHeap = NULL; // vector suport structura Heap
	int capacitate_stocare = DIM, nKeys = 0;
	int cheie;

	vHeap = (int*)malloc(capacitate_stocare * sizeof(int));

	FILE * f = fopen("HeapKeys.txt", "r");

	fscanf(f, "%d", &cheie);
	while (!feof(f))
	{
		if (nKeys == capacitate_stocare)
		{
			// realocare vector cu +DIM elemente
			// mutare elemente in nou vector
			capacitate_stocare += DIM;
			int * new_vHeap = (int*)malloc(capacitate_stocare *sizeof(int));

			// mutare elemente/chei din vectorul initial in nou vector
			for (int i = 0; i < nKeys; i++)
				new_vHeap[i] = vHeap[i];

			// dezalocare vector initial
			free(vHeap);

			// comutarea pe noul vector
			vHeap = new_vHeap;
		}

		inserare_cheie_Heap(vHeap, nKeys, cheie);

		fscanf(f, "%d", &cheie);
	}

	printf("\n Structura Heap initiala: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", vHeap[i]);
	printf("\n");

	if (nKeys == capacitate_stocare)
	{
		// realocare vector cu +DIM elemente
		// mutare elemente in nou vector
		capacitate_stocare += DIM;
		int * new_vHeap = (int*)malloc(capacitate_stocare * sizeof(int));

		// mutare elemente/chei din vectorul initial in nou vector
		for (int i = 0; i < nKeys; i++)
			new_vHeap[i] = vHeap[i];

		// dezalocare vector initial
		free(vHeap);

		// comutarea pe noul vector
		vHeap = new_vHeap;
	}
	inserare_cheie_Heap(vHeap, nKeys, 26);

	printf("\n Structura Heap dupa inserare cheie 26: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", vHeap[i]);
	printf("\n");

	// dezalocare vector suport structura Heap
	free(vHeap);

	fclose(f);

	return 0;
}
