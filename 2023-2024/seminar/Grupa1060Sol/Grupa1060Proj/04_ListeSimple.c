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

struct Nod
{
	User u;
	struct Nod* next;
};

typedef struct Nod Nod;

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

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	Nod* lista = NULL;
	char buffer[256];

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

		// inserare utilizator la sfarsitul listei simple
		lista = inserare_sfarsit(lista, utilizator);
	}

	printf("Lista simpla dupa creare:\n");
	Nod* tmp = lista;
	while (tmp != NULL)
	{
		printf("%s %s\n", tmp->u.nume_user, tmp->u.deschis_la);
		tmp = tmp->next;
	}

	// dezalocare lista simpla
	while (lista != NULL)
	{
		tmp = lista;
		lista = lista->next; // tmp este izolat fata de lista

		free(tmp->u.nume_cont);
		free(tmp->u.nume_user);
		free(tmp);

	}

	printf("Lista simpla dupa dezalocare:\n");
	tmp = lista;
	while (tmp != NULL)
	{
		printf("%s %s\n", tmp->u.nume_user, tmp->u.deschis_la);
		tmp = tmp->next;
	}

	// stergere nod in lista simpla pe baza de criteriu relativ la User

	// interschimbare noduri adiacente in lista simpla prin modificarea adreselor de legatura (de tip next)

	fclose(f);
	return 0;
}