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

struct Nod
{
	CardBancar card;
	struct Nod* next;
};

typedef struct Nod Nod;

// inserare nod la sfarsitul listei simple
Nod* inserare_sfarsit(Nod* lista , CardBancar data)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->card = data;
	nou->next = NULL;

	if (lista == NULL)
	{
		return nou; // nou devine primul si unicul si ultimul din lista simpla
	}
	else
	{
		Nod* temp = lista;
		while (temp->next != NULL)
		{
			temp = temp->next; // temp rescris cu adresa succesorului curent
		}

		// temp este ultimul nod din lista simpla
		temp->next = nou; // atasare nou la sfarsitul listei simple
	}
	return lista;
}

// traversare lista simpla
void traversare_listasimpla(Nod* lista)
{
	Nod* temp = lista;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->card.nr_card, temp->card.titular);
		temp = temp->next;
	}
}

// stergere nod la inceputul listei simple
Nod* stergere_inceput(Nod* lista)
{
	if (lista != NULL)
	{
		// exista cel putin un nod in lista simpla
		Nod* temp = lista; // salvare temporara a primului nod in temp
		lista = lista->next; // actualizare inceput de lista simpla

		free(temp->card.titular); // dezalocare mem heap alocata pt pointer titular
		free(temp); // dezalocare mem heap pentru inceputul de lista simpla
	}

	return lista; // returneaza noul inceput de lista 
}

int main()
{
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	char buffer[200];
	CardBancar card;
	Nod* prim = NULL; // variabila locala acces la primul element din lista simpla

	fgets(buffer, sizeof(buffer), f);
	while (!feof(f))
	{
		buffer[sizeof(card.nr_card) - 1] = 0;
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

		// inserare date card bancar in lista simpla
		prim = inserare_sfarsit(prim, card);

		fgets(buffer, sizeof(buffer), f);
	}
	fclose(f);

	printf("Lista simpla dupa creare:\n");
	traversare_listasimpla(prim);

	prim = stergere_inceput(prim);
	printf("\n\nLista simpla dupa stergerea unui nod:\n");
	traversare_listasimpla(prim);

	while (prim != NULL)
	{
		prim = stergere_inceput(prim);
	}
	printf("\n\nLista simpla dupa dezalocare:\n");
	traversare_listasimpla(prim);

	return 0;
}