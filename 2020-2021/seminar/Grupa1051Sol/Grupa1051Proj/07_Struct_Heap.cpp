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
int extragere_nod_Heap(int* sHeap, int& nrNoduri)
{
	int radacina = sHeap[0];	// salvare cheie din radacina	
	sHeap[0] = sHeap[nrNoduri - 1]; 

	if (--nrNoduri > 1)	// daca vectorul contine cel putin doua elemente
	{
		int offset_cheie = 0; // offset radacina cu noua cheie

		// identificare descendenti
		int offset_stanga = 2 * offset_cheie + 1;
		int offset_dreapta = 2 * offset_cheie + 2;

		// determinare descendent cu valoarea cheii maxima
		int offset_maxim = -1;
		if (offset_stanga < nrNoduri && offset_dreapta < nrNoduri)	// daca exista ambii descendenti
			offset_maxim = (sHeap[offset_stanga] > sHeap[offset_dreapta]) ? offset_stanga : offset_dreapta;	// offset-ul maxim va fi cel al descendentului cu valoarea cheii mai mare
		else
			if (offset_stanga < nrNoduri)	// daca exista doar descendentul stanga
				offset_maxim = offset_stanga;	// offset-ul maxim va fi cel al nodului din stanga

		while (offset_maxim != -1 && sHeap[offset_maxim] > sHeap[offset_cheie])
		{
			// interschimbare elemente
			int aux = sHeap[offset_cheie];
			sHeap[offset_cheie] = sHeap[offset_maxim];
			sHeap[offset_maxim] = aux;

			// actualizare offset cheie, offset stanga, offset dreapta
			offset_cheie = offset_maxim;
			offset_stanga = 2 * offset_cheie + 1;
			offset_dreapta = 2 * offset_cheie + 2;

			if (offset_stanga < nrNoduri && offset_dreapta < nrNoduri)	// daca exista ambii descendenti
				offset_maxim = (sHeap[offset_stanga] > sHeap[offset_dreapta]) ? offset_stanga : offset_dreapta;	// offset-ul maxim va fi cel al descendentului cu valoarea cheii mai mare
			else
				if (offset_stanga < nrNoduri)	// daca exista doar descendentul stanga
					offset_maxim = offset_stanga;	// offset-ul maxim va fi cel al nodului din stanga
				else
					offset_maxim = -1;	// marcare nod ca neavand descendenti
		}
	}

	return radacina;
}

int* creare_vector_sortat(int* sHeap, int& nrNoduri, int& nrSortate)
{
	nrSortate = nrNoduri;
	int* vSortate = (int*)malloc(nrSortate * sizeof(int));
	for (int i = 0; i < nrSortate; i++)
		vSortate[i] = extragere_nod_Heap(sHeap, nrNoduri);

	return vSortate;
}


int* inserare_cheie_min_Heap(int* strHeap, int& nrNoduri, int& capacitate, int cheie)
{
	if (nrNoduri == capacitate)
	{
		// nu exista loc in vector pentru cheie

		capacitate += DIM;	// capacitate de stocare marita
		int* new_sHeap = (int*)malloc(capacitate * sizeof(int));	// alocare vector nou pe capacitate marita

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

	strHeap[offset_cheie] = cheie;	// se insereaza noul nod pe prima pozitie disponibila in struct Heap
	offset_parinte = (offset_cheie - 1) / 2;

	while (strHeap[offset_cheie] < strHeap[offset_parinte]) // validare relatie de ordine pe min-heap
	{
		// nu se respecta relatia de ordine specifica unui min-heap

		// 1. interschimb elemente
		int aux = strHeap[offset_cheie];
		strHeap[offset_cheie] = strHeap[offset_parinte];
		strHeap[offset_parinte] = aux;

		// 2. actualizare offset cheie, offset parinte
		offset_cheie = offset_parinte;	// noul offset pentru cheia de inserat
		offset_parinte = (offset_cheie - 1) / 2;	// offset pentru noul parinte al cheii de inserat
	}

	return strHeap;
}

int* creare_min_Heap(int* minHeap, int& nrNoduri, int*& vSortate, int& nrSortate, int& capacitate) {
	nrNoduri = 0;
	// for (int i = nrSortate - 1; i >= 0; i--)
	for (int i = 0; i < nrSortate; i++)
	{
		minHeap = inserare_cheie_min_Heap(minHeap, nrNoduri, capacitate, vSortate[i]);
	}
	nrSortate = 0;
	if (vSortate)
	{
		free(vSortate);
		vSortate = NULL;
	}

	return minHeap;
}

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

	// extragere cheie din structura heap
	cheie = extragere_nod_Heap(sHeap, nrNoduri);
	printf("Structura Heap dupa extragere cheie radacina: ");
	for (int i = 0; i < nrNoduri; i++)
		printf(" %d ", sHeap[i]);
	printf("\n");

	// creare vector de elemente sortate descrescator din structura max-heap
	int* vSortate = NULL, nrSortate;
	vSortate = creare_vector_sortat(sHeap, nrNoduri, nrSortate);

	printf("Structura Heap dupa creare vector elemente sortate: ");
	for (int i = 0; i < nrNoduri; i++)
		printf(" %d ", sHeap[i]);
	printf("\n");
	printf("Vectorul cu elementele sortate prin extragerea tuturor nodurilor din structura Heap: ");
	for (int i = 0; i < nrSortate; i++)
		printf(" %d ", vSortate[i]);
	printf("\n");

	// creare structura min-heap cu cheile din vectorul sortate descrescator
	int* minHeap, nrNoduriMin, capacitateMin;
	capacitateMin = DIM;
	minHeap = (int*)malloc(capacitateMin * sizeof(int));
	minHeap = creare_min_Heap(minHeap, nrNoduriMin, vSortate, nrSortate, capacitateMin);
	printf("Structura Min-Heap dupa creare din vector elemente sortate: ");
	for (int i = 0; i < nrNoduriMin; i++)
		printf(" %d ", minHeap[i]);
	printf("\n");


	// dezalocare vector suport structura Max-Heap
	if(sHeap)
		free(sHeap);

	// dezalocare vector suport structura Min-Heap
	if (minHeap)
		free(minHeap);


	// dezalocare vector cu chei sortate descrescator
	if (vSortate)
		free(vSortate);

	fclose(f);
	return 0;
}