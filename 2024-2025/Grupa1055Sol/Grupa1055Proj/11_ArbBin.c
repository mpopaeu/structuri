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
	char nr_card[NR_CIFRE_CARD + 1]; 
	char* titular;
	DataExpirare data;
	float sold;
	char moneda[DIM_MONEDA + 1]; 
};

typedef struct CardBancar CardBancar;

struct NodArbore
{
	CardBancar card;
	struct NodArbore * stanga, * dreapta;
};

typedef struct NodArbore NodArbore;

NodArbore* inserare_nod_ABC(NodArbore* r, CardBancar card, unsigned char *flag)
{
	if (r != NULL)
	{
		// exista nod curent r
		// se decide pe care subarbore se continua cautarea locului de inserat pentru card
		if (strcmp(r->card.nr_card, card.nr_card) < 0)
		{
			// se continua cautarea locului de inserat pe stanga nodului (subarborelui) curent
			r->stanga = inserare_nod_ABC(r->stanga, card, flag);
		}
		else
		{
			if (strcmp(r->card.nr_card, card.nr_card) > 0)
			{
				// se continua cautarea locului de inserat pe dreapta nodului (subarborelui) curent
				r->dreapta = inserare_nod_ABC(r->dreapta, card, flag);
			}
			else
			{
				// nodul curent r contine aceeasi cheie (nr card) cu setul de date de inserat
				// trebuie oprita inserarea
				*flag = 0;  // comutare flag pe modul INSERARE ESUATA 
			}
		}
	}
	else
	{
		// nod curent este nul
		// acesta este locul de inserat pentru datele din card
		r = malloc(sizeof(NodArbore)); // alocare nod ABC nou
		r->card = card; // copiere date card bancar in nod ABC
		
		// nodul care se insereaza este nod frunza
		r->stanga = NULL;
		r->dreapta = NULL;

		*flag = 1; // comutare flag pe modul INSERARE CU SUCCES
	}

	return r;
}

// traversare ABC: preordine, inordine, postordine, niveluri

// stergere nod frunza in ABC

// determinare nr noduri frunza in ABC


int main()
{
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	char buffer[200];
	CardBancar card;
	
	NodArbore* root = NULL;

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

		// inserare date card bancar in arbore binar de cautare
		unsigned char flag_inserare = 0; // 0 - inserarea nu a avut loc
		root = inserare_nod_ABC(root, card, &flag_inserare);

		if (flag_inserare == 0)
		{
			// inserarea datelor din variabila card nu a avut loc
			printf("Inserare esuata pentru cardul %s\n", card.nr_card);
			// dezalocare zone de heap pregatite in variabila card
			free(card.titular); // pentru eliminare mem leaks
		}
		else
		{
			printf("Inserare cu succes pentru cardul %s\n", card.nr_card);
		}

		fgets(buffer, sizeof(buffer), f);
	}
	fclose(f);
}