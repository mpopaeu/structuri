#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct ArbBin
{
	struct Angajat ang;
	struct ArbBin* stanga, * dreapta;
};


struct ArbBin* inserare_arbore(struct ArbBin* r, struct Angajat a, unsigned char *inserat)
{
	if (r)
	{
		if (r->ang.cod > a.cod)
			r->stanga = inserare_arbore(r->stanga, a, inserat);
		else
			if (r->ang.cod < a.cod)
				r->dreapta = inserare_arbore(r->dreapta, a, inserat);
			else
				*inserat = 0; // inserarea nu are loc; cheie duplicat
		return r;
	}
	else
	{
		// r == NULL; pozitia pe care nodul nou o va ocupa in arbore
		struct ArbBin* nou = (struct ArbBin*)malloc(sizeof(struct ArbBin));
		nou->ang = a;
		nou->dreapta = NULL;
		nou->stanga = NULL;

		*inserat = 1; // succes inserare
		return nou;
	}
}

void inordine(struct ArbBin* r)
{
	if (r)
	{
		inordine(r->stanga);
		printf("\n\t%hu %s", r->ang.cod, r->ang.nume);
		inordine(r->dreapta);
	}
}

void main()
{
	struct ArbBin* root = NULL;
	FILE* f;
	struct Angajat tmp;

	f = fopen("Angajati.txt", "r");
	fscanf(f, "%hu,", &tmp.cod);

	while (!feof(f))
	{
		char nn[64];
		fscanf(f, "%[^,],%f\n", nn, &tmp.salariu);

		tmp.nume = malloc(sizeof(char) * (strlen(nn) + 1));
		strcpy(tmp.nume, nn);

		unsigned char inserat;
		root = inserare_arbore(root, tmp, &inserat);

		if (inserat)
		{
			printf("\nAngajatul %hu este inserat", tmp.cod);
		}
		else
		{
			printf("\nAngajatul %hu nu este inserat", tmp.cod);
			free(tmp.nume);
		}

		fscanf(f, "%hu,", &tmp.cod);
	}
	fclose(f);


	printf("\nArborele dupa creare:");
	inordine(root);
}