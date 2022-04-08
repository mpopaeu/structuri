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
	struct Nod* next;
};

// inserare nod inceput/sfarsit/interior
// stergere nod inceput/sfarsit/interior

// parsare lista
// dezalocare lista simpla

// copiere angajati in vector

// inserare nod la inceput
struct Nod* inserare_inceput(struct Nod* list, struct Angajat a)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->ang = a;
	nou->next = list;

	return nou;
}

void main()
{
	FILE* f;
	struct Angajat tmp;
	struct Nod* pList = NULL;

	f = fopen("Angajati.txt", "r");
	fscanf(f, "%u,", &tmp.cod);

	while (!feof(f))
	{
		char nn[64];
		fscanf(f, "%[^,],%f\n", nn, &tmp.salariu);

		tmp.nume = malloc(sizeof(char) * (strlen(nn) + 1));
		strcpy(tmp.nume, nn);

		// inserare angajat in lista simpla
		pList = inserare_inceput(pList, tmp);

		fscanf(f, "%u,", &tmp.cod);
	}

	tmp.nume = NULL;

	fclose(f);
}