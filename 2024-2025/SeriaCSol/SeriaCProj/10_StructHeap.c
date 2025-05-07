#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 20


void inserare_cheie_heap(int* strHeap, int* strSize, int key)
{
	*strSize += 1; // se actualizeaza numarul de noduri din structura (nr efectiv de chei din struct Heap)
	int offs_key = *strSize - 1;	 // offset nod/cheie care se inseareaza in structura Heap
	strHeap[offs_key] = key;		 // se scrie cheia de inserat in structura Heap

	int offs_parinte = (offs_key - 1) / 2; 

	while (strHeap[offs_key] > strHeap[offs_parinte]) 
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


int stergere_cheie_heap(int* strHeap, int* strSize)
{
	int key;			// cheie nod care se sterge din structura Heap
	int offs_key = 0;	// offset nod radacina; locul de unde se pleaca in procesul de cautare a pozitiei finale
	int max = 0;		
	//preiau ultimul element din structura
	int lastElement = strHeap[*strSize - 1];
	key = strHeap[0];
	strHeap[0] = lastElement; 

	*strSize -= 1;  // actualizare dimensiune efectiva a vectorului (nr de chei din structura Heap)

	int Left = 2 * offs_key + 1;
	int Right = 2 * offs_key + 2;

	if ((Left < *strSize) && (Right < *strSize)) 
	{
		// exista ambii descendenti pentru offs_key
		if (strHeap[Left] > strHeap[Right])		 
		{
			max = Left; // nodul din stanga are cheie mai mare decat cel din dreapta
		}
		else
		{
			max = Right; // nodul din dreapta are cheie mai mare decat cel din stanga
		}
	}
	else
	{
		if (Left < *strSize)
		{
			// exista un singur descendent pentru nodul offs_key (obligatoriu este descendent stanga deoarece arborele este binar complet)
			max = Left;
		}
	}

	while ((*strSize > 0) && (strHeap[max] > lastElement)) 
	{
		// relatia de ordine nu este corecta pentru un max-heap
		// interschimbare cheie cu descendentul cu cheia maxima
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[max];
		strHeap[max] = aux;

		// actualizare offset cheie care coboara in arbore
		offs_key = max;

		
		Left = 2 * offs_key + 1;
		Right = 2 * offs_key + 2;
		if ((Left < *strSize) && (Right < *strSize))
		{
			if (strHeap[Left] > strHeap[Right])
			{
				max = Left;
			}
			else
			{
				max = Right;
			}
		}
		else
		{
			if (Left < *strSize)
			{
				max = Left;
			}
		}
	}

	return key;
}



int main()
{
	int* strHeap = NULL;  // variabila acces la structura Heap

	strHeap = (int*)malloc(DIM * sizeof(int));
	int capacitate_stocare = DIM; // nr max de chei stocat de structura heap (arbore binar complet)

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
				new_strHeap[i] = strHeap[i]; // se copiaza cheile de pe structura curenta pe structura noua

			// dezalocare vector la capacitate maxima
			free(strHeap);
			// comutare pointer pe noua locatie extinsa
			strHeap = new_strHeap;
		}

		inserare_cheie_heap(strHeap, &nKeys, cheie);

		fscanf(f, "%d", &cheie);
	}

	printf("\n Structura Heap initiala: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);

	// inserare cheie 26 in structura Heap
	inserare_cheie_heap(strHeap, &nKeys, 26);

	printf("\n\n Structura Heap dupa inserare cheie 26: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);
	printf("\n");

	cheie = stergere_cheie_heap(strHeap, &nKeys);
	printf("\n\n Structura Heap dupa stergere cheie radacina: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);
	printf("\n");


	// prelucrare date/chei in ordine descrescatoare prin stergere repetata a nodului radacina
	printf("Stergere chei din structura Heap (prelucrare chei in ordine descrescatoare): ");
	while (nKeys > 0)
	{
		printf(" %d ", stergere_cheie_heap(strHeap, &nKeys));
	}
	printf("\n\n");

	// dezalocare vector suport structura max-heap
	free(strHeap);

	fclose(f);
	return 0;
}