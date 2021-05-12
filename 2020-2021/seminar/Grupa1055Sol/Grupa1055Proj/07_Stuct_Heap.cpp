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

// stergere/extragere cheie din structura max-Heap
// nodul radacina este sters din structura max-Heap
int extragere_cheie_Heap(int* vHeap, int &nKeys)
{
	// salvare cheie din offset 0
	int key = vHeap[0];

	// interschimb cheie offset 0 cu cheie offset nKeys-1
	int aux = vHeap[0];
	vHeap[0] = vHeap[nKeys - 1];
	vHeap[nKeys - 1] = aux;

	// actualizare nKeys -= 1
	nKeys -= 1; // reducerea numarului de chei din structura Heap

	// calcul descendenti stanga, dreapta pentru cheie curenta offset 0
	// determinare max(cheie_stanga, cheie_dreapta)
	int i = 0; // offset nod curent
	int max = -1; // offset pentru cheia de valoare maxima dintre descendenti
	int offset_stanga = 2 * i + 1;
	int offset_dreapta = 2 * i + 2;
	if (offset_stanga < nKeys && offset_dreapta < nKeys)
	{
		// nodul curent i are doi descendenti
		if (vHeap[offset_stanga] < vHeap[offset_dreapta])
			max = offset_dreapta;
		else
			max = offset_stanga;
	}
	else
	{
		if (offset_stanga < nKeys)
		{
			// nodul curent i are 1 descendent
			max = offset_stanga;
		}
	}

	// iterativ
	while (nKeys > 1 && vHeap[i] < vHeap[max]) 
	{
		// regula de ordonare a cheilor nu este respectata
		// interschimb cheie curenta cu cheie_max descendenti
		aux = vHeap[i];
		vHeap[i] = vHeap[max];
		vHeap[max] = aux;

		// actualizare offset cheie curenta
		i = max;
		// recalculare offsets descendenti pentru noul i
		offset_stanga = 2 * i + 1;
		offset_dreapta = 2 * i + 2;

		// calcul descendenti stanga, dreapta pentru cheie curenta
		// determinare max(cheie_stanga, cheie_dreapta)
		if (offset_stanga < nKeys && offset_dreapta < nKeys)
		{
			// nodul curent i are doi descendenti
			if (vHeap[offset_stanga] < vHeap[offset_dreapta])
				max = offset_dreapta;
			else
				max = offset_stanga;
		}
		else
		{
			if (offset_stanga < nKeys)
			{
				// nodul curent i are 1 descendent
				max = offset_stanga;
			}
		}
	}

	return key;
}

// creare vector cu valori de cheie sortate descrescator
// valorile de cheie se extrag din structura max-heap
int* vector_sortat_din_Heap(int* vHeap, int &nKeys, int &dim)
{

}

// TEMA
// functie conversie structura max-heap (vHeap) intr-o structura de tip min-heap
// conversia are loc prin extragere cheie din max-heap si inserarea ei in structura noua min-heap

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

	printf(" Stergere chei din structura Heap: ");
	while (nKeys > 0)
	{
		printf(" %d ", extragere_cheie_Heap(vHeap, nKeys));
	}
	printf("\n\n");

	// dezalocare vector suport structura Heap
	free(vHeap);

	fclose(f);

	return 0;
}
