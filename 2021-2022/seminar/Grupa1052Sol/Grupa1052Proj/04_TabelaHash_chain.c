#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define HASH_TABLE_SIZE 50

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

struct Nod* inserare_inceput(struct Nod* list, struct Angajat a)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->ang = a;
	nou->next = list;

	return nou;
}

struct Nod* stergere_nod(struct Nod* list, unsigned short int id)
{
	struct Nod* tmp = list;
	if (tmp)
	{
		if (tmp->ang.cod == id)
		{
			// stergerea primului nod in LS
			list = list->next;
			free(tmp->ang.nume);
			free(tmp);
		}
		else
		{
			while (tmp->next && tmp->next->ang.cod != id)
			{
				tmp = tmp->next;
			}

			if (tmp->next)
			{
				struct Nod* tmp2 = tmp->next;
				tmp->next = tmp2->next;

				free(tmp2->ang.nume);
				free(tmp2);
			}

		}
	}

	return list;
}

unsigned char calcul_hash(unsigned short int id, unsigned char size)
{
	return id % size;
}

void inserare_tabela_chain(struct Nod** ht, unsigned char size, struct Angajat a)
{
	unsigned char pos = calcul_hash(a.cod, size);

	ht[pos] = inserare_inceput(ht[pos], a);
}

struct Angajat* cautare_angajat(struct Nod** ht, unsigned char size, unsigned short int id_cautat)
{
	unsigned char pos = calcul_hash(id_cautat, size);

	struct Nod* tmp = ht[pos];
	while (tmp)
	{
		if (tmp->ang.cod == id_cautat)
			return &tmp->ang;
		tmp = tmp->next;
	}

	return NULL;
}

void stergere_angajat(struct Nod** ht, unsigned char size, unsigned short int id_cautat)
{
	unsigned char pos = calcul_hash(id_cautat, size);

	ht[pos] = stergere_nod(ht[pos], id_cautat);
}

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r");
	struct Angajat fang;
	char buffer[128];

	struct Nod* *HTable;
	HTable = (struct Nod**)malloc(HASH_TABLE_SIZE * sizeof(struct Nod*));
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // lista simpla i este empty


	fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia #1
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", buffer, &fang.salariu);

		fang.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fang.nume, buffer);

		inserare_tabela_chain(HTable, HASH_TABLE_SIZE, fang);

		fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia urmatoare
	}

	// tabela de dispersie se parseaza in intregime
	printf("\nTabela de dispersie dupa creare si populare:");
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (HTable[i]) // exista lista simpla pe offset i in vectorul HTable
		{
			printf("\nLista offset %d:", i);
			struct Nod* tmp = HTable[i];
			while (tmp)
			{
				printf("\n\t%hu %s", tmp->ang.cod, tmp->ang.nume);
				tmp = tmp->next;
			}
		}
	}

	struct Angajat* pang;
	pang = cautare_angajat(HTable, HASH_TABLE_SIZE, 2666);

	if (pang)
	{
		// exista angajat cu codul cautat
		printf("\nAngajat identificat: %hu %s", pang->cod, pang->nume);
	}
	else
		printf("\nAngajatul nu a fost identificat");

	stergere_angajat(HTable, HASH_TABLE_SIZE, 1900);
	// tabela de dispersie se parseaza in intregime
	printf("\nTabela de dispersie dupa stergere angajat pe baza de id (cheie de cautare):");
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (HTable[i]) // exista lista simpla pe offset i in vectorul HTable
		{
			printf("\nLista offset %d:", i);
			struct Nod* tmp = HTable[i];
			while (tmp)
			{
				printf("\n\t%hu %s", tmp->ang.cod, tmp->ang.nume);
				tmp = tmp->next;
			}
		}
	}

	// dezalocare tabela de dispersie
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
	{
		while (HTable[i]) // exista lista simpla pe offset i in vectorul HTable
		{
			stergere_angajat(HTable, HASH_TABLE_SIZE, HTable[i]->ang.cod);
		}
	}

	// tabela de dispersie se parseaza in intregime
	printf("\nTabela de dispersie dupa dezalocare:");
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (HTable[i]) // exista lista simpla pe offset i in vectorul HTable
		{
			printf("\nLista offset %d:", i);
			struct Nod* tmp = HTable[i];
			while (tmp)
			{
				printf("\n\t%hu %s", tmp->ang.cod, tmp->ang.nume);
				tmp = tmp->next;
			}
		}
	}
	free(HTable);
	HTable = NULL;


	fclose(f);
}