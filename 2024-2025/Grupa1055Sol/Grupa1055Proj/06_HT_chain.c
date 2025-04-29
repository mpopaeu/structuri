#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define NR_CIFRE_CARD 16
#define DIM_MONEDA 3
#define DIM_TABELA_DISPERSIE 77

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

struct Nod
{
	CardBancar card;
	struct Nod* next;
};

typedef struct Nod Nod;

// inserare nod la sfarsitul listei simple
Nod* inserare_sfarsit(Nod* lista, CardBancar data)
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

unsigned char functie_hash(char* cheie, unsigned char dim_tabela)
{
	unsigned int suma_ASCII = 0; // suma codurilor ASCII pentru simbolurile din stringul cheie
	for (unsigned char i = 0; i < strlen(cheie); i++)
		suma_ASCII += cheie[i];

	return (suma_ASCII % dim_tabela); // impartire cu rest la nr maxim de liste simple stocare in tabela/vectorul de dispersie
}

// inserare date card bancar in tabela de dispersie cu chaining
unsigned char inserare_HT(Nod** tabela, unsigned char dim_tabela, CardBancar data)
{
	// 1. determinare pozitie in tabela hash unde se va insera card bancar data
	unsigned char offset_tabela = functie_hash(data.nr_card, dim_tabela);
	// 2. inserare in lista simpla determinata la pasul 1 a cardului bancar data
	tabela[offset_tabela] = inserare_sfarsit(tabela[offset_tabela], data);

	return offset_tabela;
}

// cautare in tabela de dispersie cu chaining pe baza cheii
CardBancar* cautare_HT(Nod** tabela, unsigned char dim_tabela, char* nr_card_cautat)
{
	// 1. calcul offset lista in tabela hash unde s-ar afla nr_card_cautat
	unsigned char offset_tabela = functie_hash(nr_card_cautat, dim_tabela);

	// 2. cautare secventiala a cardului in lista simpla de pe offsetul offset_tabela calculat la pasul 1
	Nod* temp = tabela[offset_tabela];
	while (temp != NULL)
	{
		if (strcmp(nr_card_cautat, temp->card.nr_card) == 0)
		{
			// card cautat a fost identificat in lista offset_tabela
			return &(temp->card);
		}

		temp = temp->next;
	}

	return NULL; // temp este NULL, deci nu exista card bancar cu nr cautat in parametrii functiei
}

Nod* cautare_HT_titular(Nod** tabela, unsigned char dim_tabela, char* titular)
{
	Nod* lista_carduri = NULL; //lista cu date card avand acelasi titular
	Nod* temp; //nod temporar utilizat la parsarea unei liste 
	if (tabela)
	{
		for (unsigned char i = 0; i < dim_tabela; i++) //se traverseaza vectorul de liste simple
		{
			temp = tabela[i]; //temp se initializeaza cu adresa primului nod din lista tabela[i]
			while (temp != NULL) //lista i se traverseaza in intregime
			{
				if (strcmp(temp->card.titular, titular) == 0) //verifica daca titular este in nodul temp
				{
					lista_carduri = inserare_sfarsit(lista_carduri, temp->card); //inserare card bancar in lista rezultat
				}
				temp = temp->next; //acces la nodul succesor al lui temp
			}
		}
	}
	return lista_carduri; //se returneaza adresa primului nod care va contine cardurile bancare avand acelasi titular
}

Nod** dezalocare_HT(Nod** tabela, unsigned char dim_tabela)
{
	Nod* temp;
	if (tabela)
	{
		for (unsigned char i = 0; i < dim_tabela; i++)
		{
			while (tabela[i])
			{
				temp = tabela[i];
				tabela[i] = tabela[i]->next;
				free(temp->card.titular);
				free(temp);
			}
		}

		free(tabela);
		tabela = NULL;
	}
	return tabela;
}

void stergere_dupa_cheie(Nod** tabela, unsigned char dim_tabela, char* cheie)
{
	unsigned int offset = functie_hash(cheie, dim_tabela);
	Nod* lista = tabela[offset];
	Nod* temp = lista;
	Nod* prev = NULL;
	while (temp)
	{
		if (strcmp(temp->card.nr_card, cheie) == 0)
		{
			if (prev == NULL)
			{
				tabela[offset] = tabela[offset]->next;
				free(temp->card.titular);
				free(temp);
				return;
			}
			else
			{
				prev->next = temp->next;
				free(temp->card.titular);
				free(temp);
				return;
			}
		}
		prev = temp;
		temp = temp->next;
	}
}

int main()
{
	Nod** HT = malloc(DIM_TABELA_DISPERSIE * sizeof(Nod*)); // vector cu elemente de tip Nod* (adrese de inceput de liste simple)

	for (unsigned char i = 0; i < DIM_TABELA_DISPERSIE; i++)
	{
		HT[i] = NULL; // HT[i] adresa de inceput a listei simple i
	}
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	char buffer[200];
	CardBancar card;

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

		// inserare card bancar in tabela de dispersie implementata cu chaining
		unsigned char offset_inserare = inserare_HT(HT, DIM_TABELA_DISPERSIE, card);

		printf("Lista simpla unde a avut loc inserarea cardului %s: %u\n", card.nr_card, offset_inserare);

		fgets(buffer, sizeof(buffer), f);
	}
	fclose(f);

	CardBancar* pCard = NULL;
	pCard = cautare_HT(HT, DIM_TABELA_DISPERSIE, "7777888800005643");

	if (pCard != NULL)
	{
		printf("Cardul a fost identificat in tabela de dispersie: %s %s\n", pCard->nr_card, pCard->titular);
	}
	else
	{
		printf("Cardul bancar nu a fost identificat in tabela de dispersie!\n");
	}


	// stergere card bancar pe baza de cheie

	Nod* lista_carduri = cautare_HT_titular(HT, DIM_TABELA_DISPERSIE, "Ionescu Marian");
	Nod* temp = lista_carduri;
	printf("\n\nCarduri cu acelasi titular: \n");
	while (temp)
	{
		printf("\nNumele: %s\nNr Card: %s\n", temp->card.titular, temp->card.nr_card);
		temp = temp->next;
	}

	stergere_dupa_cheie(HT, DIM_TABELA_DISPERSIE, "4720098769018080");
	pCard = cautare_HT(HT, DIM_TABELA_DISPERSIE, "4720098769018080");
	printf("\n\n----Stergere card bancar dupa cheie----\n");
	if (pCard != NULL)
	{
		printf("Cardul a fost identificat in tabela de dispersie: %s %s\n", pCard->nr_card, pCard->titular);
	}
	else
	{
		printf("Cardul bancar nu a fost identificat in tabela de dispersie!\n");
	}

	// dezalocare tabela de dispersie
	HT = dezalocare_HT(HT, DIM_TABELA_DISPERSIE);
	//dezalocare lista carduri ( deoarece variabila lista_carduri este reutilizata pentru stocarea datelor de card cu acelasi titular)
	temp = lista_carduri;
	while (lista_carduri)
	{
		temp = lista_carduri;
		lista_carduri = lista_carduri->next;
		
		//free(temp->card.titular);
		//titularul este deja dezalocat prin functia dezalocare_HT

		free(temp);
	}

	lista_carduri = cautare_HT_titular(HT, DIM_TABELA_DISPERSIE, "Ionescu Marian");
	temp = lista_carduri;
	printf("\n\nCarduri cu acelasi titular DUPA dezalocare tabela de dispersie: \n");
	while (temp)
	{
		printf("\nNumele: %s\nNr Card: %s\n", temp->card.titular, temp->card.nr_card);
		temp = temp->next;
	}
}