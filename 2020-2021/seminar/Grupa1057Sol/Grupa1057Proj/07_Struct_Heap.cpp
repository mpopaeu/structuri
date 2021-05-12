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
int extragere_cheie_heap(int* strHeap, int& nrNoduri)
{
	int key;
	int offs_key = 0; // offset nod curent pentru care se aplica op de filtrare top-down
	int offs_max = -1; // offset descendent cu cheia maxima (max(left_key, right_key); pentru offs_key
	//preiau ultimul element din structura
	int lastElement = strHeap[nrNoduri - 1];
	key = strHeap[0];
	strHeap[0] = lastElement; //ultimul element devine primul

	nrNoduri -= 1; //numarul de chei scade cu 1

	int Left = 2 * offs_key + 1;
	int Right = 2 * offs_key + 2;

	if (Left < nrNoduri && Right < nrNoduri) // exista ambii descendenti
	{
		if (strHeap[Left] > strHeap[Right])
		{
			offs_max = Left;
		}
		else
		{
			offs_max = Right;
		}
	}
	else
	{
		if (Left < nrNoduri)
		{
			offs_max = Left;
		}
	}

	while (nrNoduri > 1 && offs_max != -1 && strHeap[offs_max] > strHeap[offs_key]) //nu se respecta relatia de ordine 
	{
		// strSize > 0 - exista cel putin 2 elemente in structura
		// max != -1 - exista cel putin 1 descendent pentru nodul curent strHeap[offs_key]
		// strHeap[max] > strHeap[offs_key] - nu se respecta relatia de ordine pentru un max-heap
		//interschimbare key-parinte
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[offs_max];
		strHeap[offs_max] = aux;

		// actualizare offset key in vector
		offs_key = offs_max;

		//calcul offset pentru noul key
		Left = 2 * offs_key + 1;
		Right = 2 * offs_key + 2;
		if (Left < nrNoduri && Right < nrNoduri) // exista 2 descendenti pentru nodul curent strHeap[offs_key]
		{
			if (strHeap[Left] > strHeap[Right]) 
			{
				offs_max = Left; // descendent stanga are cheia maxima
			}
			else
			{
				offs_max = Right; // descendnent dreapta are cheia maxima
			}
		}
		else
		{
			if (Left < nrNoduri) // exista 1 singur descendent (obligatoriu cel din stanga) pentru nodul curent
			{
				offs_max = Left;
			}
			else
			{
				offs_max = -1; // exista 0 descendenti pentru nodul curent
			}
		}
	}

	return key;
}

// creare structura min-heap cu cheile extrase succesiv din structura max-heap
// [in] strHeap - max-heap sursa de date pentru min-heap
// [in,out] nrNoduriMax - dimensiunea efectiva (nr noduri) max-heap
// [out] capacitateMin - capacitatea de stocare min-heap
// [out] nrNoduriMin - dimensiunea efectiva (nr noduri) min-heap
// return - adresa vectorului suport pentru structura min-heap
int* creare_min_heap(int* strHeap, int& nrNoduriMax, int& capacitateMin, int& nrNoduriMin)
{

}

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

	cheie = extragere_cheie_heap(sHeap, nrNoduri);
	printf("Cheia extrasa este: %d\n", cheie);
	printf("Structura Heap dupa extragere cheie radacina: ");
	for (int i = 0; i < nrNoduri; i++)
		printf(" %d ", sHeap[i]);
	printf("\n\n");

	// dezalocare vector suport structura Heap
	if(sHeap)
		free(sHeap);

	fclose(f);

	return 0;
}