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

void inserare_user_htable_v2(Nod** ht, unsigned char ht_size, User usr)
{
	// 1. determinare pozitie lista simpla in care se efectueaza inserarea
	unsigned char poz = functie_hash(usr.nume_user, ht_size);

	// 2. inserare utilizator usr in lista simpla ht[poz]
	ht[poz] = inserare_sfarsit(ht[poz], usr);
}

User* cauta_utilizator_htable(Nod** ht, unsigned char ht_size, char* cheie_cautare)
{
	// 1. determinare hash (offset lista simpla in care ar trebui sa gasesc date pentru cheie_cautare)
	unsigned char poz = functie_hash(cheie_cautare, ht_size);

	// 2. parsare nod cu nod lista simpla ht[poz]; returnare adresa heap unde structura este stocata in lista
	Nod* temp = ht[poz];
	while (temp != NULL)
	{
		if (strcmp(cheie_cautare, temp->u.nume_cont) == 0)
		{
			return &temp->u; // utilizator identificat in tabela hash; nu exista nodul 2 cu acelasi nume_cont
		}

		temp = temp->next;
	}
	
	return NULL; // utilizatorul nu exista in tabela de dispersie
}

User** cauta_utilizator_htable_v2(Nod** ht, unsigned char ht_size, char* cheie_cautare, 
									unsigned char* nr_users)
{
	// 1. determinare nr conturi cu acelasi nume_user

	// 2. alocare memorie heap pentru vectorul de User* DACA nr de conturi nu este 0

	// 3. cautare in extenso a conturilor si salvare adrese de conturi in vectorul alocat la p2.

	// 4. return vector alocat sau NULL
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
	User* usr_gasit = cauta_utilizator_htable(HTable, HASH_TABLE_SIZE, "popes_9");
	if (usr_gasit != NULL)
	{
		printf("Utilizator identificat in tabela de dispersie: %s %s\n",
			usr_gasit->nume_cont, usr_gasit->nume_user);
	}
	else
	{
		printf("Utilizatorul cautat nu exista in tabela de dispersie!\n");
	}

	// dezalocare tabela de dispersie
	// 1. dezalocare liste simple din tabela de dispersie
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
	// 2. dezalocare vector suport pentru tabela de dispersie
	free(HTable);
	HTable = NULL;
	usr_gasit = NULL; // ca urmare a dezalocarii tabelei, datele pointate nu mai exista

	// creare tabela hash gestionata prin HTable unde cheie de cautare este nume_user
	// re-parsare fisier cu date de intrare
	fseek(f, 0, SEEK_SET);

	HTable = (Nod**)malloc(HASH_TABLE_SIZE * sizeof(Nod*));
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // HTable[i] acceseaza pointerul aferent listei i in tabela de dispersie HTable

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
		inserare_user_htable_v2(HTable, HASH_TABLE_SIZE, utilizator);
	}

	// apel functie de cautare conturi User pentru cheie nume_user specificata in lista de parametri
	unsigned char nr_users = 0;
	User ** v_usr_gasiti = cauta_utilizator_htable_v2(HTable, HASH_TABLE_SIZE, "Ionescu Georgica", &nr_users);


	// dezalocare tabela de dispersie #2 (cheie: nume_user)

	// dezalocare vector de pointeri

	fclose(f);
	return 0;
}