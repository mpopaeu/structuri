#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 7

// cautare si plasare cheie inserata intr-un max-heap
// strHeap - vectorul de chei din structura Heap (transfer prin valoare)
// strSize - numarul de noduri/chei din structura Heap (transfer prin adresa)
// key - cheie de inserat in structura Heap (transfer)
void inserare_cheie_heap(int* strHeap, int* strSize, int key)
{
	*strSize += 1;				 // incrementare dimensiune structura Heap (vector)
	int offs_key = *strSize - 1; // offset initial pt key (cheie de inserat in structura) -> i
	strHeap[offs_key] = key;	 // stocare key (cheie noua) in arbore/structura Heap

	int offs_parinte = (offs_key - 1) / 2; // calcul offset parinte -> offset calculat j

	while (strHeap[offs_key] > strHeap[offs_parinte])  // (in)validare pozitia lui key in arbore
	{		
		// interschimb cheie inserata (key) cu cheie parinte
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[offs_parinte];
		strHeap[offs_parinte] = aux;
		
		// modificare offset cheie inserata (dupa interschimb cu parinte)
		offs_key = offs_parinte;

		offs_parinte = (offs_key - 1) / 2; // recalculare offset parinte pentru cheie inserata (key)
	}
}


int stergere_cheie_heap(int* strHeap, int* strSize)
{
	int key;
	int offs_key = 0;
	int max = 0;

	int lastElement = strHeap[*strSize - 1]; // ultimul nod din arbore Heap
	key = strHeap[0]; // cheia din nodul radacina al struct Heap
	strHeap[0] = lastElement; // rescriere nod radacina cu cheia ultimului nod de pe ultimul nivel

	*strSize -= 1; // actualizare nr de noduri/chei din arbore Heap

	int Left = 2 * offs_key + 1; // descendent stanga initial pentru noua radacina (lastElement/strHeap[0])
	int Right = 2 * offs_key + 2; // descendent dreapata initial pentru noua radacina (lastElement/strHeap[0])

	if ((Left < *strSize) && (Right < *strSize))  // exista ambii descendenti pt noua radacina
	{
		if (strHeap[Left] > strHeap[Right]) // determinare descendent cu cheia maxima
		{
			max = Left;
		}
		else
		{
			max = Right;
		}
	}
	else // 0 sau 1 descendent pentru noua radacina
	{
		if (Left < *strSize)
		{
			max = Left; // maxim este unicul descendent
		}
	}

	while ((*strSize > 0) && (strHeap[max] > lastElement)) // lastElement nu respecta relatia de ordine cu descendentii
	{
		// interschimb lastElement cu descendentul cu cheia maxima 
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[max];
		strHeap[max] = aux;

		// actualizare offset lastElement
		offs_key = max;

		// re-calculare descendenti pentru noul offset al lui lastElement
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
	int* strHeap = NULL;	// vector stocare chei din structura Heap

	strHeap = (int*)malloc(DIM * sizeof(int)); // alocare vector suport pe capacitate initiala DIM
	int capacitate_stocare = DIM; // capacitate de stocare (nr maxim de chei stocat) initiala

	int nKeys = 0, cheie; // nKeys - nr. de chei din structura Heap la un moment

	FILE* f;
	f = fopen("HeapKeys.txt", "r");

	fscanf(f, "%d", &cheie);
	while (!feof(f))
	{
		if (nKeys == capacitate_stocare) // nr de noduri este la capacitate max de stocare in vector
		{
			// realocare vector pe capacitate mai mare
			capacitate_stocare += DIM;
			int* new_strHeap = (int*)malloc(capacitate_stocare * sizeof(DIM)); // noul vector suport pentru struct Heap
			for (int i = 0; i < nKeys; i++)
				new_strHeap[i] = strHeap[i]; // copiere chei din structura curenta (incarcata la max) pe noua structura Heao
											 // cheile se pastreaza pe aceleasi locatii pe noua structura

			free(strHeap); // eliberare mem heap pentru struct Heap curenta
			strHeap = new_strHeap; // comutare variabila accces vector suport pe noul vector suport struct Heap
		}

		inserare_cheie_heap(strHeap, &nKeys, cheie);

		fscanf(f, "%d", &cheie);
	}

	printf("\n Structura Heap initiala: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);

	inserare_cheie_heap(strHeap, &nKeys, 26);

	printf("\n\n Structura Heap dupa inserare cheie 26: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);
	printf("\n");

	cheie = stergere_cheie_heap(strHeap, &nKeys);

	printf("\n\n Structura Heap dupa stergere cheie din radacina: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);
	printf("\n");


	printf("Stergere chei din structura Heap: ");
	while (nKeys > 0)
	{
		printf(" %d ", stergere_cheie_heap(strHeap, &nKeys));
	}
	printf("\n\n");

	// Dezalocare vector suport 
	free(strHeap);

	printf("\n\n Structura Heap dupa dezalocare structura Heap: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);
	printf("\n");

	fclose(f);
	return 0;
}