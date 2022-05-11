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
struct Angajat* cautare_angajat(struct Nod** ht, unsigned char ht_size, unsigned short int key)
{
	unsigned short int poz = hash_function(key, HASH_TABLE_SIZE);

	if (ht[poz])
	{
		struct Nod* tmp = ht[poz];
		while (tmp)
		{
			if (tmp->ang.cod == key)
				return &tmp->ang;

			tmp = tmp->next;
		}
	}

	return NULL;
}

// stergere angajat pentru cheie de cautare specificata
void stergere_angajat(struct Nod** ht, unsigned char ht_size, unsigned short int key)
{
	unsigned short int poz = hash_function(key, HASH_TABLE_SIZE);

	if (ht[poz])
	{
		struct Nod* tmp = ht[poz];

		if (tmp->ang.cod == key)
		{
			// stergere primul nod ind lista simpla ht[poz]
			ht[poz] = tmp->next;

			free(tmp->ang.nume);
			free(tmp);
		}
		else
		{
			// angajatul de sters nu este plasat in primul nod din lista simpla ht[poz]
			while (tmp->next)
			{
				if (tmp->next->ang.cod == key)
				{
					// angajat de sters identificat
					struct Nod* aux = tmp->next;
					tmp->next = aux->next;

					free(aux->ang.nume);
					free(aux);
					return;
				}
				tmp = tmp->next;
			}
		}
	}
}


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

	struct Angajat* pang;
	pang = cautare_angajat(HTable, HASH_TABLE_SIZE, 1099);
	if (pang)
	{
		printf("\n\nAngajat identificat: %hu %s", pang->cod, pang->nume);
	}
	else
	{
		// angajatul nu este in tabela hash
		printf("\n\nAngajatul nu a fost identificat.");
	}

	stergere_angajat(HTable, HASH_TABLE_SIZE, 2900);
	printf("\nTabela de dispersie dupa stergere angajat:");
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