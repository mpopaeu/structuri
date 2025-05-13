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

	// validare structura stanga mai mare decat cea din dreapta la agregare
	if (size_heap1 < size_heap2)
	{
		// structura dreapta este mai mare

		// intreschimb de structuri la nivel de vectori si dimensiuni
		int* paux = heap1;
		heap1 = heap2;
		heap2 = paux;

		unsigned char daux = size_heap1;
		size_heap1 = size_heap2;
		size_heap2 = daux;
	}

	unsigned char nr_h = 1; // nr chei de pe nivel h: 1 cheie pe nivel 1
	unsigned char gata = 1;
	while (gata)
	{
		unsigned char l = i; // l - numar de chei copiate in heap agregat in iteratiile anterioare
		// traversare nivel h din heap 1 si copiere chei in heap_agregat
		for (; i < size_heap1 && i < nr_h + l; i++) // i offset curent in heap1 
		{
			heap_agregat[k++] = heap1[i]; // copiere element din heap 1 in offset curent heap_agregat
			*size_heap_agregat += 1;
			if (*size_heap_agregat == *capacitate_heap_agregat)
			{
				heap_agregat = realocare_structura_heap(heap_agregat, capacitate_heap_agregat, 
														CAPACITATE_STOCARE_HEAP);
			}
		}


		// traversare nivel h din heap 2 si copiere chei in heap_agregat
		for (; j < size_heap2 && j < nr_h + l; j++) // j offset curent in heap2
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
		nr_h = nr_h * 2; // numarul de chei de pe nivelul urmator accesat in interatia urmatoare
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

	// 1. cele doua structuri de intrare trebuie sa aiba o diferenta de inaltime de maxim 1 nivel pentru a obtine
	// o structura agregata ca arbore binar complet
	// 2. este posibil ca structura din dreapta sa fie mai inalta (max 1 nivel) fata de cea din stanga.
	// cele doua structuri heap de intrare se interschimba pentru a avea un arbore binar complet pe structura rezultata
	// (rezolvare: vezi implementare agregare_structuri_heap)
	
	//heap_rezultat = agregare_structuri_heap(23, struct_heap1, sizeof(struct_heap1) / sizeof(int),
	//										struct_heap2, sizeof(struct_heap2) / sizeof(int),
	//										heap_rezultat, &nr_noduri_heap, &capacitate_heap);

	heap_rezultat = agregare_structuri_heap(23, struct_heap2, sizeof(struct_heap2) / sizeof(int),
											struct_heap1, sizeof(struct_heap1) / sizeof(int),
											heap_rezultat, &nr_noduri_heap, &capacitate_heap);

	printf("Vector structura heap dupa agregare: ");
	for (unsigned char i = 0; i < nr_noduri_heap; i++)
	{
		printf("%d ", heap_rezultat[i]);
	}
	printf("\n");

	// structura este cea corespunzatoare figurii a din suport de curs
	// cheia din nodul radacina trebuie sa fie validata in raport cu descendentii sai prin filtrarea top-down
	// vezi suport de curs operatie de stergere radacina din arbore Heap !!! pentru a duce structura Heap agregata
	// in situatia prezentata de figura c) din slide suport de curs

	return 0;
}