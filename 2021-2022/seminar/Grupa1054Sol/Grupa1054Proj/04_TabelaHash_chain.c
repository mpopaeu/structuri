
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
struct Angajat* cauta_angajat_cheie(struct Nod** ht, unsigned char ht_size, unsigned short int key)
{
	unsigned char poz = hash_function(key, ht_size);

	struct Nod* tmp = ht[poz]; // adresa primului nod din lista simpla ht[poz]
	while (tmp)
	{
		if (key == tmp->ang.cod)
			return &tmp->ang;

		tmp = tmp->next;
	}

	return NULL;
}

// stergere angajat dupa cheie de cautare
void sterge_angajat_cheie(struct Nod** ht, unsigned char ht_size, unsigned short int key)
{
	unsigned char poz = hash_function(key, ht_size);

	if (ht[poz]) // exista cel putin 1 nod in lista ht[poz]
	{
		struct Nod* tmp = ht[poz];

		if (tmp->ang.cod == key)
		{
			// angajatul de sters este primul nod din lista
			ht[poz] = tmp->next;

			free(tmp->ang.nume);
			free(tmp);
		}
		else
		{
			while (tmp->next)
			{
				if (tmp->next->ang.cod == key)
				{
					struct Nod* q = tmp->next;

					tmp->next = q->next;

					free(q->ang.nume);
					free(q);

					return; // oprire executie functie deoarece exista un singur angajat cu codul cautat
				}

				tmp = tmp->next;
			}
		}
	}
}

// cautare angajat(i) dupa nume
// stergere angajat(i) dupa interval salarii

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

	struct Angajat* pang;
	pang = cauta_angajat_cheie(HTable, HASH_TABLE_SIZE, 1789);

	printf("\n\nOperatia de cautare in tabela de dispersie, folosind cheia de cautare");
	if (pang)
	{
		printf("\nAngaja identificat in tabela de dispersie: %hu %s", pang->cod, pang->nume);
	}
	else
		printf("\nAngajatul cautat nu este identificat in tabela de dispersie.");
	
	// stergerea unui angajat pe baza de cheie de cautare (cod angajat)
	sterge_angajat_cheie(HTable, HASH_TABLE_SIZE, 7889);
	printf("\n\nTabela de dispersie dupa stergere angajat:\n");
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