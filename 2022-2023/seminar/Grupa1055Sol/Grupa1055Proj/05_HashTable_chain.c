#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define HASH_TABLE_SIZE 50

enum UM { RON, EUR, USD };

struct ContBancar
{
	char iban[25];
	char* titular;
	float sold;
	enum UM moneda;
	char activ; // boolean pentru cont activ; true - activ
};

struct NodCB
{
	struct ContBancar cb;
	struct NodCB* next;
};

// functie hash pentru determinar pozitie in tabela conform cheie
unsigned int functie_hash(char* cheie, unsigned int size_ht)
{
	unsigned int suma = 0;
	for (unsigned int i = 0; i < strlen(cheie); i++)
		suma += (unsigned char)cheie[i];

	suma /= strlen(cheie); // media codului ASCII per simbol => tabela nu tb sa fie mai mare de 256 elemente
	
	return suma % size_ht;
}

// inserare nod in lista simpla de conturi bancare (pe prima pozitie)
struct NodCB* inserare_inceput(struct NodCB* p, struct ContBancar contb)
{
	struct NodCB* nou = (struct NodCB*)malloc(sizeof(struct NodCB));

	nou->cb = contb;
	nou->next = p;

	return nou;
}

// inserare cont bancar in tabela de dispersie
// [in] ht - tabela de dispersie cu cheia IBAN
// [in] size_ht - dimensiunea tabelei de dispersie ht
// [in] contb - datele contului bancar care se insereaza in tabela de dispersie
// [out] pozitia listei in tabela de dispersie ht unde se insereaza contul bancar contb
unsigned int inserare_ht_chaining(struct NodCB** ht, unsigned int size_ht, struct ContBancar contb)
{
	// pasul 1: determinare pozitie in tabela de dispersie unde contb trebuie inserat
	unsigned int pozitie = functie_hash(contb.iban, size_ht);

	// pasul 2: inserarea in lista simple ht[pozitie]
	ht[pozitie] = inserare_inceput(ht[pozitie], contb);

	return pozitie;
}

// cautare cont bancar in tabela de dispersie
struct ContBancar* cautare_ht_chaining(struct NodCB** ht, unsigned int size_ht, char* cheie)
{
	unsigned int pozitie = functie_hash(cheie, size_ht);

	if (ht[pozitie] != NULL)
	{
		// exista lista cu noduri pe pozitie
		struct NodCB* temp = ht[pozitie];
		while (temp)
		{
			if (strcmp(cheie, temp->cb.iban) == 0)
			{
				// contul bancar este identificat in lista 
				return &(temp->cb);
			}
			temp = temp->next;
		}
	}

	return NULL; // nu a fost gasit contul bancar cu "cheie"
}

int main()
{
	FILE* f;
	f = fopen("conturi.txt", "r");

	char buffer[BUFFER_SIZE], seps[] = ",\n";

	struct NodCB** HTable = NULL; // variabila de acces la tabela de dispersie
	// alocare vector suport tabela hash
	HTable = (struct NodCB**)malloc(HASH_TABLE_SIZE * sizeof(struct NodCB*));
	// initilizare elemente vector (liste simple -> empty)
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // lista i este pointer NULL, lista i este empty (0 noduri)

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		struct ContBancar cb;
		char* token = strtok(buffer, seps);
		strcpy(cb.iban, token);

		token = strtok(NULL, seps);
		cb.titular = (char*)malloc(strlen(token) + 1);
		strcpy(cb.titular, token);

		token = strtok(NULL, seps);
		cb.sold = atof(token);

		token = strtok(NULL, seps);
		if (strcmp(token, "RON") == 0)
			cb.moneda = RON;
		if (strcmp(token, "EUR") == 0)
			cb.moneda = EUR;
		if (strcmp(token, "USD") == 0)
			cb.moneda = USD;

		token = strtok(NULL, seps);
		if (strcmp(token, "true") == 0)
			cb.activ = 1;
		else
			if (strcmp(token, "false") == 0)
				cb.activ = 0;

		// inserare in tabela hash cont bancar cb preluat din fisier
		unsigned int poz = inserare_ht_chaining(HTable, HASH_TABLE_SIZE, cb);
		printf("Inserare in lista %u cont bancar %s\n", poz, cb.iban);
	}

	// validare continut tabela de dispersie
	printf("Tabela de dispersie dupa creare:\n");
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (HTable[i] != NULL)
		{
			// exista lista de conturi bancare pe pozitia i
			printf("Lista %u de conturi bancare:\n", i);
			struct NodCB* temp = HTable[i];
			while (temp)
			{
				printf("   %s, %s\n", temp->cb.iban, temp->cb.titular);

				temp = temp->next;
			}
		}
	}

	// cautare cont bancar in tabela de dispersie
	struct ContBancar* pcb;
	pcb = cautare_ht_chaining(HTable, HASH_TABLE_SIZE, "RO04BTRL0000XXXX12345601");
	if (pcb != NULL)
	{
		printf("Cont bancar identificat: %s, %s\n", pcb->iban, pcb->titular);
	}
	else
	{
		printf("Contul bancar nu a fost gasit in tabela.\n");
	}


	// stergere cont bancar pe baza de cheie iban

	// dezalocare tabela de dispersie

	fclose(f);
}