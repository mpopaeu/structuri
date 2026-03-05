#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Client
{
	unsigned int id;
	char* denumire;
	unsigned char tip;
	char ultima_comanda[11]; // 10 + 1; +1 pentru spatiu necesar terminatorului de string (byte 0x00)
	float valoare_totala_comenzi;
};

typedef struct Client Client;

struct Nod {
	Client cl;
	struct Nod* next; // adresa nodului succesor pentru nod curent
};

typedef struct Nod Nod;

Nod* inserareNod(Nod* p, Client client)
{
	Nod* nou = malloc(sizeof(Nod));

	nou->cl = client;
	nou->next = p;
	
	return nou;
}

void traversare(Nod* p)
{
	Nod* t = p;
	while (t)
	{
		printf("id client = %d\n", t->cl.id);

		t = t->next;
	}
}

int main()
{
	Nod* prim = NULL;
	FILE* f = NULL;

	f = fopen("Clienti.txt", "r");

	char buffer[256];
	char sep[] = ",\n";
	Client c;

	while (fgets(buffer, sizeof(buffer), f))
	{
		char* token = strtok(buffer, sep);
		c.id = atoi(token); // conversie ASCII-int

		token = strtok(NULL, sep);
		c.denumire = malloc(strlen(token) + 1); // +1 pentru spatiu necesar terminatorului de string
		strcpy(c.denumire, token);

		token = strtok(NULL, sep);
		c.tip = token[0];

		token = strtok(NULL, sep);
		strcpy(c.ultima_comanda, token);

		token = strtok(NULL, sep);
		c.valoare_totala_comenzi = (float)atof(token);

		prim = inserareNod(prim, c);
	}

	traversare(prim);

	fclose(f);
	return 0;
}