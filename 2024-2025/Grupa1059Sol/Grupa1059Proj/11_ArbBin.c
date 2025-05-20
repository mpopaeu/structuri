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
	// verificare cheie de inserat cu cheie nod curent (r) pentru a continua cautarea 
	// pe subarbore stanga sau dreapta
	if (r != NULL)
	{
		if (strcmp(data.nr_card, r->data.nr_card) < 0)
		{
			// cautarea locului de inserat continua pe subarbore stanga
			r->st = inserare_nod_ABC(r->st, data, inserat);
		}
		else
		{
			if (strcmp(data.nr_card, r->data.nr_card) > 0)
			{
				// cautarea locului de inserat continua pe subarbore dreapta
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

		r = malloc(sizeof(NodArb)); // alocare nod ABC

		r->data = data;
		r->st = NULL;
		r->dr = NULL;

		*inserat = 0; // inserare cu succes pentru datele primite in parametrul data
	}

	return r;
}


void traversare_Inordine_ABC(NodArb* r)
{
	if (r != NULL)
	{
		traversare_Inordine_ABC(r->st);
		printf("%s\n", r->data.nr_card);
		traversare_Inordine_ABC(r->dr);
	}
}

NodArb* stergere_nod_ABC(NodArb* r, char* cheie, unsigned char* flag_stergere)
{
	if (r != NULL)
	{
		if (strcmp(cheie, r->data.nr_card) < 0)
		{
			// cautarea locului de inserat continua pe subarbore stanga
			r->st = stergere_nod_ABC(r->st, cheie, flag_stergere);
		}
		else
		{
			if (strcmp(cheie, r->data.nr_card) > 0)
			{
				// cautarea locului de inserat continua pe subarbore dreapta
				r->dr = stergere_nod_ABC(r->dr, cheie, flag_stergere);
			}
			else {
				// stringuri identice
				// r este nodul care se sterge din ABC
				*flag_stergere = 1; // comutare flag cheie existenta in ABC. se sterge nodul r
				
				// operatie de stergere pentru cele 3 cazuri: 0, 1 sau 2 descendenti
			}
		}
	}
	else
	{
		// r == NULL
		// nu exista nod de sters in ABC
		*flag_stergere = 0;
	}

	return r;
}

// dezalocare ABC

// determinare inaltime ABC

// identificare carduri bancare plasate pe un nivel specificat in ABC

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
		unsigned char inserat = 0; // flag identificare a unei chei deja existente in ABC
		root = inserare_nod_ABC(root, card, &inserat);

		if (inserat != 0)
		{
			printf("Cardul bancar %s NU a fost inserat in ABC\n", card.nr_card);
			// dezalocare detinator card
			free(card.detinator);
		}
		else
		{
			printf("Cardul bancar %s A FOST inserat in ABC\n", card.nr_card);
		}

		
		fscanf(f, "%[^,],%[^,],%[^,],%f,%[^\n]", card.nr_card, titular,
					card.expira_la, &(card.sold), card.moneda); // citire nr card de pe linia urmatoare din fisier
	}
	fclose(f);

	printf("ABC in traversare in Inordine:\n");
	traversare_Inordine_ABC(root);

	return 0;
}