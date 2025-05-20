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
	char nr_card[DIM_CARD_BANCAR + 1];
	char* titular;
	char data_expirare[DIM_DATA_EXPIRARE + 1];
	float sold;
	char moneda[DIM_MONEDA + 1];
};

typedef struct CardBancar CardBancar;

struct NodArbore
{
	CardBancar cb;
	struct NodArbore* stanga, *dreapta;
};

typedef struct NodArbore NodArbore;

NodArbore* inserare_nod_ABC(NodArbore* r, CardBancar data, unsigned char *inserat)
{
	if (r != NULL)
	{
		// cautare a locului de inserat
		// r este nod curent atins in operatia de cautare a locului de inserat
		if (strcmp(data.nr_card, r->cb.nr_card) < 0)
		{
			// continua cautarea locului de inserat pe descendentul stanga al nodului curent r
			r->stanga = inserare_nod_ABC(r->stanga, data, inserat);
		}
		else
		{
			if (strcmp(data.nr_card, r->cb.nr_card) > 0)
			{
				// continua cautarea locului de inserat pe subarborele dreapta nodului curent r
				r->dreapta = inserare_nod_ABC(r->dreapta, data, inserat);
			}
			else
			{
				// s-a identificat cheie duplicat in ABC
				// se abandoneaza operatia de inserare
				*inserat = 0;
			}
		}
	}
	else
	{
		// nodul curent este NULL
		// a fost identificat locul in arbore unde se insereaza nod cu datele din data

		r = malloc(sizeof(NodArbore)); // alocare nod ABC

		r->cb = data;
		r->stanga = NULL;
		r->dreapta = NULL;

		// comutare flag pe SUCCES
		*inserat = 1;
	}

	return r;
}

void traversare_inordine(NodArbore* r)
{
	if (r != NULL)
	{
		// exista nod curent r
		traversare_inordine(r->stanga);
		printf("Card %s\n", r->cb.nr_card);
		traversare_inordine(r->dreapta);
	}
}

// stergere noduri frunza din ABC

// determinare inaltime ABC (nr niveluri)

// determinare nr de noduri de pe nivel specificat

// dezalocare ABC
NodArbore* dezalocare_ABC(NodArbore* r)
{
	if (r != NULL)
	{
		// dezalocare noduri din subarbore stanga
		r->stanga = dezalocare_ABC(r->stanga);
		// dezalocare noduri din subarbore dreapta
		r->dreapta = dezalocare_ABC(r->dreapta);

		printf("Stergere card bancar %s\n", r->cb.nr_card);
		free(r->cb.titular);
		free(r); // dezalocare nod curent
		r = NULL; // valoarea NULL scrisa in parintele lui r la revenirea in apelul anterior
	}

	return r;
}

// stergere noduri frunza plasate pe un nivel specificat in ABC
NodArbore* stergere_frunze_nivel(NodArbore* r, unsigned char nivel)
{
	if (r != NULL)
	{
		if (nivel > 1)
		{
			r->stanga = stergere_frunze_nivel(r->stanga, nivel-1);
			r->dreapta = stergere_frunze_nivel(r->dreapta, nivel-1);
		}
		else
		{
			if (nivel == 1)
			{
				// nivelul targetat prin operatia de stergere
				if ((r->stanga == NULL) && (r->dreapta == NULL))
				{
					printf("Frunza care se sterge: %s\n", r->cb.nr_card);
					free(r->cb.titular);
					free(r);
					r = NULL;
				}
			}
		}
	}

	return r;
}

int main()
{
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	CardBancar card;

	NodArbore* root = NULL; // pointer acces la arbore binar de cautare

	char buffer[150];
	char sep[] = ";\n";

	fgets(buffer, sizeof(buffer), f);

	while (!feof(f))
	{
		char* token = NULL;
		token = strtok(buffer, sep);
		strcpy(card.nr_card, token);

		token = strtok(NULL, sep);
		card.titular = malloc(strlen(token) + 1); // pointer titular se rescrie pentru fiecare card preluat din fisier
		strcpy(card.titular, token);

		token = strtok(NULL, sep);
		strcpy(card.data_expirare, token);

		token = strtok(NULL, sep);
		card.sold = (float)atof(token);

		token = strtok(NULL, sep);
		strcpy(card.moneda, token);

		// inserare card in arbore binar de cautare
		unsigned char inserat; // flag pentru finalizare operatie inserare: 0 esec, 1 succes
		root = inserare_nod_ABC(root, card, &inserat);

		if (inserat != 0)
		{
			printf("Cardul %s a fost inserat in arbore \n", card.nr_card);
		}
		else
		{
			printf("Cardul %s NU a fost inserat in arbore \n", card.nr_card);
			free(card.titular); // dezalocare titular deoarece card nu a fost inserat in ABC
		}
		
		// incercare preluare linie urmatoare (daca exista)
		fgets(buffer, sizeof(buffer), f);
	}
	fclose(f);

	printf("\n\nTraversare inordine arbore binar de cautare:\n");
	traversare_inordine(root);

	printf("\n\nStergere frunze de pe nivel specificat:\n");
	root = stergere_frunze_nivel(root, 4);
	printf("\n\nTraversare inordine arbore binar de cautare dupa stergere frunze de pe nivel specificat:\n");
	traversare_inordine(root);

	printf("\nDezalocare ABC\n");
	root = dezalocare_ABC(root);
	printf("\nTraversare inordine arbore binar de cautare dupa dezalocare:\n");
	traversare_inordine(root);

	return 0;
}