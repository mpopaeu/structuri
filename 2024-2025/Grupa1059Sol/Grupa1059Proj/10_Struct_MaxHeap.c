#include <stdio.h>
#include <malloc.h>

#define CAPACITATE_STOCARE_STRUCT_HEAP 6

unsigned short int *agregare_struct_heap(unsigned short int *struct_heap_1, unsigned short int size_struct_heap1,
										 unsigned short int* struct_heap_2, unsigned short int size_struct_heap2,
										 unsigned short int* struct_heap_agregata, unsigned short int *nr_noduri,
										 unsigned short int * capacitate_stocare_agregat,
										 unsigned short int cheie)
{
	unsigned short int k = 0; // offset curent in structura agregata
	struct_heap_agregata[k++] = cheie; // inserare cheie in structura agreagata 
	*nr_noduri += 1;

	// structura heap 1 (stanga) trebuie sa fie mai mare decat cealalta pentru a obtine o structura heap agregata 
	// corecta din punct de vedere al asezarii nodurilor in arborele Heap
	if (size_struct_heap1 < size_struct_heap2)
	{
		// structura heap 2 este mai mare
		// se interschimba pointerii de acces la structuri (vector) si dimensiunile celor 2 vectori

		unsigned short int* paux = struct_heap_1;
		struct_heap_1 = struct_heap_2;
		struct_heap_2 = paux;

		unsigned short int saux = size_struct_heap1;
		size_struct_heap1 = size_struct_heap2;
		size_struct_heap2 = saux;
	}

	unsigned flag = 1;
	unsigned short int nr_h = 1; // numar de noduri de pe nivel curent h
	unsigned short int i = 0;	 // offset de traversare structura heap struct_heap_1
	unsigned short int j = 0;	 // offset de traversare structura heap struct_heap_2
	while (flag)
	{
		unsigned short int l = i; // nr elemente preluate din struct_heap_1 si struct_heap_2 in interatiile anterioare
		for (i; i < nr_h + l && i < size_struct_heap1; i++)
		{
			struct_heap_agregata[k++] = struct_heap_1[i];
			*nr_noduri += 1;
			// validare nr_noduri mai mic decat capacitate
			if (*nr_noduri == *capacitate_stocare_agregat)
			{
				// nu mai exista pozitii disponibile in structura agregata
				// realocare structura agregata pe +CAPACITATE_STOCARE_STRUCT_HEAP elemente
				*capacitate_stocare_agregat = *capacitate_stocare_agregat + CAPACITATE_STOCARE_STRUCT_HEAP;
				unsigned short int* new_struct_heap = malloc((*capacitate_stocare_agregat) * sizeof(unsigned short int));
				for (unsigned short int idx = 0; idx < *nr_noduri; idx++)
				{
					// mutare elemente de pe structura curenta pe noua structra
					new_struct_heap[idx] = struct_heap_agregata[idx];
				}
				// dezalocare structura cu capacitate la maxim
				free(struct_heap_agregata);
				// comutare pe noua structura
				struct_heap_agregata = new_struct_heap;
			}
		}
		l = j;
		for (j; j < nr_h + l && j < size_struct_heap2; j++)
		{
			struct_heap_agregata[k++] = struct_heap_2[j];
			*nr_noduri += 1;
			// validare nr_noduri mai mic decat capacitate
			if (*nr_noduri == *capacitate_stocare_agregat)
			{
				// nu mai exista pozitii disponibile in structura agregata
				// realocare structura agregata pe +CAPACITATE_STOCARE_STRUCT_HEAP elemente
				*capacitate_stocare_agregat = *capacitate_stocare_agregat + CAPACITATE_STOCARE_STRUCT_HEAP;
				unsigned short int* new_struct_heap = malloc((*capacitate_stocare_agregat) * sizeof(unsigned short int));
				for (unsigned short int idx = 0; idx < *nr_noduri; idx++)
				{
					// mutare elemente de pe structura curenta pe noua structra
					new_struct_heap[idx] = struct_heap_agregata[idx];
				}
				// dezalocare structura cu capacitate la maxim
				free(struct_heap_agregata);
				// comutare pe noua structura
				struct_heap_agregata = new_struct_heap;
			}
		}
		if (i >= size_struct_heap1 && j >= size_struct_heap2)
			flag = 0;

		nr_h = nr_h * 2; // determinare numar de chei de pe nivel urmator (mai jos pe arborele Heap)
	}

	return struct_heap_agregata;
}

int main()
{
	unsigned short int *struct_heap_agregata = NULL; // structura max-heap cu elemente rezultate din agregare structuri heap
	unsigned short int struct_heap_1[] = {32, 12, 24, 7, 9, 17};
	unsigned short int struct_heap_2[] = {8, 2, 3};
	unsigned short int capacitate_stocare = CAPACITATE_STOCARE_STRUCT_HEAP;
	unsigned short int nr_noduri_struct_heap = 0;

	struct_heap_agregata = malloc(capacitate_stocare * sizeof(unsigned short int)); // alocare structura heap agregata la capacitate max

	// 1. ma asigur ca diferenta de inaltime dintre cele doua structuri este de maxim 1 nivel!!!!
	// 2. ma asigur ca ultimul nivel din structura heap 1 este complet ocupat cu noduri daca cele doua structuri Heap
	// au aceeasi inaltime. Scopul este ca structura Heap agregata sa fie corecta din punct de vedere al asezarii nodurilor:
	// arbore bina complet
	struct_heap_agregata = agregare_struct_heap(struct_heap_2, sizeof(struct_heap_2) / sizeof(unsigned short int),
											struct_heap_1, sizeof(struct_heap_1) / sizeof(unsigned short int),
											struct_heap_agregata, &nr_noduri_struct_heap, &capacitate_stocare,
											23);

	printf("Structura agregata cu nr chei = %hu si capacitate de stocare = %hu este: ", 
				nr_noduri_struct_heap, capacitate_stocare);
	for (unsigned short int i = 0; i < nr_noduri_struct_heap; i++)
		printf("%hu ", struct_heap_agregata[i]);
	printf("\n\n");

	// se apeleaza functia de cautare a locului corect in arborele Heap pentru nodul radacina (cheia inserata 23!!!)
	// vezi suport curs: operatia de stergere!!!

	return 0;
}