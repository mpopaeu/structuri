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

struct NodD
{
	User * puser;
	struct NodD* next, *prev;
};

typedef struct NodD NodD;

struct ListaDubla
{
	NodD* p, * u;
};

typedef struct ListaDubla ListaDubla;

ListaDubla inserare_sfarsit(ListaDubla lista, User *pusr)
{
	NodD* nou = (NodD*)malloc(sizeof(NodD));
	nou->next = NULL; // obligatoriu pentru ca nou devine ultimul nod in lista dubla
	nou->prev = lista.u;
	nou->puser = pusr;

	if (lista.p == NULL)
	{
		// lusta dubla este empty
		lista.p = lista.u = nou;
	}
	else
	{
		// exista cel putin 1 nod in lista dubla
		lista.u->next = nou;
		lista.u = nou;
	}

	return lista;
}

// stergere noduri din lista dubla care au fost deschise la aceeasi data calendaristica
ListaDubla stergere_nod_data(ListaDubla lista, char * data_deschidere)
{


	return lista;
}

// interschimb noduri adiacente; primul nod identificat pe baza nume_cont din structura User
ListaDubla interschimb_adiacente(ListaDubla lista, char* cont)
{

}

// modificare nume_user pe baza nume_cont din structura User
void modifica_nume_user(ListaDubla lista, char* cont)
{

}

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	ListaDubla listaD;
	listaD.p = listaD.u = NULL;
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

		User* pusr = (User*)malloc(sizeof(User)); // alocare spatiu in mem heap pt stocare date User
		*pusr = utilizator;

		// inserare nod in lista dubla
		listaD = inserare_sfarsit(listaD, pusr);
	}

	printf("Lista dubla dupa creare (prim->ultim):\n");
	NodD* tmp = listaD.p;
	while (tmp != NULL)
	{
		printf("%s %s\n", tmp->puser->nume_user, tmp->puser->deschis_la);
		tmp = tmp->next;
	}
	printf("Lista dubla dupa creare (ultim->prim):\n");
	tmp = listaD.u;
	while (tmp != NULL)
	{
		printf("%s %s\n", tmp->puser->nume_user, tmp->puser->deschis_la);
		tmp = tmp->prev;
	}


	// dezalocare lista dubla
	while (listaD.p != NULL)
	{
		tmp = listaD.p;
		listaD.p = listaD.p->next; // tmp este izolat fata de lista dubla; adresa primului nod 
								   // este modificata (al doilea nod in lista dubla)
		if(listaD.p != NULL)
			listaD.p->prev = NULL;  // predecesorul se actualizeaza pentru nou inceput de lista ne-null
		else
		{
			// se sterge ultimul nod din lista dubla; se actualizeaza adresa ultimului nod din lista dubla
			listaD.u = NULL;
		}

		free(tmp->puser->nume_cont); // dezalocare nume cont din User
		free(tmp->puser->nume_user); // dezalocare nume user din User
		free(tmp->puser);			 // dezalocare User din NodD
		free(tmp);					 // dezalocare NodD

	}

	printf("Lista dubla dupa dezalocare (prim->ultim):\n");
	tmp = listaD.p;
	while (tmp != NULL)
	{
		printf("%s %s\n", tmp->puser->nume_user, tmp->puser->deschis_la);
		tmp = tmp->next;
	}
	printf("Lista dubla dupa dezalocare (ultim->prim):\n");
	tmp = listaD.u;
	while (tmp != NULL)
	{
		printf("%s %s\n", tmp->puser->nume_user, tmp->puser->deschis_la);
		tmp = tmp->prev;
	}

	fclose(f);
	return 0;
}