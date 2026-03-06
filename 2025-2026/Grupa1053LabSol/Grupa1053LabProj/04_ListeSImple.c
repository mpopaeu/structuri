#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct Client
{
	char* nume;			// 4 bytes
	unsigned int id;	// 4 bytes
	unsigned char tip;	// 1 bytes
	unsigned int puncte;// 4 bytes
	float medie_cos;	// 4 bytes
};

typedef struct Client Client;

struct Nod
{
	Client cl;
	struct Nod* next;
};

typedef struct Nod Nod;

Nod* inserareAscId(Nod* p, Client c)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->cl = c;
	
	if (p == NULL) 
	{
		nou->next = NULL;
		return nou;
	}
	else
	{

	}

}

int main()
{
	Nod* prim = NULL; // lista marcata ca fiind empty

	FILE* f;

	f = fopen("Clienti.txt", "r");

	char buffer[256];
	char seps[] = ",\n";

	while (fgets(buffer, sizeof(buffer), f))
	{
		Client client;
		char * token = strtok(buffer, seps);
		client.nume = malloc(strlen(token) + 1);
		strcpy(client.nume, token);

		token = strtok(NULL, seps);
		client.id = atoi(token);

		token = strtok(NULL, seps);
		client.tip = token[0];

		token = strtok(NULL, seps);
		client.puncte = atoi(token);

		token = strtok(NULL, seps);
		client.medie_cos = atof(token);

		prim = inserareAscId(prim, client);
	}

	fclose(f);

	return 0;
}