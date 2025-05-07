#include <stdio.h>
#include <malloc.h>

#define CAPACITATE_STOCARE_HEAP 7

int* realocare_vector_heap(int* h_rezultat, unsigned char* capacitate, unsigned char capacitate_suplimentara)
{
	unsigned char nr_chei = *capacitate; // nr chei identic cu capacitate
	*capacitate = *capacitate + capacitate_suplimentara; // marire capacitate maxima de stocare a vectorului

	int* new_vector_heap = malloc(*capacitate * sizeof(int)); // alocare vector nou pe capacitate noua

	// mutare elemente pe noul vector
	for (unsigned char i = 0; i < nr_chei; i++)
	{
		new_vector_heap[i] = h_rezultat[i];
	}

	free(h_rezultat); // vectorul curent este dezalocat

	return new_vector_heap; // adresa noului vector suport pentru heap agregat
}

int* agregare_structuri_heap(int* h1, unsigned char dim_h1,
							 int* h2, unsigned char dim_h2, 
							 unsigned char* capacitate, unsigned char* nr_chei,
							 int cheie_inserata)
{
	int* h_rezultat = malloc(*capacitate * sizeof(int));
	h_rezultat[0] = cheie_inserata; // cheia noua se aseaza pe radacina de structura heap agregata

	*nr_chei = 1;

	if (dim_h1 < dim_h2)
	{
		// structura h2 este mai mare (eventual cu inaltime mai mare)
		// interschimb adresa astfel incat h1 este intotdeauna mai mare (eventual mai inalt)

		int* paux = h1;
		h1 = h2;
		h2 = paux;

		// se interschimba si dimensiunile pentru accesarea corecta a elementelor din vectorii interschimbati mai sus
		unsigned char daux = dim_h1;
		dim_h1 = dim_h2;
		dim_h2 = daux;
	}

	unsigned char flag = 1; // flag determinare momemnt finalizare operatie de salvare a cheilor din h1 si h2 in struct agregata
	unsigned char i = 0;	// offset traversare h1
	unsigned char j = 0;	// offset traversare h2
	unsigned int nr_chei_nivel_curent = 1; // nr maxim de chei de pe nivel curent

	while (flag == 1) // traversare structuri h1 si h2 pe niveluri in tandem 
	{
		// fiecare iteratie de while acceseaza acelasi nivel din h1 si h2
		unsigned char l = i; // numar de chei salvate in structura agregata de pe nivelurile superioare
		for (; i < dim_h1 && i < nr_chei_nivel_curent + l; i++)
		{
			h_rezultat[*nr_chei] = h1[i];
			*nr_chei += 1;

			if (*nr_chei == *capacitate)
			{
				// nu mai exista spatiu pentru salvare de chei in heap agregat
				h_rezultat = realocare_vector_heap(h_rezultat, capacitate, CAPACITATE_STOCARE_HEAP);
			}
		}

		for (; j < dim_h2 && j < nr_chei_nivel_curent + l; j++)
		{
			h_rezultat[*nr_chei] = h2[j];
			*nr_chei += 1;

			if (*nr_chei == *capacitate)
			{
				// nu mai exista spatiu pentru salvare de chei in heap agregat
				h_rezultat = realocare_vector_heap(h_rezultat, capacitate, CAPACITATE_STOCARE_HEAP);
			}
		}

		if (i == dim_h1 && j == dim_h2) // suficienta validarea doar cu i deoarece dim_h2 <= dim_h1
		{
			flag = 0;
		}

		nr_chei_nivel_curent = nr_chei_nivel_curent * 2; // numar maxim de chei de pe nivel inferior
	}

	return h_rezultat;
}

int main()
{
	int heap1[] = {32, 12, 24, 7, 9, 17};
	int heap2[] = {8, 2, 3};

	int* heap_agregat = NULL;
	unsigned char capacitate, nr_chei;

	capacitate = CAPACITATE_STOCARE_HEAP;

	heap_agregat = agregare_structuri_heap(heap1, sizeof(heap1)/sizeof(int),
										   heap2, sizeof(heap2)/sizeof(int),
										   &capacitate, &nr_chei, 23);

	printf("Structura heap agregata: ");
	for (unsigned char i = 0; i < nr_chei; i++)
		printf("%d ", heap_agregat[i]);
	printf("\n");

	return 0;
}