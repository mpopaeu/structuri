#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int id;
	char* nume;
	float salariu;
};

struct Nod
{
	struct Angajat ang;
	struct Nod* next;
};

// operatii de baza cu liste simple

// inserare nod la inceput

// [in] pList - lista in care se face inserarea la inceput
// [in] ang - date Angajat care se insereaza in lista simpla
// [return] adresa noului nod inceput de lista
struct Nod* inserare_inceput(struct Nod* pList, struct Angajat new_ang)
{
	struct Nod* new_node;
	new_node = (struct Nod*)malloc(sizeof(struct Nod));

	new_node->ang = new_ang;
	new_node->next = pList;

	return new_node;
}

// inserare nod la sfarsit
// inserare nod interior

// stergere nod la inceput
// stergere nod la sfarsit
// stergere nod interior

// parsare lista simpla

// export angajati in vector

void main()
{
	FILE* f;
	struct Angajat tmp;
	struct Nod* pList = NULL;

	f = fopen("Angajati.txt", "r");

	fscanf(f, "%hu,", &tmp.id);
	while (!feof(f))
	{
		char nn[64];
		fscanf(f, "%[^,],%f\n", nn, &tmp.salariu);

		tmp.nume = (char*)malloc(sizeof(char) * (strlen(nn) + 1));
		strcpy(tmp.nume, nn);

		// inserare tmp in lista simpla
		pList = inserare_inceput(pList, tmp);

		fscanf(f, "%hu,", &tmp.id);
	}

	tmp.nume = NULL;

	struct Nod* t = pList;

	while (t)
	{
		printf("\nId angajat = %u, nume = %s", t->ang.id, t->ang.nume);
		t = t->next;
	}


	// dezalocare lista simpla
	while (pList)
	{
		free(pList->ang.nume);

		t = pList;
		pList = pList->next;

		free(t);
	}

	fclose(f);
}