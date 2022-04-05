#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct Nod
{
	struct Angajat ang;
	struct Nod* next; // adresa structura similara in abordare secventiala/liniara
};

struct Nod* inserare_sfarsit(struct Nod* list, struct Angajat a)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->ang = a;
	nou->next = NULL;

	if (list == NULL)
		return nou;
	else
	{
		struct Nod* t = list;

		while (t->next != NULL)
			t = t->next;
		t->next = nou;
	}
	return list;
}

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	struct Angajat fang;
	char nume[64];

	struct Nod* pList = NULL;

	fscanf(f, "%hu,", &fang.cod);
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", nume, &fang.salariu);

		fang.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		pList = inserare_sfarsit(pList, fang);

		fscanf(f, "%hu,", &fang.cod);
	}


	// testare continut lista simpla
	// inserare inceput/interior
	// stergere inceput/sfarsit/interior

	// export angajati in vector

	// dezalocare structura lista simpla

	fclose(f);
}