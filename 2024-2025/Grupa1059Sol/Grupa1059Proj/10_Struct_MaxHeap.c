#include <stdio.h>
#include <malloc.h>

#define CAPACITATE_STOCARE_STRUCT_HEAP 10

unsigned short int *agregare_struct_heap(unsigned short int *struct_heap_1, unsigned short int size_struct_heap1,
										 unsigned short int* struct_heap_2, unsigned short int size_struct_heap2,
										 unsigned short int* struct_heap_agregata, unsigned short int *nr_noduri,
										 unsigned short int * capacitate_stocare_agregat,
										 unsigned short int cheie)
{
	unsigned short int k = 0; // offset curent in structura agregata
	struct_heap_agregata[k++] = cheie; // inserare cheie in structura agreagata
	*nr_noduri += 1;

	unsigned flag = 1;
	unsigned short int h = 0;
	unsigned short int i = 0;
	unsigned short int j = 0;
	while (flag)
	{
		unsigned short int l = i;
		for (i; i < (2 * h + 1) + l && i < size_struct_heap1; i++)
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
		for (j; j < (2 * h + 1) + l && j < size_struct_heap2; j++)
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

		h += 1; // incrementare nivel
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

	struct_heap_agregata = agregare_struct_heap(struct_heap_1, sizeof(struct_heap_1) / sizeof(unsigned short int),
											struct_heap_2, sizeof(struct_heap_2) / sizeof(unsigned short int),
											struct_heap_agregata, &nr_noduri_struct_heap, &capacitate_stocare,
											23);

	return 0;
}