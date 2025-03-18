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

// inserare nod la interior pe criteriu definit (?!)
Nod* inserare_nod_interior(Nod* lista, CardBancar data, ??????)
{

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

		// incercare preluare linie urmatoare (daca exista)
		fgets(buffer, sizeof(buffer), f);
	}
	fclose(f);

	// stergere nod din lista simpla (inceput, sfarsit)
}