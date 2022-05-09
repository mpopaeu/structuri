
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

#define HASH_TABLE_SIZE 100

// [in] list - adresa primului nod in care se efectueaza inserare la sfarsit
// [in] new_ang - date angajat care se insereaza la sfarsitul listei
// [return] - adresa (eventual noua la inserare nod in lista empty) primului nod din lista simpla
struct Nod* inserare(struct Nod* list, struct Angajat new_ang)
{
	struct Nod* nou;
	nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->ang = new_ang;
	nou->next = NULL; // nodul nou va fi ultimul din lista

	if (list == NULL) // lista contine 0 noduri
		return nou;
	else
	{
		struct Nod* t = list;
		while (t->next) // parsare lista simpla pana pe ultimul nod (t->next == NULL)
			t = t->next;
		t->next = nou; // "legarea" nodului nou la lista existenta
	}
	return list;
}

unsigned char hash_function(unsigned short int key, unsigned char ht_size)
{
	return key % ht_size;
}

void inserare_hashtable_chain(struct Nod** ht, unsigned char ht_size, struct Angajat a)
{
	unsigned char poz = hash_function(a.cod, ht_size);

	ht[poz] = inserare(ht[poz], a);
}

// cautare angajat dupa cheie de cautare
// stergere angajat dupa cheie de cautare

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	char nume[64];
	struct Angajat fang;
	struct Nod** HTable;

	// alocare vector suport pentru tabela de dispersie cu chaining
	HTable = (struct Nod**)malloc(HASH_TABLE_SIZE * sizeof(struct Nod*));
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // toate listele sunt initializate ca fiind empty

	fscanf(f, "%[^,],", nume);
	while (!feof(f))
	{
		fscanf(f, "%hu,%f\n", &fang.cod, &fang.salariu);

		fang.nume = malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		inserare_hashtable_chain(HTable, HASH_TABLE_SIZE, fang);
		fscanf(f, "%[^,],", nume);
	}
	fclose(f);

	printf("Tabela de dispersie dupa creare:\n");
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (HTable[i])
		{
			printf("\nLista %u:", i);
			struct Nod* tmp = HTable[i];
			while (tmp)
			{
				printf("\n\t %hu %s", tmp->ang.cod, tmp->ang.nume);
				tmp = tmp->next;
			}
		}
	}
}