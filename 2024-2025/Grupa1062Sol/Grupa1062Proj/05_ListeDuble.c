#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define DIM_CARD_BANCAR 16
#define DIM_DATA_EXPIRARE 7
#define DIM_MONEDA 3


struct CardBancar
{
	char nr_card[DIM_CARD_BANCAR + 1]; // +1 pentru terminator string; 20 bytes (17 + 3 padding)
	char* titular; // 4 bytes
	char data_expirare[DIM_DATA_EXPIRARE + 1]; // +1 pentru terminator string; 12 bytes (9 + 3 padding) 
	float sold; // 4 bytes
	char moneda[DIM_MONEDA + 1]; // cod moneda; 4 bytes (no padding)
};

typedef struct CardBancar CardBancar;

struct NodD
{
	CardBancar cb;
	struct NodD* next, *prev;
};

typedef struct NodD NodD;

struct ListaDubla
{
	NodD* prim, * ultim;
};

typedef struct ListaDubla ListaDubla;

// inserare nod la interior pe criteriu definit (dupa nod cu nr_card specificat)
ListaDubla inserare_nod_interior(ListaDubla lista, CardBancar data, char* numar_card)
{
	if (lista.prim == NULL)
	{
		// lista nu contine nici un nod
		NodD* nou = malloc(sizeof(NodD));
		nou->cb = data;
		nou->next = NULL;
		nou->prev = NULL;
		lista.prim = nou;
		lista.ultim = nou;
	}
	else
	{
		// cel putin 1 nod in lista
		// cautare nod cu numar_card
		NodD* temp = lista.prim;
		while (temp != NULL)
		{
			if (strcmp(temp->cb.nr_card, numar_card) == 0)
			{
				// nodul cu nr card cautat a fost identificat
				// nou se insereaza dupa temp
				NodD* nou = malloc(sizeof(NodD));
				nou->cb = data;
				nou->prev = temp;
				nou->next = temp->next;
				NodD* succesor_temp = temp->next;
				temp->next = nou;

				if (nou->next == NULL)
				{
					// nou se insereaza la sfarsitul listei duble
					lista.ultim = nou;
				}
				else
				{
					// exista succesor pt temp inainte de atasarea lui nou la lista dubla
					succesor_temp->prev = nou;
				}
				temp = NULL; // fortare iesire din while
			}
			else
				temp = temp->next;
		}
	}

	return lista;
}

void traversare_listadubla(ListaDubla lista)
{
	NodD* temp = lista.prim;
	printf("Lista dubla traversare prim->ultim:\n");
	while (temp)
	{
		printf("%s %s\n", temp->cb.nr_card, temp->cb.titular);
		temp = temp->next;
	}

	temp = lista.ultim;
	printf("Lista dubla traversare ultim->prim:\n");
	while (temp)
	{
		printf("%s %s\n", temp->cb.nr_card, temp->cb.titular);
		temp = temp->prev;
	}
}

ListaDubla stergere_inceput(ListaDubla lista)
{
	if (lista.prim != NULL)
	{
		NodD* temp = lista.prim;
		lista.prim = lista.prim->next;

		if (lista.prim == NULL)
		{
			// lista dubla devine empty
			lista.ultim = NULL;
		}
		else
		{
			lista.prim->prev = NULL;
		}

		free(temp->cb.titular);		// dezalocare string titular card bancar
		free(temp);					// dezalocare nod lista dubla
	}

	return lista;
}

int main()
{
	// preluare date din fisiere pentru carduri bancare
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	CardBancar card;
	ListaDubla listaD; // variabila cu pointeri de acces la capetele listei duble
	listaD.prim = NULL; // nu exista primul nod (lista empty)
	listaD.ultim = NULL; // nu exista ultimul nod (lista empty)

	char buffer[150];
	char sep[] = ";\n";

	fgets(buffer, sizeof(buffer), f);

	while (!feof(f))
	{
		char* token = NULL;
		token = strtok(buffer, sep);
		strcpy(card.nr_card, token);

		token = strtok(NULL, sep);
		card.titular = malloc(strlen(token) + 1);
		strcpy(card.titular, token);

		token = strtok(NULL, sep);
		strcpy(card.data_expirare, token);

		token = strtok(NULL, sep);
		card.sold = (float)atof(token);

		token = strtok(NULL, sep);
		strcpy(card.moneda, token);

		// apel de functie pentru inserare nod in lista simpla
		if (listaD.prim == NULL)
		{
			// lista este empty
			listaD = inserare_nod_interior(listaD, card, "");
		}
		else
		{
			listaD = inserare_nod_interior(listaD, card, listaD.prim->cb.nr_card); // listaD.prim->cb.nr_card exista sigur in lista
		}

		// verificare prezenta card in lista simpla
		NodD* temp = listaD.prim;
		unsigned char flag = 0; // card.nr_card nu este prezent in lista simpla
		while ((temp != NULL) && (flag == 0))
		{ // cautare prezenta card.nr_card in lista simpla dupa apel functie inserare nod
			if (strcmp(temp->cb.nr_card, card.nr_card) == 0)
			{
				flag = 1; // card.nr_card este gasit in lista simpla
			}
			temp = temp->next;
		}
		if (flag == 0) // card nu a fost inserat in lista simpla
		{
			// card.nr_card nu a fost gasit in lista simple, deci nu a avut loc inserarea
			free(card.titular);
		}

		// incercare preluare linie urmatoare (daca exista)
		fgets(buffer, sizeof(buffer), f);
	}
	fclose(f);

	printf("Lista dubla dupa creare:\n");
	traversare_listadubla(listaD);

	listaD = stergere_inceput(listaD);
	printf("\n\nLista dubla dupa stergerea primului nod:\n");
	traversare_listadubla(listaD);

	while (listaD.prim != NULL)
	{
		// exista cel putin 1 nod in lista dubla
		listaD = stergere_inceput(listaD);
	}
	printf("\n\nLista dubla dupa dezalocare:\n");
	traversare_listadubla(listaD);

	// stergere nod din lista dubla (inceput, sfarsit)

	// stergere noduri cu acelasi titular in lista dubla
	// Implementare QuickSort
}