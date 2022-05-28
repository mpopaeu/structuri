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
	Coada* nou = (Coada*)malloc(sizeof(Coada));
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
	{
		q = nou;
	}

	return q;
}

Coada* get(Coada* q, unsigned char *varf)
{
	*varf = 0;
	if (q)
	{
		*varf = q->id_varf;

		Coada* temp = q;
		q = q->next;

		free(temp);
	}

	return q;
}

unsigned char* traversare_BF(unsigned char ** mat_adiacenta, unsigned char nrv, unsigned char vf_start)
{
	unsigned char* out = (unsigned char*)malloc(nrv * sizeof(unsigned char));
	unsigned char offset_out = 0;
	unsigned char* VIS = (unsigned char*)malloc(nrv * sizeof(unsigned char));
	for (unsigned char i = 0; i < nrv; i++)
		VIS[i] = 0;

	Coada* q = NULL;
	q = put(q, vf_start);
	VIS[vf_start - 1] = 1;

	while (q)
	{
		unsigned char varf_extras;
		q = get(q, &varf_extras);
		out[offset_out++] = varf_extras;

		for (unsigned char j = 0; j < nrv; j++)
		{
			// identificare varfuri adiacente pentru varf_extras
			if (mat_adiacenta[varf_extras - 1][j] == 1)
			{
				// j + 1 este varf adiacent pentru varf_extras
				if (VIS[j] == 0)
				{
					// varful j + 1 nu a ajuns niciodata in coada
					// este eligibil pentru punere in coada (vizitare/prelucrare)
					q = put(q, j + 1);
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

	f = fopen("Graf.txt", "r");
	unsigned char** mat_adiacenta, nr_varfuri, vi, vj;

	fscanf(f, "%hhu", &nr_varfuri);
	// alocare matrice de adiacenta
	mat_adiacenta = (unsigned char**)malloc(nr_varfuri * sizeof(unsigned char*));
	for (unsigned char i = 0; i < nr_varfuri; i++)
		mat_adiacenta[i] = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));

	// initializare matrice de adiacenta
	for (unsigned char i = 0; i < nr_varfuri; i++)
		for (unsigned char j = 0; j < nr_varfuri; j++)
			mat_adiacenta[i][j] = 0;

	fscanf(f, "%hhu", &vi); // varf 1 al muchiei (i,j)
	while (!feof(f))
	{		
		fscanf(f, "%hhu", &vj); // varf 2 al muchiei (i,j)

		mat_adiacenta[vi - 1][vj - 1] = 1;
		mat_adiacenta[vj - 1][vi - 1] = 1;

		fscanf(f, "%hhu", &vi);
	}
	fclose(f);

	for (unsigned char i = 0; i < nr_varfuri; i++)
	{
		printf("\n");
		for (unsigned char j = 0; j < nr_varfuri; j++)
			printf(" %hhu", mat_adiacenta[i][j]);
	}

	unsigned char* OutStream;
	OutStream = traversare_BF(mat_adiacenta, nr_varfuri, 5);

	printf("\nTraversare graf BF: ");
	for (unsigned char i = 0; i < nr_varfuri; i++)
		printf(" %hhu", OutStream[i]);

	// traversare de tip Depth-First (stiva ca structura suport)

	// dezalocare OutStream

	// dezalocare matrice de adiacenta
}