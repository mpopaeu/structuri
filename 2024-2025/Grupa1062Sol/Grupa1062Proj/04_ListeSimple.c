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

struct Nod
{
	CardBancar cb;
	struct Nod* next;
};

typedef struct Nod Nod;

// inserare nod la interior pe criteriu definit (dupa nod cu nr_card specificat)
Nod* inserare_nod_interior(Nod* lista, CardBancar data, char* numar_card)
{
	if (lista == NULL)
	{
		// lista este empty (0 noduri)
		Nod* nou = malloc(sizeof(Nod));
		nou->cb = data; // partajare temporara mem heap pt titular
		nou->next = NULL;
		lista = nou;
	}
	else
	{
		// lista contine cel putin 1 nod
		Nod* temp = lista;
		while (temp != NULL)
		{
			if (strcmp(temp->cb.nr_card, numar_card) == 0)
			{
				// nodul temp este identificat ca predecesor al lui nou
				Nod* nou = malloc(sizeof(Nod));
				nou->cb = data; // partajare temporara mem heap pt titular
				nou->next = temp->next;
				temp->next = nou;
				temp = NULL; // pentru a forta iesirea din while
							 // nodurile ramase de parsat nu intereseaza la inserare
			}
			else
				temp = temp->next;
		}
	}

	return lista;
}

void traversare_listasimpla(Nod* lista)
{
	Nod* temp = lista;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->cb.nr_card, temp->cb.titular);

		temp = temp->next;
	}
}

Nod* stergere_inceput(Nod* lista)
{
	if (lista != NULL)
	{
		// exista cel putin 1 nod in lista simpla
		Nod* temp = lista;
		lista = lista->next;

		free(temp->cb.titular); // dezalocare string pentru titular card bancar
		free(temp); // dezalocare nod de lista simpla
	}

	return lista;
}

int main()
{
	// preluare date din fisiere pentru carduri bancare
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	CardBancar card;
	Nod* prim = NULL;

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
		if (prim == NULL)
		{
			// lista este empty
			prim = inserare_nod_interior(prim, card, "");
		}
		else
		{
			prim = inserare_nod_interior(prim, card, prim->cb.nr_card);
		}

		// verificare prezenta card in lista simpla
		Nod* temp = prim;
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

	printf("Lista simpla dupa creare:\n");
	traversare_listasimpla(prim);

	prim = stergere_inceput(prim);
	printf("\n\nLista simpla dupa stergerea primului nod:\n");
	traversare_listasimpla(prim);

	while (prim != NULL)
	{
		// exista cel putin 1 nod in lista simpla
		prim = stergere_inceput(prim);
	}
	printf("\n\nLista simpla dupa dezalocare:\n");
	traversare_listasimpla(prim);

	// stergere nod din lista simpla (inceput, sfarsit)
}