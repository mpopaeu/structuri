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
void interschimbare(int* vHeap, int offs_nod_descendent, int offs_nod_current) {
	int aux = vHeap[offs_nod_descendent];
	vHeap[offs_nod_descendent] = vHeap[offs_nod_current];
	vHeap[offs_nod_current] = aux;
}

void ordonare(int* vHeap, int nKeys, int offs_nod_current)
{
		int left = 2 * offs_nod_current + 1;
		int right = 2 * offs_nod_current + 2;
		if (left < nKeys && right < nKeys)
		{
			if (vHeap[offs_nod_current] < vHeap[left] || vHeap[offs_nod_current] < vHeap[right])
			{
				if (vHeap[left] < vHeap[right])
				{
					interschimbare(vHeap, right, offs_nod_current);
					ordonare(vHeap, nKeys, right);
				}
				else
				{
					interschimbare(vHeap, left, offs_nod_current);
					ordonare(vHeap, nKeys, left);
				}
			}
		}
		if (left < nKeys) // penultimul nivel
		{
			if (vHeap[offs_nod_current] < vHeap[left])
			{
				interschimbare(vHeap, left, offs_nod_current);
			}
		}
}

// extragere cheie din nod radacina
int extragere_cheie_Heap(int* vHeap, int& nKeys)
{
	if (nKeys > 0)
	{
		int aux = vHeap[0];
		vHeap[0] = vHeap[nKeys - 1]; // primul element (radacina) rescrisa cu ultimul element
		nKeys -= 1; // noul numar de noduri din arbore de structura Heap
		ordonare(vHeap, nKeys, 0);

		return aux;
	}

	return -1; // daca cheile nu accepta valori intregi negative
}

// creare vector de chei extrase din structura max-heap pana la un prag specificat
// [in,out] vHeap - vectorul suport pentru structura max-heap
// [in,out] nKeys - nr de noduri din structura max-heap
// [in] prag_minim - pragul pana la care se face extragerea din max-heap
// [out] nVExtrase - nr de chei extrase
// return - vector cu chei extrase

int* creare_vector(int* vHeap, int& nKeys, int prag_minim, int &nVExtrase)
{

}

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

	printf("\n Structura Heap dupa inserare cheie 26 cu capacitate de stocare %d: ", capacitate_stocare);
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", vHeap[i]);
	printf("\n");

	cheie = extragere_cheie_Heap(vHeap, nKeys);
	printf("\n Structura Heap dupa extragere cheie %d: ", cheie);
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", vHeap[i]);
	printf("\n");

	cheie = extragere_cheie_Heap(vHeap, nKeys);
	printf("\n Structura Heap dupa extragere cheie %d: ", cheie);
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", vHeap[i]);
	printf("\n");

	// dezalocare vector suport structura Heap
	free(vHeap);


	fclose(f);
	return 0;
}
