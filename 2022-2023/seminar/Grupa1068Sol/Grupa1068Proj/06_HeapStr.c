#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 20

void inserare_cheie_heap(int* strHeap, int* strSize, int key)
{
	*strSize += 1;
	int offs_key = *strSize - 1;
	strHeap[offs_key] = key; 

	int offs_parinte = (offs_key - 1) / 2; 

	while (strHeap[offs_key] > strHeap[offs_parinte]) 
	{
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[offs_parinte];
		strHeap[offs_parinte] = aux;

		offs_key = offs_parinte;

		offs_parinte = (offs_key - 1) / 2;
	}
}


int stergere_cheie_heap(int* strHeap, int* strSize)
{
	int key;
	int offs_key = 0;
	int max = 0;
	
	int lastElement = strHeap[*strSize - 1];
	key = strHeap[0]; 
	strHeap[0] = lastElement; 

	*strSize -= 1; 

	int Left = 2 * offs_key + 1;
	int Right = 2 * offs_key + 2;

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

	while ((*strSize > 0) && (strHeap[max] > lastElement)) 
	{
		int aux = strHeap[offs_key];
		strHeap[offs_key] = strHeap[max];
		strHeap[max] = aux;

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
	int* strHeap = NULL; 

	strHeap = (int*)malloc(DIM * sizeof(int));
	int capacitate_stocare = DIM;

	int nKeys = 0, cheie; 

	FILE* f;
	f = fopen("HeapKeys.txt", "r");

	fscanf(f, "%d", &cheie);
	while (!feof(f))
	{
		if (nKeys == capacitate_stocare)
		{
			capacitate_stocare += DIM;
			int* new_strHeap = (int*)malloc(capacitate_stocare * sizeof(DIM));
			for (int i = 0; i < nKeys; i++)
				new_strHeap[i] = strHeap[i];

			free(strHeap);
			strHeap = new_strHeap;
		}

		inserare_cheie_heap(strHeap, &nKeys, cheie);

		fscanf(f, "%d", &cheie);
	}

	printf("\n Heap structure right after creation: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);

	inserare_cheie_heap(strHeap, &nKeys, 26); // a new key 26 is inserted into Heap structure

	printf("\n\n Heap structure after insertion of the key 26: ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);
	printf("\n");

	cheie = stergere_cheie_heap(strHeap, &nKeys);
	printf("\n\n Heap structure after deletion (key from the root node): ");
	for (int i = 0; i < nKeys; i++)
		printf(" %d ", strHeap[i]);
	printf("\n");

	printf("Deletion of all keys in the Heap structure: ");
	while (nKeys > 0)
	{
		printf(" %d ", stergere_cheie_heap(strHeap, &nKeys));
	}
	printf("\n\n");

	free(strHeap);

	fclose(f);
	return 0;
}