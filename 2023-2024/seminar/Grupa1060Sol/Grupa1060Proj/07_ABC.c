#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct User
{
	char* nume_cont;
	char* nume_user;
	unsigned char varsta;
	char deschis_la[11]; // 10 bytes pt data calendaristica + 1 byte pt terminator string (0x00)
};

typedef struct User User;

struct NodABC
{
	unsigned short int id_user;
	User u;
	struct NodABC *st, *dr;
};

typedef struct NodABC NodABC;

// inserare nod in arbore binar de cautare
// cheie de cautare: id_user
NodABC* inserare_user_ABC(NodABC* r, unsigned short int id, User usr)
{
	// TODO: implementare cu apel recursiv pentru cautare pozitie in arbore a noului nod

	return r;
}

int main()
{
	FILE* f = fopen("AccountsTree.txt", "r");
	NodABC* rad = NULL;

	char buffer[256];
	char sep[] = ";";

	while (fgets(buffer, sizeof(buffer), f))
	{
		char* token = NULL;
		User utilizator;
		unsigned short int id_user;
		token = strtok(buffer, sep); // token contine adresa de inceput in buffer pt id_user
		id_user = (unsigned short int)atoi(token);

		token = strtok(NULL, sep);
		utilizator.nume_cont = (char*)malloc(strlen(token) + 1);
		strcpy(utilizator.nume_cont, token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt nume_user
		utilizator.nume_user = (char*)malloc(strlen(token) + 1);
		strcpy(utilizator.nume_user, token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt varsta
		utilizator.varsta = (unsigned char)atoi(token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt deschis_la
		strcpy(utilizator.deschis_la, token);

		// inserare user in arbore binar de cautare
		rad = inserare_user_ABC(rad, id_user, utilizator);
	}

	fclose(f);

	// parsare arbore binar de cautare (inordine)

	// determinare numar de noduri frunza

	// dezalocare arbore binar de cautare

	return 0;
}