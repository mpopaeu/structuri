
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	char* nume;
	unsigned short int cod;
	float salariu;
};

struct NodArb
{
	struct Angajat ang;
	struct NodArb* stanga, * dreapta;
};

struct NodArb* inserare_nod(struct NodArb* r, struct Angajat a, unsigned char *flag_inserare)
	{
	if (r) // r este nod curent; parametrul r este succesiv nod plasat pe drumul de la radacina 
			// la locul de inserat al angajatul a
	{
		// secventa de cautare a pozitiei de inserat pentru angajatul a
		if (a.cod < r->ang.cod) r->stanga = inserare_nod(r->stanga, a, flag_inserare);
		else
			if (a.cod > r->ang.cod) r->dreapta = inserare_nod(r->dreapta, a, flag_inserare);
			else
				*flag_inserare = 0; //inserarea nu are loc; cheie duplicata
		return r;
	}
	else
	{
		// pozitia de inserat este identificata (pozitie de NULL in arbore binar de cautare)
		struct NodArb* p = (struct NodArb*)malloc(sizeof(struct NodArb));
		p->stanga = NULL;
		p->dreapta = NULL;
		p->ang = a;

		*flag_inserare = 1;

		return p;
	}
}

void inordine(struct NodArb* r)
{
	if (r)
	{
		inordine(r->stanga);
		printf("\n%hu %s", r->ang.cod, r->ang.nume);
		inordine(r->dreapta);
	}
}

// inaltime arbore
// nr noduri frunza
// noduri de pe nivel specificat
// traversari preordine, postordine, pe niveluri
// dezalocare arbore
// stergere nod in arbore binar de cautare

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	char nume[64];
	struct Angajat fang;
	struct NodArb * root = NULL; // arbore binar de cautare empty

	fscanf(f, "%[^,],", nume);
	while (!feof(f))
	{
		fscanf(f, "%hu,%f\n", &fang.cod, &fang.salariu);

		fang.nume = malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		unsigned char flag;
		root = inserare_nod(root, fang, &flag);

		if (flag)
		{
			printf("\n Angajat cu cod %hu inserat in arbore binar de cautare", fang.cod);
		}
		else
		{
			printf("\n Angajat deja inserat cu codul %hu in arbore binar de cautare", fang.cod);
			free(fang.nume); // angajatul fang NU se mai insereaza in arbore binar de cautare
		}

		fscanf(f, "%[^,],", nume);
	}
	fclose(f);

	printf("\nArbore binar de cautare dupa operatia de creare/populare:");
	inordine(root);
}