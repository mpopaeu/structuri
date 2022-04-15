#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct NodD
{
	struct Angajat ang;
	struct NodD *prev, *next;
};

struct ListaDubla
{
	struct NodD* prim, * ultim;
};

// inserare nod la inceput in lista dubla

struct ListaDubla inserare_inceput(struct ListaDubla list, struct Angajat a)
{
	struct NodD* nou = (struct NodD*)malloc(sizeof(struct NodD));
	nou->ang = a;
	nou->prev = NULL;
	nou->next = list.prim;

	if (list.prim == NULL)
	{
		list.ultim = nou;
	}
	else
	{
		list.prim->prev = nou;
	}
	list.prim = nou;

	return list;
}

void main()
{
	struct ListaDubla listD;
	listD.prim = NULL; // adresa primului nod
	listD.ultim = NULL; // adresa ultimului nod

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

		// inserare angajat in lista simpla
		listD = inserare_inceput(listD, tmp);

		fscanf(f, "%hu,", &tmp.cod);
	}

	// operatiile de la liste simple translatate pe liste duble
}