#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

#define CAPACITATE_STOCARE_HEAP 10


int* realocare_structura_heap(int* heap_agregat, unsigned char* capacitate_heap_agregat, unsigned char nr_eleme_aditionale)
{
	unsigned char nr_chei = *capacitate_heap_agregat;
	*capacitate_heap_agregat += nr_eleme_aditionale;
	int* new_heap = malloc(*capacitate_heap_agregat * sizeof(int)); // alocare vector cu capacitate mai mare

	for (unsigned char i = 0; i < nr_chei; i++)
	{
		new_heap[i] = heap_agregat[i];
	}

	free(heap_agregat); // dezalocare structura heap curenta
	return new_heap; // noul vector este returnat in apelator unde heap_agregat se rescrie cu noua adresa
}

int* agregare_structuri_heap(int cheie_noua, int* heap1, unsigned char size_heap1,
							 int* heap2, unsigned char size_heap2, 
							 int* heap_agregat, unsigned char *size_heap_agregat, 
							 unsigned char* capacitate_heap_agregat)
{
	heap_agregat = malloc(*capacitate_heap_agregat * sizeof(int)); // alocare initiala pentru structura heap rezultata

	unsigned char i = 0; // offset in heap1
	unsigned char j = 0; // offset in heap2
	unsigned char k = 0; // offset in heap_agregat

	heap_agregat[k++] = cheie_noua; // scriere cheie in radacina heap agregat
	*size_heap_agregat += 1;		// incrementare numar de chei din structura heap

	unsigned char h = 0; // index de nivel
	unsigned char gata = 1;
	while (gata)
	{
		printf("Nivel %u\n", h);
		unsigned char l = i; // l - numar de chei copiate in iteratiile anterioare
		// traversare nivel h din heap 1 si copiere chei in heap_agregat
		for (; i < size_heap1 && i < (2 * h + 1) + l; i++) // i offset curent in heap1 
					/// ?? 2^h este nr de noduri pe nivel h
		{
			heap_agregat[k++] = heap1[i]; // copiere element din heap 1 in offset curent heap_agregat
			*size_heap_agregat += 1;
			if (*size_heap_agregat == *capacitate_heap_agregat)
			{
				heap_agregat = realocare_structura_heap(heap_agregat, capacitate_heap_agregat, 
														CAPACITATE_STOCARE_HEAP);
			}
		}

		l = j;
		// traversare nivel h din heap 2 si copiere chei in heap_agregat
		for (; j < size_heap2 && j < (2 * h + 1) + l; j++) // j offset curent in heap2
		{
			heap_agregat[k++] = heap2[j]; // copiere element din heap 2 in offset curent heap_agregat
			*size_heap_agregat += 1;
			if (*size_heap_agregat == *capacitate_heap_agregat)
			{
				heap_agregat = realocare_structura_heap(heap_agregat, capacitate_heap_agregat, 
														CAPACITATE_STOCARE_HEAP);
			}
		}

		if (i >= size_heap1 && j >= size_heap2)
			gata = 0; // nu mai exista elemente de adus din cele doua structuri heap de intrare in agregare
		h += 1; // trecere la nivel urmator in heap 1 si heap 2
	}


	return heap_agregat;
}

int main()
{
	int struct_heap1[] = {32, 12, 24, 7, 9, 17};
	int struct_heap2[] = {8, 2, 3};

	int* heap_rezultat = NULL;
	unsigned char capacitate_heap = CAPACITATE_STOCARE_HEAP; // capacitate de stocare initiala pentru heap_rezultat
	unsigned char nr_noduri_heap = 0; // nr de chei stocate de heap_rezultat


	heap_rezultat = agregare_structuri_heap(23, struct_heap1, sizeof(struct_heap1) / sizeof(int),
											struct_heap2, sizeof(struct_heap2) / sizeof(int),
											heap_rezultat, &nr_noduri_heap, &capacitate_heap);

	printf("Vector structura heap dupa agregare: ");
	for (unsigned char i = 0; i < nr_noduri_heap; i++)
	{
		printf("%d ", heap_rezultat[i]);
	}
	printf("\n");

	return 0;
}