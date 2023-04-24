#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define VECTOR_SIZE 10

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
	struct NodCB* next, *prev;
};

struct ListaDubla
{
	struct NodCB* p, * u;
};


struct ListaDubla inserare_LD_sfarsit(struct ListaDubla lista, struct ContBancar cont)
{
	struct NodCB* nou = (struct NodCB*)malloc(sizeof(struct NodCB));
	nou->cb = cont;
	nou->next = NULL;
	nou->prev = lista.u;

	if (lista.p == NULL)
	{
		// lista dubla empty
		lista.p = nou;
		lista.u = nou;
	}
	else
	{
		// exista cel putin 1 nod in lista dubla
		lista.u->next = nou;
		lista.u = nou;
	}

	return lista;
}

void traversare_bi(struct ListaDubla lista)
{
	// traversare lista dubla in ambele sensuri
	struct NodCB* temp = lista.p;
	printf("Traversare lista dubla inceput->sfarsit:\n");
	while (temp)
	{
		printf("%s %.2f\n", temp->cb.titular, temp->cb.sold);
		temp = temp->next;
	}
	temp = lista.u;
	printf("Traversare lista dubla sfarsit->inceput:\n");
	while (temp)
	{
		printf("%s %.2f\n", temp->cb.titular, temp->cb.sold);
		temp = temp->prev;
	}
}


int main()
{
	FILE* f;
	f = fopen("conturi.txt", "r");

	struct ListaDubla listaD; // variabila gestionare structura lista dubla
	listaD.p = listaD.u = NULL; // initialiare structur lista dubla ca fiind empty

	char buffer[BUFFER_SIZE], seps[] = ",\n";

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

		// inserare cont bancar cb in lista dubla listaD
		listaD = inserare_LD_sfarsit(listaD, cb);
	}

	printf("Lista dubla dupa creare:\n");
	traversare_bi(listaD);

	fclose(f);

	// dezalocare lista dubla
	struct NodCB* temp;
	while (listaD.p)
	{
		temp = listaD.p; 

		listaD.p = listaD.p->next;
		if(listaD.p) // exista cel putin 1 nod in lista ramasa
			listaD.p->prev = NULL; 

		free(temp->cb.titular); // dezalocare extensii ale contului bancar in memorie heap
		free(temp);				// dezalocare nod
	}
	listaD.u = NULL; // reinitializare adresa catre ultimul nod; nici un nod ramas in lista dubla

	printf("Lista dubla dupa dezalocare:\n");
	traversare_bi(listaD);
}