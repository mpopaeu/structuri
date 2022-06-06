#include <stdio.h>
#include <malloc.h>

struct Nod
{
	unsigned char varf_graf;
	struct Nod* next;
};

typedef struct Nod Nod;

Nod* push(Nod* stack, unsigned char varf)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->varf_graf = varf;
	nou->next = stack;

	return nou;
}

Nod* pop(Nod* stack, unsigned char *varf)
{
	*varf = 0;
	if (stack)
	{
		*varf = stack->varf_graf;

		Nod* t = stack;
		stack = stack->next;

		free(t);
	}

	return stack;
}

unsigned char* traversare_DF(unsigned char** mat, unsigned char nrv, unsigned char vf_start)
{
	unsigned char* out = (unsigned char*)malloc(nrv * sizeof(unsigned char)); // banda de iesire
	unsigned char k = 0;

	unsigned char* VIS = (unsigned char*)malloc(nrv * sizeof(unsigned char)); // indicatori de stare
	for (unsigned char i = 0; i < nrv; i++)
		VIS[i] = 0;

	Nod* stack = NULL;

	stack = push(stack, vf_start);
	VIS[vf_start - 1] = 1; // comutare flag stare pentru varful de start

	while (stack)
	{
		unsigned char varf_extras;
		stack = pop(stack, &varf_extras); // extragere varf graf din varful stivei
		out[k++] = varf_extras; // salvare varf extras in banda de iesire

		for(unsigned char j = 0; j < nrv; j++)
			if (mat[varf_extras - 1][j] == 1)
			{
				// (j + 1)  este varf adiacent pentru varful extras cu pop mai sus
				if (VIS[j] == 0)
				{
					// varful (j + 1) are flag pe 0, deci nu a ajuns pe stack
					stack = push(stack, j + 1);
					VIS[j] = 1; // comutare flag varf (j + 1)
				}
			}
	}

	free(VIS);

	return out;
}

// traversare Breadth-First (inlocuire stack cu structura queue)

void main() {
	FILE* f;
	f = fopen("Graf.txt", "r");

	unsigned char ** mat_adiacenta;
	unsigned char nrVarfuri = 0, vfi, vfj;

	fscanf(f, "%hhu", &nrVarfuri); // preluare nr varfuri de pe prima linie din fisier
	// alocare matrice de adiacenta
	mat_adiacenta = (unsigned char**)malloc(nrVarfuri * sizeof(unsigned char*));
	for (unsigned char i = 0; i < nrVarfuri; i++)
		mat_adiacenta[i] = (unsigned char*)malloc(nrVarfuri * sizeof(unsigned char));

	// initializare matrice de adicenta cu valori nule
	for (unsigned char i = 0; i < nrVarfuri; i++)
		for (unsigned char j = 0; j < nrVarfuri; j++)
			mat_adiacenta[i][j] = 0;

	fscanf(f, "%hhu", &vfi);
	while (!feof(f)) {
		fscanf(f, "%hhu", &vfj);

		mat_adiacenta[vfi - 1][vfj - 1] = 1;
		mat_adiacenta[vfj - 1][vfi - 1] = 1; // graf neorientat

		fscanf(f, "%hhu", &vfi);
	}
	fclose(f);

	// afisare matrice de adiacenta
	printf("\nMatricea de adiacenta este:");
	for (unsigned char i = 0; i < nrVarfuri; i++)
	{
		printf("\n");
		for (unsigned char j = 0; j < nrVarfuri; j++)
			printf(" %hhu", mat_adiacenta[i][j]);
	}

	// traversare Depth-First
	unsigned char* outStream;
	outStream = traversare_DF(mat_adiacenta, nrVarfuri, 8);

	printf("\nTraversare Depth-First graf: ");
	for (unsigned char i = 0; i < nrVarfuri; i++)
		printf(" %hhu", outStream[i]);

	// dezalocare banda de iesire
	free(outStream);

	// dezalocare matrice de adiacenta
	for (unsigned char i = 0; i < nrVarfuri; i++)
		free(mat_adiacenta[i]); // dezalocare linie i

	free(mat_adiacenta); // dezalocare vector de pointeri la linii

}