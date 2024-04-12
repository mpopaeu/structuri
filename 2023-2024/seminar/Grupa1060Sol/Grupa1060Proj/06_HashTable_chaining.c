#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 100

struct User
{
	char* nume_cont;
	char* nume_user;
	unsigned char varsta;
	char deschis_la[11]; // 10 bytes pt data calendaristica + 1 byte pt terminator string (0x00)
};

typedef struct User User;

struct Nod
{
	User u;
	struct Nod* next;
};

typedef struct Nod Nod;

// inserare la sfarsit in lista simpla
Nod* inserare_sfarsit(Nod* p, User usr)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->next = NULL; // obligatoriu pentru ca nou devine ultimul nod in lista simpla
	nou->u = usr; // ?!

	if (p == NULL)
		return nou;

	Nod* t = p;
	while (t->next != NULL)
		t = t->next;
	t->next = nou;

	return p;
}

// cheie - cheia de cautare in tabela de dispersie
// ht_size - nr de elemente (dimensiune) vector suport pentru tabela de dispersie
unsigned char functie_hash(char* cheie, unsigned char ht_size)
{
	unsigned int suma = cheie[0] * 31;
	for (unsigned char i = 1; i < strlen(cheie); i++)
	{
		suma += cheie[i];
	}

	return (unsigned char)(suma % ht_size);
}

void inserare_user_htable(Nod** ht, unsigned char ht_size, User usr)
{
	// 1. determinare pozitie lista simpla in care se efectueaza inserarea
	unsigned char poz = functie_hash(usr.nume_cont, ht_size);

	// 2. inserare utilizator usr in lista simpla ht[poz]
	ht[poz] = inserare_sfarsit(ht[poz], usr);
}

User cauta_utilizator_htable(Nod** ht, unsigned char ht_size, char* cheie_cautare)
{
	User usr;

	//

	return usr;
}

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	Nod* *HTable = NULL;
	char buffer[256];

	HTable = (Nod**)malloc(HASH_TABLE_SIZE * sizeof(Nod*));
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // HTable[i] acceseaza pointerul aferent listei i in tabela de dispersie HTable

	char sep[] = ";";

	while (fgets(buffer, sizeof(buffer), f))
	{
		char* token = NULL;
		User utilizator;
		token = strtok(buffer, sep); // token contine adresa de inceput in buffer pt nume_cont
		utilizator.nume_cont = (char*)malloc(strlen(token) + 1);
		strcpy(utilizator.nume_cont, token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt nume_user
		utilizator.nume_user = (char*)malloc(strlen(token) + 1);
		strcpy(utilizator.nume_user, token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt varsta
		utilizator.varsta = (unsigned char)atoi(token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt deschis_la
		strcpy(utilizator.deschis_la, token);

		// inserare user in tabela de dispersie
		inserare_user_htable(HTable, HASH_TABLE_SIZE, utilizator);
	}

	// cautare cont utilizator pe baza de cheie in tabela de dispersie cu chaining
	User usr_gasit = cauta_utilizator_htable(HTable, HASH_TABLE_SIZE, "popes_9");

	// dezalocare tabela de dispersie
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
	{
		while (HTable[i] != NULL)
		{
			// lista HTable[i] contine cel putin 1 nod care trebuie dezalocat(e)
			Nod* temp = HTable[i];
			HTable[i] = HTable[i]->next;

			free(temp->u.nume_cont); // dezalocare string nume_cont
			free(temp->u.nume_user); // dezalocare string nume_user
			free(temp);				 // dezalocare nod
		}
	}

	fclose(f);
	return 0;
}