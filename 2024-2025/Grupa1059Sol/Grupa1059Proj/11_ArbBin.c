#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define CARD_NO_LENGTH 16
#define MONEDA_COD_LENGTH 3

struct CardBancar
{
	char nr_card[CARD_NO_LENGTH + 1];
	char* detinator;
	char expira_la[6];
	float sold;
	char moneda[MONEDA_COD_LENGTH + 1];
};

typedef struct CardBancar CardBancar;

struct NodArb {
	CardBancar data;
	struct NodArb* st, * dr;
};

typedef struct NodArb NodArb;

NodArb* inserare_nod_ABC(NodArb* r, CardBancar data, unsigned char *inserat)
{
	// verificare cheie de inserat cu cheie nod curent (r) pentru a continua cautarea pe subarbore stanga sau dreapta
	if (r != NULL)
	{
		if (strcmp(r->data.nr_card, data.nr_card) < 0)
		{
			r->st = inserare_nod_ABC(r->st, data, inserat);
		}
		else
		{
			if (strcmp(r->data.nr_card, data.nr_card) > 0)
			{
				r->dr = inserare_nod_ABC(r->dr, data, inserat);
			}
			else {
				// stringuri identice
				*inserat = 1; // comutare flag cheie existenta in ABC. se abandoneaza cautarea locului de inserat
				return r;
			}
		}
	}
	else
	{
		// r == NULL
		// am identificat locul de inserat pentru setul data
	}


}

int main()
{
	NodArb* root = NULL; // variabila pointer la nod radacina cu care accesez tot arborele binar de cautare

	char titular[150];
	CardBancar card;
	FILE* f = fopen("CarduriBancare.txt", "r");
	fscanf(f, "%[^,],%[^,],%[^,],%f,%[^\n]", card.nr_card, titular,
		card.expira_la, &(card.sold), card.moneda);
	while (!feof(f))
	{
		card.detinator = malloc(strlen(titular) + 1);
		strcpy(card.detinator, titular);

		fscanf(f, "\n");

		// inserare date card bancar (card) in arbore binar de cautare
		unsigned char inserat = 0; // flag de identificare a unei chei deja existente in ABC
		root = inserare_nod_ABC(root, card, &inserat);

		if (inserat != 0)
		{
			printf("Cardul bancar %s nu a fost inserat in ABC\n", card.nr_card);
			// dezalocare detinator card
			free(card.detinator);
		}

		
		fscanf(f, "%[^,],%[^,],%[^,],%f,%[^\n]", card.nr_card, titular,
			card.expira_la, &(card.sold), card.moneda); // citire nr card de pe linia urmatoare
	}
	fclose(f);

	return 0;
}