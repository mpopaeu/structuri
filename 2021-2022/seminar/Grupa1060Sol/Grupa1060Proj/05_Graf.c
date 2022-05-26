#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Nod
{
	unsigned char id_varf;
	struct Nod* next;
};

typedef struct Nod Coada;

Coada* put(Coada* q, unsigned char varf)
{
	Coada* nou = malloc(sizeof(Coada));
	nou->id_varf = varf;
	nou->next = NULL;

	if (q)
	{
		Coada* temp = q;
		while (temp->next)
			temp = temp->next;

		temp->next = nou;
	}
	else
		q = nou;

	return q;
}

Coada* get(Coada* q, unsigned char* varf)
{
	if (q)
	{
		*varf = q->id_varf;

		Coada* temp = q;

		q = q->next;

		free(temp);
	}

	return q;
}

unsigned char* traversare_BF(unsigned char ** ma, unsigned char nr_varfuri, unsigned char id_varf_start)
{
	unsigned char* out = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	unsigned char k = 0;
	unsigned char* VIS = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	for (unsigned char i = 0; i < nr_varfuri; i++)
		VIS[i] = 0; // i + 1 este varful i, VIS[i] - indicator de stare pt varful i + 1

	Coada* Queue = NULL;

	Queue = put(Queue, id_varf_start);
	VIS[id_varf_start - 1] = 1; // marcare varf de start ca fiind luat in considerare pentru prelucrare/vizitare

	while (Queue)
	{
		unsigned char varf_extras;
		Queue = get(Queue, &varf_extras);

		out[k++] = varf_extras; // salvare varf extras in banda de iesire
		for (unsigned char j = 0; j < nr_varfuri; j++)
		{
			if (ma[varf_extras - 1][j] == 1)
			{
				// j + 1 este adiacent lui varf_extras
				if (VIS[j] == 0)
				{
					// j + 1 nu a fost considerat in vederea vizitarii/prelucrarii
					Queue = put(Queue, j + 1);
					VIS[j] = 1;
				}
			}
		}
	}

	free(VIS);

	return out;
}

void main()
{
	FILE* f;
	unsigned char** mat_adiacenta, nr_varfuri, vm_st, vm_dr;

	f = fopen("Graf.txt", "r");
	// preluare din fisier a nr de varfuri graf
	fscanf(f, "%hhu", &nr_varfuri);

	// alocare matrice de adiacenta
	mat_adiacenta = (unsigned char**)malloc(nr_varfuri * sizeof(unsigned char*));
	for (unsigned char i = 0; i < nr_varfuri; i++)
		mat_adiacenta[i] = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));

	// initializare matrice de adiacenta; initial, nu exista muchie in graf
	for (unsigned char i = 0; i < nr_varfuri; i++)
		for (unsigned char j = 0; j < nr_varfuri; j++)
			mat_adiacenta[i][j] = 0;

	fscanf(f, "%hhu", &vm_st);
	while (!feof(f))
	{
		// exista muchie in graf
		fscanf(f, "%hhu", &vm_dr);

		mat_adiacenta[vm_st - 1][vm_dr - 1] = 1;
		mat_adiacenta[vm_dr - 1][vm_st - 1] = 1;

		// citire varf pentru urmatoare muchie din graf
		fscanf(f, "%hhu", &vm_st);
	}
	fclose(f);

	// afisare la consola a matricei de adiacenta
	for (unsigned char i = 0; i < nr_varfuri; i++)
	{
		printf("\n");
		for (unsigned char j = 0; j < nr_varfuri; j++)
			printf(" %hhu", mat_adiacenta[i][j]);
	}

	// traversare Breadth-First a grafului
	unsigned char* OutStream;
	OutStream = traversare_BF(mat_adiacenta, nr_varfuri, 1);

	// traversare banda de iesire cu ordine varfuri de prelucrart/vizitat
	printf("\n\nTraversare Breadth-First a grafului: ");
	for (unsigned char i = 0; i < nr_varfuri; i++)
		printf(" %hhu", OutStream[i]);

	// traversare DF a grafului

	// dezalocare structuri
}