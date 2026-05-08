#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 20

// inserare cheie
void inserare_cheie_heap(int* strHeap, int* strSize, int key)
{
	*strSize += 1;
	int offs_key = *strSize - 1;
	strHeap[offs_key] = key; // inserare intiala cheie in structura Heap

	int offs_parinte = (offs_key - 1) / 2; // offset element/nod parinte pentru key

	while (offs_key > 0 && // offs_key 0 inseamna ca noua cheie key este radacina de arbore max-heap
		strHeap[offs_key] > strHeap[offs_parinte]) // nu se respecta relatia de ordine pentru un max-heap
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

// procedura filtrare top-down
// apelata pentru operatia de stergere cheie in structura Heap
//////
int stergere_cheie_heap(int* strHeap, int* strSize)
{
	int key; // cheie din radacina arbore structura Heap
	int offs_key = 0; // offset curent cheie care "coboara" in arborele Hep
	int max = 0; // offset cheie maxima descendenti cheie care "coboara" in arborele heap
	//preiau ultimul element din structura
	int lastElement = strHeap[*strSize - 1]; // cheie curenta care va rescrie nodul radacina; este cheie care "coboara" in arbore
	key = strHeap[0];
	strHeap[0] = lastElement; //ultimul element devine primul; rescriere radacina structura Heap

	*strSize -= 1; //numarul de chei scade cu 1; cheia de sters ramane in afara limitelor cu chei valide in arbore/vector

	int Left = 2 * offs_key + 1; // offset descendent stanga
	int Right = 2 * offs_key + 2; // offset descendent dreapta

	if ((Left < *strSize) && (Right < *strSize)) // exista ambii descendenti
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

	while ((*strSize > 0) && (strHeap[max] > lastElement)) //nu se respecta relatia de ordine 
	{
		//interschimbare key-parinte
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[max];
		strHeap[max] = aux;

		// actualizare offset key in vector
		offs_key = max;

		//calcul offset pentru noul key
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
	int* strHeap = NULL; // vector suport structura Heap

	strHeap = (int*)malloc(DIM * sizeof(int));
	int capacitate_stocare = DIM;

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
			// astfel incat relatiile dintre noduri se pastreaza
			capacitate_stocare += DIM;
			int* new_strHeap = (int*)malloc(capacitate_stocare * sizeof(DIM));
			for (int i = 0; i < nKeys; i++)
				new_strHeap[i] = strHeap[i];

			// dezalocare vector la capacitate maxima
			free(strHeap);
			// comutare pointer strHeap pe noua locatie extinsa (vector new_strHeap)
			strHeap = new_strHeap;
		}

		inserare_cheie_heap(strHeap, &nKeys, cheie);

		fscanf(f, "%d", &cheie);
	}

	fclose(f);

	printf("\n Structura Heap initiala: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);

	// inserare cheie 32 in structura max-heap
	inserare_cheie_heap(strHeap, &nKeys, 32);

	printf("\n Structura Heap dupa inserarea cheii 32: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);


	int cheie_eliminata = stergere_cheie_heap(strHeap, &nKeys);
	printf("\n Structura Heap dupa stergere nod radacina %d: ", cheie_eliminata);
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);
	cheie_eliminata = stergere_cheie_heap(strHeap, &nKeys);
	printf("\n Structura Heap dupa stergere nod radacina %d: ", cheie_eliminata);
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);

	// dezalocare structura 
	free(strHeap); // dezalocare vector de chei !! dupa "extragerea" tuturor cheilor din arbore -> nKeys == 0

}