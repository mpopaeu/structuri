#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define NR_CIFRE_CARD 16
#define DIM_MONEDA 3

struct DataExpirare
{
	unsigned short int anul;
	unsigned char luna;
};

typedef struct DataExpirare DataExpirare;

struct CardBancar
{
	char nr_card[NR_CIFRE_CARD + 1]; // +1 pentru terminatot de string util in cazul utilizarii ca string
	char* titular;
	DataExpirare data;
	float sold;
	char moneda[DIM_MONEDA + 1]; // RON, EUR, USD
};

typedef struct CardBancar CardBancar;

struct NodD
{
	CardBancar card;
	struct NodD* next, *prev;
};

typedef struct NodD NodD;

struct ListaDubla
{
	NodD* prim, * ultim;
};

typedef struct ListaDubla ListaDubla;

// inserare nod la sfarsitul listei duble
ListaDubla inserare_sfarsit(ListaDubla lista, CardBancar data)
{
	NodD* nou = malloc(sizeof(NodD));
	nou->card = data;
	nou->next = NULL; // succesor NULL tot timpul pentru nou
	nou->prev = lista.ultim; // predecesor ultim curent

	if (lista.ultim == NULL)
	{
		// lista nu contine nici un nod
		// nou devine primul, ultimul si unicul nod in lista dubla
		lista.prim = nou;
	}
	else
	{
		lista.ultim->next = nou; // sfarsitul curent va avea succesor pe nou
	}
	lista.ultim = nou; // actualizare sfarsit curent de lista dubla

	return lista; // actualizare capete de acces la lista dubla
}


// traversare lista dubla in ambele sensuri
void traversare_listadubla(ListaDubla lista)
{
	NodD* temp = lista.prim;
	printf("Lista dubla traversare prim->ultim:\n");
	while (temp != NULL)
	{
		printf("%s %s\n", temp->card.nr_card, temp->card.titular);
		temp = temp->next;
	}
	temp = lista.ultim;
	printf("Lista dubla traversare ultim->prim:\n");
	while (temp != NULL)
	{
		printf("%s %s\n", temp->card.nr_card, temp->card.titular);
		temp = temp->prev;
	}
}

void traversare_recursiv(NodD* temp)
{
	if (temp != NULL)
	{
		printf("%s %s\n", temp->card.nr_card, temp->card.titular);
		traversare_recursiv(temp->next); // apel recursiv pentru nodul succesor
	}
}

// stergere nod la inceputul listei duble
ListaDubla stergere_inceput(ListaDubla lista)
{
	if (lista.prim != NULL)
	{
		// exista cel putin 1 nod in lista dubla
		NodD* temp = lista.prim;
		if (lista.prim->next == NULL)
		{
			// exista un singur nod in lista dubla fiind deja salvat in temp
			lista.prim = NULL; // lista devine empty
			lista.ultim = NULL; // lista devine empty
		}
		else
		{
			// cel putin 2 noduri in lista dubla
			lista.prim = lista.prim->next; // noul inceput de lista dubla este nodul #2
			lista.prim->prev = NULL; // nodul #2 devine inceput de lista dubla, deci nu are predecesor
		}

		free(temp->card.titular); // dezalocare string pentru titular
		free(temp); // dezalocare nod lista dubla 
	}

	return lista;
}

// traversare recursiva ultim->prim

// stergere noduri din lista dubla pe baza anului expirarii cardului

// functie interschimbare noduri oarecare din lista dubla

// functie sortare noduri lista dubla

// functie stergere nod de pe pozitia i in lista dubla
// datele cardului bancar sunt "salvate"/returnate in vederea utilizarii ulterioare 
// (stergere cu extragerea datelor din nod)


int main()
{
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	char buffer[200];
	CardBancar card;
	ListaDubla listaD;
	listaD.prim = NULL;
	listaD.ultim = NULL;

	fgets(buffer, sizeof(buffer), f);
	while (!feof(f))
	{
		strtok(buffer, "\n");
		strcpy(card.nr_card, buffer);

		fgets(buffer, sizeof(buffer), f);
		strtok(buffer, "\n");
		card.titular = malloc(strlen(buffer) + 1); // +1 terminator de string
		strcpy(card.titular, buffer);

		fgets(buffer, sizeof(buffer), f);
		strtok(buffer, "\n");
		sscanf(buffer, "%hu%hhu", &card.data.anul, &card.data.luna);

		fgets(buffer, sizeof(buffer), f);
		strtok(buffer, "\n");
		card.sold = (float)atof(buffer);

		fgets(buffer, sizeof(buffer), f);
		strtok(buffer, "\n");
		strcpy(card.moneda, buffer);

		// inserare date card bancar in lista dubla
		listaD = inserare_sfarsit(listaD, card);

		fgets(buffer, sizeof(buffer), f);
	}
	fclose(f);

	printf("Lista dubla dupa creare:\n");
	traversare_listadubla(listaD);
	printf("\n\nLista dubla dupa creare (traversare versiune recursiva)\n");
	traversare_recursiv(listaD.prim);

	listaD = stergere_inceput(listaD);
	printf("\n\nLista dubla dupa stergerea unui nod:\n");
	traversare_listadubla(listaD);

	while (listaD.prim != NULL)
	{
		listaD = stergere_inceput(listaD);
	}
	printf("\n\nLista dubla dupa dezalocare:\n");
	traversare_listadubla(listaD);

	return 0;
}