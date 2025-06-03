#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Nod
{
	unsigned char varfg;
	struct Nod* next;
};

typedef struct Nod Nod;

Nod* push(Nod* list, unsigned char varf)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->varfg = varf;
	nou->next = list;

	return nou;
}


Nod* put(Nod* list, unsigned char varf)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->varfg = varf;
	nou->next = NULL;

	if (list == NULL)
	{
		list = nou;
	}
	else
	{
		Nod* tmp = list;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = nou;
	}

	return list;
}

Nod* pop(Nod* list, unsigned char* varf_extras)
{
	if (list)
	{
		*varf_extras = list->varfg;

		Nod* temp = list;
		list = list->next;

		free(temp);
	}

	return list;
}

Nod* get(Nod* list, unsigned char* varf_extras)
{
	if (list)
	{
		*varf_extras = list->varfg;

		Nod* temp = list;
		list = list->next;

		free(temp);
	}

	return list;
}

unsigned char* traversare_DF(unsigned char** mata, unsigned char nr_varfuri, unsigned char varf_start)
{
	// vector flag-uri (indicatori de stare) pentru varfuri din graf
	unsigned char* VIS = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	// vector care se populeaza cu varfuri din graf conform traversarii DF
	unsigned char* out = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	unsigned char k = 0; // offset curent pentru vectorul out (banda de iesire)

	// initializare flag-uri salvare varfuri pe structura stack
	for (unsigned char i = 0; i < nr_varfuri; i++)
		VIS[i] = 0;

	Nod* stack = NULL; // initializare structura stack
	stack = push(stack, varf_start); // scriere varf de start pe stack
	VIS[varf_start - 1] = 1; // comutare flag pentru varf_start
	while (stack)
	{
		unsigned char varfe; // id varf extras de pe stack
		stack = pop(stack, &varfe); // se extrage varful de graf de pe stiva
		out[k++] = varfe;

		// identificare si salvare pe stiva a vafurilor adiacente lui varfe
		for (unsigned char j = 0; j < nr_varfuri; j++)
			if (mata[varfe - 1][j] == 1)
			{
				// j + 1 este varf adiacent pentru varfe
				if (VIS[j] == 0)
				{
					// j + 1 nu fost luat in considerare pentru prelucrare in iteratiile anterioare
					VIS[j] = 1;
					stack = push(stack, j + 1);
				}
			}
	}

	// dezalocare vector VIS
	free(VIS);

	return out;
}


unsigned char* traversare_BF(unsigned char** mata, unsigned char nr_varfuri, unsigned char varf_start)
{
	// vector flag-uri (indicatori de stare) pentru varfuri din graf
	unsigned char* VIS = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	// vector care se populeaza cu varfuri din graf conform traversarii DF
	unsigned char* out = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	unsigned char k = 0; // offset curent pentru vectorul out (banda de iesire)

	// initializare flag-uri salvare varfuri pe structura stack
	for (unsigned char i = 0; i < nr_varfuri; i++)
		VIS[i] = 0;

	Nod* queue = NULL; // initializare structura stack
	queue = put(queue, varf_start); // scriere varf de start pe stack
	VIS[varf_start - 1] = 1; // comutare flag pentru varf_start
	while (queue)
	{
		unsigned char varfe; // id varf extras de pe stack
		queue = get(queue, &varfe); // se extrage varful de graf de pe stiva
		out[k++] = varfe;

		// identificare si salvare pe stiva a vafurilor adiacente lui varfe
		for (unsigned char j = 0; j < nr_varfuri; j++)
			if (mata[varfe - 1][j] == 1)
			{
				// j + 1 este varf adiacent pentru varfe
				if (VIS[j] == 0)
				{
					// j + 1 nu fost luat in considerare pentru prelucrare in iteratiile anterioare
					VIS[j] = 1;
					queue = put(queue, j + 1);
				}
			}
	}

	// dezalocare vector VIS
	free(VIS);

	return out;
}

void main()
{
	FILE* f;

	f = fopen("Graf.txt", "r");

	unsigned char** mat_adiacenta, nr_varfuri, vas, vad;

	// preluare nur varfuri graf de pe prima linie din fisierul text
	fscanf(f, "%hhu,", &nr_varfuri);

	// alocare matrice de adiacenta (patratica)
	mat_adiacenta = (unsigned char**)malloc(nr_varfuri * sizeof(unsigned char*));
	for (unsigned char i = 0; i < nr_varfuri; i++)
		mat_adiacenta[i] = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));

	// initializare matrice de adiacenta
	for (unsigned char i = 0; i < nr_varfuri; i++)
		for (unsigned char j = 0; j < nr_varfuri; j++)
			mat_adiacenta[i][j] = 0;


	fscanf(f, "%hhu,", &vas);
	while (!feof(f))
	{
		fscanf(f, "%hhu", &vad);

		// graf neorientat; daca exista muchie(1, 2), atunci trebuie marcata si muchie(2, 1)
		mat_adiacenta[vas - 1][vad - 1] = 1;
		mat_adiacenta[vad - 1][vas - 1] = 1;

		fscanf(f, "%hhu,", &vas);
	}

	printf("\nMatricea de adiacenta:");
	for (unsigned char i = 0; i < nr_varfuri; i++)
	{
		printf("\n");
		for (unsigned char j = 0; j < nr_varfuri; j++)
			printf(" %hhu", mat_adiacenta[i][j]);
	}

	unsigned char* OutStream = NULL;
	OutStream = traversare_DF(mat_adiacenta, nr_varfuri, 5);

	printf("\n\nOrdine varfuri la traversarea de tip Depth-First: ");
	for (unsigned char i = 0; i < nr_varfuri; i++)
		printf(" %hhu", OutStream[i]);


	unsigned char* OutStream_BF = NULL;
	OutStream_BF = traversare_BF(mat_adiacenta, nr_varfuri, 5);

	printf("\n\nOrdine varfuri la traversarea de tip Breadth-First: ");
	for (unsigned char i = 0; i < nr_varfuri; i++)
		printf(" %hhu", OutStream_BF[i]);

	// dezalocare structuri
	// banda de iesire de la traversare DF
	free(OutStream);

	// banda de iesire de la traversare BF
	free(OutStream_BF);

	// matricea de adicenta
	for (unsigned char i = 0; i < nr_varfuri; i++)
		free(mat_adiacenta[i]);
	free(mat_adiacenta);
}