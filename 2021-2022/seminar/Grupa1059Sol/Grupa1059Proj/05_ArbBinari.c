#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct NodArb
{
	struct Angajat ang;
	struct NodArb * stanga, *dreapta;
};

struct NodArb* inserare_nod(struct NodArb* r, struct Angajat a, unsigned char *flag_inserare)
{
	if (r)
	{
		if (a.cod < r->ang.cod)
		{
			r->stanga = inserare_nod(r->stanga, a, flag_inserare);
		}
		else
		{
			if (a.cod > r->ang.cod)
			{
				r->dreapta = inserare_nod(r->dreapta, a, flag_inserare);
			}
			else
				*flag_inserare = 0;
		}
		return r;
	}
	else
	{
		struct NodArb* nou = (struct NodArb*)malloc(sizeof(struct NodArb));
		nou->ang = a;
		nou->stanga = NULL;
		nou->dreapta = NULL;

		*flag_inserare = 1;
		return nou;
	}
}

void inordine(struct NodArb* r)
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
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	struct Angajat fang;
	char nume[64];

	struct NodArb* root = NULL;


	fscanf(f, "%hu,", &fang.cod);
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", nume, &fang.salariu);

		fang.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		unsigned char flag;
		root = inserare_nod(root, fang, &flag);

		if (flag)
			printf("\nAngajat %hu inserat in arbore binar de cautare.", fang.cod);
		else
		{
			printf("\nAngajatul %hu exista in arbore binar de cautare", fang.cod);
			free(fang.nume); // angajatul fang nu se insereaza in arbore
		}

		fscanf(f, "%hu,", &fang.cod);
	}

	printf("\nArborele dupa creare:");
	inordine(root);

	fclose(f);
}