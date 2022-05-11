#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define HASH_TABLE_SIZE 50

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct ArbBin
{
	struct Angajat ang;
	struct ArbBin* stanga, *dreapta;
};

struct ArbBin* inserare_arbore(struct ArbBin *r, struct Angajat a, unsigned char *flag_inserare)
{
	if (r)
	{
		// se continua cautarea locului de inserat
		if (r->ang.cod > a.cod)
			r->stanga = inserare_arbore(r->stanga, a, flag_inserare);
		else
			if (r->ang.cod < a.cod)
				r->dreapta = inserare_arbore(r->dreapta, a, flag_inserare);
			else
				*flag_inserare = 0; // se abandaoneaza operatia de inserare
		return r;
	}
	else
	{
		// am gasit locul de inserat
		struct ArbBin* nou = (struct ArbBin*)malloc(sizeof(struct ArbBin));
		nou->ang = a;
		nou->stanga = NULL;
		nou->dreapta = NULL;

		*flag_inserare = 1;

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

struct ArbBin* dezalocare_arbore(struct ArbBin* r)
{
	if (r)
	{
		r->stanga = dezalocare_arbore(r->stanga);
		r->dreapta = dezalocare_arbore(r->dreapta);

		free(r->ang.nume);
		free(r);	

		return NULL;
	}
}

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r");
	struct Angajat fang;
	char buffer[128];

	struct ArbBin* root = NULL;


	fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia #1
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", buffer, &fang.salariu);

		fang.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fang.nume, buffer);

		unsigned char flag;
		root = inserare_arbore(root, fang, &flag);

		if (flag)
		{
			printf("\nAngajat %hu inserat in arbore.", fang.cod);
		}
		else
		{
			printf("\nEsec inserare angajat %hu in arbore.", fang.cod);
			free(fang.nume);
		}

		fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia urmatoare
	}
	fclose(f);

	printf("\nTraversare inordine arbore:");
	inordine(root);

	root = dezalocare_arbore(root);
	printf("\nTraversare inordine arbore dupa dezalocare:");
	inordine(root);
}

