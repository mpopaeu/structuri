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

unsigned char* traversare_DF(unsigned char** mata, unsigned char nr_varfuri, unsigned char varf_start)
{
	unsigned char* VIS = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	unsigned char* out = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	unsigned char k = 0; // offset curent pentru vectorul out (banda de iesire)

	for (unsigned char i = 0; i < nr_varfuri; i++)
		VIS[i] = 0;

	Nod* stack = NULL;
	stack = push(stack, varf_start);
	VIS[varf_start - 1] = 1; // comutare flag pentru varf_start
	while (stack)
	{
		unsigned char varfe;
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
	OutStream = traversare_DF(mat_adiacenta, nr_varfuri, 3);

	printf("\n\nOrdine varfuri la traversarea de tip Depth-First: ");
	for (unsigned char i = 0; i < nr_varfuri; i++)
		printf(" %hhu", OutStream[i]);

	// dezalocare structuri
	// banda de iesire de la traversare DF
	free(OutStream);

	// matricea de adicenta
	for (unsigned char i = 0; i < nr_varfuri; i++)
		free(mat_adiacenta[i]);
	free(mat_adiacenta);
}