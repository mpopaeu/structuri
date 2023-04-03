#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define VECTOR_SIZE 10
#define BUFFER_SIZE 256

struct ContBancar
{
	char iban[25];
	char* titular;
	char moneda[4];
	float sold;
	unsigned int nr_carduri;
};

struct NodD_CB
{
	struct ContBancar cb;
	struct NodD_CB *prev, *next;
};

struct ListaDubla
{
	struct NodD_CB* p, * u;
};

struct ListaDubla inserare_inceputLD(struct ListaDubla lst, struct ContBancar cb)
{
	struct NodD_CB* nou = (struct NodD_CB*)malloc(sizeof(struct NodD_CB));

	nou->cb = cb;
	nou->cb.titular = (char*)malloc(strlen(cb.titular) + 1);
	strcpy(nou->cb.titular, cb.titular);

	nou->prev = NULL;
	nou->next = lst.p;

	if (lst.p == NULL)
	{
		// lista dubla empty
		lst.p = lst.u = nou;
	}
	else
	{
		// exista cel putin 1 nod in lista dubla
		lst.p->prev = nou;
		lst.p = nou;
	}

	return lst;
}


// inserare nod in interiorul LD astfel incat conturile bancare sunt sortare crescator/descrescator pe sold

// stergere nod (cu extragere date cont bancar) de pe o pozitie specificata in lista dubla

// interschimbare noduri oarecare in lista dubla (cu modificarea adreselor de legatura/succesiunii de noduri) 

int main()
{

	struct ContBancar cb, vcb[VECTOR_SIZE];
	FILE* f;
	unsigned int i = 0;
	unsigned char nr_conturi;

	f = fopen("Conturi.txt", "r");

	char buffer[BUFFER_SIZE], seps[] = ",\n";

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

		vcb[i++] = cb;
	}
	fclose(f);

	struct ListaDubla lista;
	lista.p = lista.u = NULL;

	nr_conturi = (unsigned char)i;
	for (i = 0; i < nr_conturi; i++)
	{
		lista = inserare_inceputLD(lista, vcb[i]);
	}

	// parsare lista dubla in ambele sensuri

	struct ListaDubla lst;
}