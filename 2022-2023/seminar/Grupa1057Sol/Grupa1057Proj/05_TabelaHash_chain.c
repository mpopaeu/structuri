#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 30
#define BUFFER_SIZE 256

struct ContBancar
{
	char iban[25];
	char* titular;
	char moneda[4];
	float sold;
	unsigned int nr_carduri;
};

struct Nod
{
	struct ContBancar cb;
	struct Nod* next;
};


struct Nod* inserare_inceputLS(struct Nod* p, struct ContBancar cont_bancar)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->cb = cont_bancar;
	nou->next = p;

	return nou;
}

// functie hash
// [in] str - string pentru care se calculeaza functia hash
// [in] size - numar de elemente din vectorul suport pentru tabela de dispersie
// [out] pozitia calculata pentru tabela de dispersie cu size elemente
unsigned int  functie_hash(char* str, unsigned int size)
{
	unsigned int suma = 0;
	for (unsigned int i = 0; i < strlen(str); i++)
		suma += str[i];

	return suma % size;
}

// functie inserare in tabela de dispersie
// [in] ht - tabela de dispersie in care se realizeaza inserarea
// [in] size - numarul de elemente din ht
// [in] cont_bancar - structura cu date cont bancar care se insereaza in tabela de dispersie
// [out] pozitia calculata de functia hash: [0, ..., size-1]
unsigned int inserare_ht_chaining(struct Nod** ht, unsigned int size, struct ContBancar cont_bancar)
{
	unsigned int poz_tabela = functie_hash(cont_bancar.iban, size); // iban este cheie in tabela de dispersie

	// inserare cont_bancar in lista ht[poz_tabela]
	ht[poz_tabela] = inserare_inceputLS(ht[poz_tabela], cont_bancar);

	return poz_tabela;
}


struct ContBancar cautare_cb_htable(struct Nod** ht, unsigned int size, char* cheie)
{
	unsigned poz = functie_hash(cheie, size);

	if (ht[poz] != NULL)
	{
		// lista poz este non-empty
		struct Nod* temp = ht[poz]; // acces direct la lista poz
		while (temp != NULL)
		{
			if (strcmp(temp->cb.iban, cheie) == 0)
			{
				return temp->cb; // cont bancar identificat pe baza de iban (unic in colectia de date)
			}

			temp = temp->next; // acces secvential
		}
	}

	// contul bancar nu a fost identificat in tabela de dispersie
	struct ContBancar cont_bancar;
	cont_bancar.sold = -1; // flag pentru cont bancar fake
	return cont_bancar;
}


struct ContBancar stergere_cb_htable(struct Nod** ht, unsigned int size, char* cheie)
{
	unsigned poz = functie_hash(cheie, size);
	struct ContBancar cont_bancar;

	if (ht[poz] != NULL)
	{
		// lista poz este non-empty
		struct Nod* temp = ht[poz]; // acces direct la lista poz
		struct Nod* prec = NULL;
		while (temp != NULL)
		{
			if (strcmp(temp->cb.iban, cheie) == 0)
			{
				// stergere nod temp din lista simpla ht[poz]
				if (prec != NULL)
				{
					prec->next = temp->next;
				}
				else
				{
					ht[poz] = temp->next; // se sterge primul nod
				}

				cont_bancar = temp->cb;
				free(temp);
				
				return cont_bancar;
			}

			prec = temp; // prec este nodul predecesor lui temp
			temp = temp->next; // acces secvential
		}
	}


	// contul bancar nu a fost identificat in tabela de dispersie
	cont_bancar.sold = -1; // flag pentru cont bancar fake
	return cont_bancar;
}

int main()
{

	struct ContBancar cb;
	FILE* f;

	f = fopen("Conturi.txt", "r");

	char buffer[BUFFER_SIZE], seps[] = ",\n";

	struct Nod** HTable = NULL; // variabila pentru gestionarea vectorului suport pentru tabela hash
	
	// alocare vector in mem heap
	HTable = (struct Nod**)malloc(HASH_TABLE_SIZE * sizeof(struct Nod*));
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // initializare liste ca fiind empty

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		char* token;
		token = strtok(buffer, seps);
		strcpy(cb.iban, token);

		token = strtok(NULL, seps);
		cb.titular = (char*)malloc(strlen(token) + 1); // +1 pentru terminat de string, adica byte 0x00
		strcpy(cb.titular, token);

		token = strtok(NULL, seps);
		strcpy(cb.moneda, token);

		token = strtok(NULL, seps);
		cb.sold = atof(token);

		token = strtok(NULL, seps);
		cb.nr_carduri = atoi(token);

		// inserare cont bancar cb in tabela hash cu chaining
		unsigned int poz = inserare_ht_chaining(HTable, HASH_TABLE_SIZE, cb);
		printf("COnt bancar %s inserat in lista simpla %u\n", cb.iban, poz);
	}
	fclose(f);

	printf("Tabela de dispersie cu chaining dupa creare:\n");
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (HTable[i] != NULL)
		{
			// lista i nu este empty
			printf("Lista %u:\n", i);
			// traversare secventiala lista i
			struct Nod* temp = HTable[i];
			while (temp != NULL)
			{
				printf("    %s %s\n", temp->cb.iban, temp->cb.titular);
				temp = temp->next;
			}
		}
	}

	// cautare cont bancar in tabela de dispersie pe baza de cheie
	cb = cautare_cb_htable(HTable, HASH_TABLE_SIZE, "RO14RNCB1994567890101011");
	if (cb.sold != -1)
	{
		printf("Cont bancar identificat: %s --> %s\n", cb.iban, cb.titular);
	}
	else
	{
		printf("Cont bancar inexistent in tabela de dispersie pentur cheia de cautare folosita mai sus.");
	}

	// stergere element pe baza de cheie in tabela de dispersie

	// dezalocare structura tabela de dispersie
}