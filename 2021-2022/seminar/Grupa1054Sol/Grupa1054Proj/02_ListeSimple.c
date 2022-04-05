
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// creare lista simpla cu angajati
// date preluate din fisier

struct Angajat
{
	char* nume;
	unsigned short int cod;
	float salariu;
};

struct Nod
{
	struct Angajat ang;
	struct Nod* next;
};

#define LINE_SIZE 128

struct Nod* inserare(struct Nod* list, struct Angajat new_ang)
{
	struct Nod* nou;
	nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->ang = new_ang;
	nou->next = NULL;

	if (list == NULL)
		return nou;
	else
	{
		struct Nod* t = list;
		while (t->next)
			t = t->next;
		t->next = nou;
	}
	return list;
}

// inserare nod la inceput
// inserare nod in interior (definiti criteriul)
// stergere nod inceput/sfarsit/interior (definiti criteriul)

// export angajati in vector

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	char buffer_linie[LINE_SIZE], nume[64];
	struct Angajat fang;
	struct Nod* pList = NULL;

	// while (fgets(buffer_linie, LINE_SIZE, f))
	fscanf(f, "%[^,],", nume, &fang.cod, &fang.salariu);
	while (!feof(f))
	{
		fscanf(f, "%hu,%f\n", &fang.cod, &fang.salariu);

		fang.nume = malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		pList = inserare(pList, fang);
		fscanf(f, "%[^,],", nume);		
	}

	printf("\nContinut lista simpla de angajati:\n");
	struct Nod* tmp = pList;
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}

	fclose(f);
}