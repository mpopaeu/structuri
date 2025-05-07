#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define DIM_CARD_BANCAR 16
#define DIM_DATA_EXPIRARE 7
#define DIM_MONEDA 3
#define DIM_TABELA_HASH 39


struct CardBancar
{
	char nr_card[DIM_CARD_BANCAR + 1]; 
	char* titular; 
	char data_expirare[DIM_DATA_EXPIRARE + 1]; 
	float sold; 
	char moneda[DIM_MONEDA + 1]; 
};

typedef struct CardBancar CardBancar;

struct Nod
{
	CardBancar cb;
	struct Nod* next;
};

typedef struct Nod Nod;

unsigned char functie_hash(char* cheie, unsigned char dim_tabela)
{
	unsigned int suma_ascii = 0;
	for (unsigned char i = 0; i < strlen(cheie); i++)
		suma_ascii += cheie[i];

	return (suma_ascii % dim_tabela);
}

Nod* inserare_inceput(Nod* lista, CardBancar data)
{
	Nod* nou = malloc(sizeof(Nod)); // alocare nod lista simpla

	nou->cb = data;
	nou->next = lista; // actualizare inceput de lista

	return nou; // returnare nou inceput de lista
}

unsigned char inserare_HT(Nod** tabela, unsigned char dim_tabela, CardBancar data)
{
	// 1. determinare offset pt lista simpla in care se insereaza data
	unsigned char offset_inserare = functie_hash(data.nr_card, dim_tabela);

	// 2. inserare data in lista simpla
	tabela[offset_inserare] = inserare_inceput(tabela[offset_inserare], data);

	return offset_inserare;
}


CardBancar* cautare_HT(Nod** tabela, unsigned char dim_tabela, char* cheie)
{
	unsigned char offset_lista = functie_hash(cheie, dim_tabela);

	Nod* temp = tabela[offset_lista];
	while (temp != NULL)
	{

		if (strcmp(cheie, temp->cb.nr_card) == 0)
		{
			return &(temp->cb); // card bancar returnat ca adresa de heap; cheia (nr_card) este unica
		}

		temp = temp->next;
	}

	return NULL; // cardul bancar nu a fost gasit in tabela de dispersie
}


void stergere_card_HT(Nod** tabela, unsigned char dim_tabela, char* cheie)
{
	unsigned char offset_lista = functie_hash(cheie, dim_tabela);

	if (tabela[offset_lista] != NULL)
	{
		// lista de pe offset_lista contine cel putin 1 nod
		Nod* temp = tabela[offset_lista];
		Nod* prev = NULL;
		while (temp != NULL)
		{
			if (strcmp(temp->cb.nr_card, cheie) == 0)
			{
				if (prev == NULL)
				{
					// se sterge primul nod din lista tabela[offset_lista]
					tabela[offset_lista] = temp->next; // actualizare inceput de lista tabela [offset_lista]
				}
				else
				{
					// se sterge nod la interior lista (inclusiv ultimul nod)
					prev->next = temp->next; // actualizare legatura predecesor al lui temp catre succesor al lui temp
				}
				free(temp->cb.titular);		// dezalocare extensie titular pentru date card bancar stocate de temp
				free(temp);					// dezalocare nod lista simpla

				return;		// nu are sens cautarea unui alt nod cu acelasi nr de card 
			}
			
			temp = temp->next;
		}
	}
}

// cautare carduri bancare care au aceeasi moneda
// cardurile de salveaza intr-un vector
CardBancar** cautare_card_moneda(Nod** tabela, unsigned char dim, char* moneda, unsigned char* nr)
{
	*nr = 0;
	for (int i = 0; i < dim; i++)	//calcul nr de carduri bancare cu aceeasi moneda
	{
		Nod* temp = tabela[i];
		while (temp != NULL)
		{
			if (strcmp(moneda, temp->cb.moneda) == 0)
				(*nr)++;		//incrementare counter carduri bancare cu aceeasi moneda
			temp = temp->next;
		}

	}
	CardBancar** carduri = malloc(*nr * sizeof(CardBancar*));	//alocare memorie heap pt vector cu counter determinat mai sus
	int j = 0;		//offset curent pentru stocare cardBancar in vector
	for (int i = 0; i < dim; i++)
	{
		Nod* temp = tabela[i];
		while (temp != NULL)
		{
			if (strcmp(moneda, temp->cb.moneda) == 0)
			{
				carduri[j] = &(temp->cb);	//scriere adresa card bancar in vector; vectorul si tabela Hash partajeaza memorie heap pt titular
				j++;
			}
			temp = temp->next;
		}

	}
	return carduri;
}


int main()
{
	// preluare date din fisiere pentru carduri bancare
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	CardBancar card;
	Nod* *HT = NULL; // vector alocat la runtime de pointeri la liste simple
	HT = malloc(DIM_TABELA_HASH * sizeof(Nod*)); // alocare heap pt vector HT
	for (unsigned char i = 0; i < DIM_TABELA_HASH; i++)
		HT[i] = NULL;	// HT[i] este lista simpla pe offset i in vector HT


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

		// inserare card in tabela de dispersie cu chaining
		unsigned char pozitie_tabela = inserare_HT(HT, DIM_TABELA_HASH, card);

		printf("Inserare card %s in lista %u\n", card.nr_card, pozitie_tabela);

		// incercare preluare linie urmatoare (daca exista)
		fgets(buffer, sizeof(buffer), f);
	}
	fclose(f);

	printf("Cautare card bancar in tabela de dispersie pe baza de cheie -> nr card\n");
	CardBancar* pCard = cautare_HT(HT, DIM_TABELA_HASH, "6453000010109999");
	if (pCard != NULL)
	{
		printf("Card bancar identificat: %s %s\n", pCard->nr_card, pCard->titular);
	}
	else
	{
		printf("Cardul bancar nu este prezent in tabela de dispersie!\n");
	}

	// stergere card bancar din tabela de dispersie
	printf("Stergere card bancar in tabela de dispersie pe baza de cheie -> nr card\n");
	stergere_card_HT(HT, DIM_TABELA_HASH, "6453000010109999");

	printf("Cautare card bancar in tabela de dispersie dupa operatia de stergere:\n");
	pCard = cautare_HT(HT, DIM_TABELA_HASH, "6453000010109999");
	if (pCard != NULL)
	{
		printf("Card bancar identificat: %s %s\n", pCard->nr_card, pCard->titular);
	}
	else
	{
		printf("Cardul bancar nu este prezent in tabela de dispersie!\n");
	}

	unsigned char nr;
	CardBancar** carduri = cautare_card_moneda(HT, DIM_TABELA_HASH, "RON", &nr);
	printf("\nCarduri bancare din vector\n");
	for (int i = 0; i < nr; i++)
	{
		printf("%s %s\n", carduri[i]->nr_card, carduri[i]->moneda);
	}


	//dezalocare tabela hash
	for (int i = 0; i < DIM_TABELA_HASH; i++)
	{
		
		while (HT[i] != NULL)
		{
			Nod* temp = HT[i];		//temp este primul nod din lista
			HT[i] = HT[i]->next;	//noul inceput de lista este nodul 2
			free(temp->cb.titular);
			free(temp);
		}
	}
	free(HT);		//dezalocare vector de liste
	
	//dezalocare vector
	free(carduri);	//titularii cardurilor bancare au fost dezalocati anterior in secventa dezalocare tabela hash
	return 0;
}