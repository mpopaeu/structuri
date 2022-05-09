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

#define HASH_TABLE_SIZE 100

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

unsigned char hash_function(unsigned short int key, unsigned char ht_size)
{
	return key % ht_size;
}

void inserare_tabelahash(struct Nod** ht, unsigned char ht_size, struct Angajat a)
{
	unsigned char poz = hash_function(a.cod, HASH_TABLE_SIZE);

	ht[poz] = inserare_sfarsit(ht[poz], a);
}

// cautare angajata pentru cheie de cautare
// stergere angajat pentru cheie de cautare specificata

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	struct Angajat fang;
	char nume[64];

	struct Nod** HTable;
	HTable = (struct Nod**)malloc(HASH_TABLE_SIZE * sizeof(struct Nod*));

	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // toate listele sunt marcate ca fiind empty

	fscanf(f, "%hu,", &fang.cod);
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", nume, &fang.salariu);

		fang.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		inserare_tabelahash(HTable, HASH_TABLE_SIZE, fang);

		fscanf(f, "%hu,", &fang.cod);
	}

	fclose(f);

	printf("\nTabela de dispersie dupa creare si populare:");
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (HTable[i])
		{

			printf("\nLista de coliziuni %u", i);
			struct Nod* tmp = HTable[i];
			while (tmp)
			{
				printf("\n\t %hu %s", tmp->ang.cod, tmp->ang.nume);

				tmp = tmp->next;
			}
		}
	}
}