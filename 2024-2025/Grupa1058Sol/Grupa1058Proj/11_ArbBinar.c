#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define DIM_NR_CARD 16
#define DIM_DATA_EXPIRARE 5

struct CardBancar
{
	char* titular;
	char nr_card[DIM_NR_CARD + 1];
	float sold;
	char* emitent;
	char data_expirare[DIM_DATA_EXPIRARE + 1];
};

typedef struct CardBancar CardBancar;

struct NodABC
{
	CardBancar cb;
	struct NodABC *stanga, *dreapta;
};

typedef struct NodABC NodABC;

NodABC* inserare_nod_ABC(NodABC* r, CardBancar data, unsigned char* inserat)
{
	if (r != NULL) // r este nod curent in ABC
	{
		// exista nod curent care trebuie verificat in raport cu cheia din data
		if (strcmp(data.nr_card, r->cb.nr_card) < 0)
		{
			// se continua cautare locaului de inserat pe descendentul stanga a nodului curent r
			r->stanga = inserare_nod_ABC(r->stanga, data, inserat);
		}
		else
		{
			if (strcmp(data.nr_card, r->cb.nr_card) > 0)
			{
				// se continua cautarea locului de inserat pe descendentul dreapta a nodului curent r
				r->dreapta = inserare_nod_ABC(r->dreapta, data, inserat);
			}
			else
			{
				// cheie de inserat este identificata in ABC
				// se abandoneaza operatia de inserare
				*inserat = 0;
			}
		}
	}
	else {
		// locul de inserat a fost identificat in ABC (este pozitie de NULL in structura ABC)
		r = malloc(sizeof(NodABC)); // alocare nod 

		r->cb = data;
		r->stanga = NULL;
		r->dreapta = NULL;

		// comutare flag inserare
		*inserat = 1;
	}

	return r;
}

void traversare_Inordine(NodABC * r)
{
	if (r != NULL)
	{
		traversare_Inordine(r->stanga);
		printf("Card %s\n", r->cb.nr_card);
		traversare_Inordine(r->dreapta);
	}
}

// dezalocare de ABC
NodABC* dezalocare_ABC(NodABC* r)
{
	if (r != NULL)
	{
		// 1. dezalocare noduri din subarbore stanga
		r->stanga = dezalocare_ABC(r->stanga);
		// 2. dezalocare noduri din subarbore dreapta
		r->dreapta = dezalocare_ABC(r->dreapta);

		// 3. prelucrare nod curent r: dezalocare/stergere nod din ABC
		printf("Stergere nod %s\n", r->cb.nr_card);
		free(r->cb.emitent);
		free(r->cb.titular);
		free(r);
		r = NULL;
	}

	return r; 
}

// determinare inaltime ABC (nr niveluri)

// determinare numar de noduri de pe nivel specificat

// stergere noduri frunza in ABC
NodABC* stergere_frunze_ABC(NodABC* r)
{
	if (r != NULL)
	{
		// traversare/vizitare ABC in preordine
		if ((r->stanga == NULL) && (r->dreapta == NULL))
		{
			free(r->cb.emitent);
			free(r->cb.titular);
			free(r);
			r = NULL;
		}
		else
		{
			// r nu este frunza; continua cautarea pe ambii descendenti
			r->stanga = stergere_frunze_ABC(r->stanga);
			r->dreapta = stergere_frunze_ABC(r->dreapta);
		}
	}

	return r;
}

NodABC* stergere_nod_ABC(NodABC* r, char* cheie, unsigned char* flag_stergere)
{
	if (r != NULL)
	{
		if (strcmp(cheie, r->cb.nr_card) < 0)
		{
			r->stanga = stergere_nod_ABC(r->stanga, cheie, flag_stergere);
		}
		else
		{
			if (strcmp(cheie, r->cb.nr_card) > 0)
			{
				r->dreapta = stergere_nod_ABC(r->dreapta, cheie, flag_stergere);
			}
			else
			{
				// a fost identificat nodul de sters
				*flag_stergere = 1;
				if ((r->stanga == NULL) && (r->dreapta = NULL))
				{
					// r este nod frunza
					free(r->cb.emitent);
					free(r->cb.titular);
					free(r);
					r = NULL;
				}
				else
				{
					if ((r->stanga != NULL) && (r->dreapta != NULL))
					{
						// r cu 2 descendenti
						// ????
					}
					else
					{
						// r cu 1 descendent
						NodABC* temp = NULL;
						if (r->stanga != NULL)
						{
							temp = r->stanga;
						}
						else
						{
							temp = r->dreapta;
						}

						free(r->cb.emitent);
						free(r->cb.titular);
						free(r);
						r = temp; // r se actualizeaza cu descendentul sau pe care il trimitem la parinte
					}
				}
			}
		}
	}
	else
	{
		*flag_stergere = 0; // nu a fost identificat nodul de sters in ABC
	}

	return r; 
}

int main()
{
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");
	CardBancar card; // variabila stocare temporara a datelor unui card

	NodABC* root = NULL;

	char temp_buff[100]; // buffer temporar pentru stocare linii preluate din fisier text
	fgets(temp_buff, sizeof(temp_buff), f);

	while (!feof(f))
	{
		strtok(temp_buff, "\n");
		card.titular = malloc(strlen(temp_buff) + 1); // rescriere card.titular; mem leak potential
		strcpy(card.titular, temp_buff);

		fgets(temp_buff, sizeof(temp_buff), f);
		strtok(temp_buff, "\n");
		strcpy(card.nr_card, temp_buff);

		fgets(temp_buff, sizeof(temp_buff), f);
		strtok(temp_buff, "\n");
		card.sold = (float)atof(temp_buff); // conversie ASCII-to-Binary pentru float

		fgets(temp_buff, sizeof(temp_buff), f);
		strtok(temp_buff, "\n");
		card.emitent = malloc(strlen(temp_buff) + 1); // rescriere card.titular; mem leak potential
		strcpy(card.emitent, temp_buff);

		fgets(temp_buff, sizeof(temp_buff), f);
		strtok(temp_buff, "\n");
		strcpy(card.data_expirare, temp_buff);

		// inserare nod in arbore binar de cautare
		unsigned char inserat = 0; // 0 - esec inserare, 1 - succes inserare
		root = inserare_nod_ABC(root, card, &inserat);

		if (inserat != 0)
		{
			printf("Inserare cu succes card %s \n", card.nr_card);
		}
		else
		{
			printf("Inserare esuata card %s \n", card.nr_card);
			// dezalocare extensii card (pointerii emitent si titular) in mem heap
			free(card.emitent);
			free(card.titular);
		}
		
		// incercare preluare titular card urmator
		fgets(temp_buff, sizeof(temp_buff), f);
	}
	fclose(f);

	printf("\nArbore Binar de Cautare traversat in Inordine:\n");
	traversare_Inordine(root);

	printf("\nStergere frunze in Arbore Binar de Cautare:\n");
	root = stergere_frunze_ABC(root);
	printf("\nArbore Binar de Cautare traversat in Inordine dupa stergere frunze:\n");
	traversare_Inordine(root);
	
	printf("\nDezalocare Arbore Binar de Cautare:\n");
	root = dezalocare_ABC(root);
	printf("\nArbore Binar de Cautare traversat in Inordine dupa dezalocare:\n");
	traversare_Inordine(root);
}