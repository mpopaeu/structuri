#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define CARD_NO_LENGTH 16
#define MONEDA_COD_LENGTH 3
#define TABELA_HASH_LENGTH 50

struct CardBancar
{
	char nr_card[CARD_NO_LENGTH + 1];
	char* detinator;
	char expira_la[6];
	float sold;
	char moneda[MONEDA_COD_LENGTH + 1];
};

typedef struct CardBancar CardBancar;

unsigned char functie_hash(char* cheie, unsigned char tabela_length)
{
	// unsigned int nr_card_integer = atoi(cheie); // conversie string nr_card in intregul numar card
	unsigned int suma_card = 0;
	for (unsigned char i = 0; i < CARD_NO_LENGTH; i++)
		suma_card += cheie[i];

	return (suma_card % tabela_length); // impartire cu rest la dimensiune tabela de dispersie
}

struct Nod
{
	CardBancar card;
	struct Nod* next;
};
typedef struct Nod Nod;

// functie de inserare nod la inceputul listei simple
Nod* inserare_inceput(Nod* lista, CardBancar data)
{
	Nod* nou = malloc(sizeof(Nod)); // alocare nod nou pentru preluarea datelor din param data
	nou->card = data; // salvare date din data (card bancar) in Nod nou
	nou->next = lista; // succesorului lui nou va fi actual inceput de lista simpla (lista)

	return nou; // se returneaza noua adresa de inceput
}

unsigned char inserare_HT(Nod** tabela, CardBancar data, unsigned char tabela_length)
{
	// inserare date card bancar (data) in tabela de dispersie cu chaining
	unsigned char offset_hash = functie_hash(data.nr_card, tabela_length);

	// inserare card bancar (data) in tabela hash pe offset calculat in offset_hash
	tabela[offset_hash] = inserare_inceput(tabela[offset_hash], data);

	return offset_hash; // offset pe care a avut loc inserare un tabela hash
}

// cautare card bancar in functie de cheie (nr_card)

// stergere card bancar din tabela hash pe baza de cheie (nr_card)

// dezalocare tabela de dispersie

int main()
{
	Nod** HT = NULL;

	HT = malloc(sizeof(Nod*) * TABELA_HASH_LENGTH); // tabela hash cu maxim 50 de liste simple
					// fiecare element din tabela (vector) este de tip Nod* (adresa de inceput de lista simpla
	
	for (unsigned char i = 0; i < TABELA_HASH_LENGTH; i++)
		HT[i] = NULL; // HT[i] adresa de inceput a listei i din vectorul HT

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

		// inserare date card bancar (card) in tabela de dispersie
		unsigned char offset_inserare = inserare_HT(HT, card, TABELA_HASH_LENGTH);

		printf("Card bancar %s inserat in lista simpla %u\n", card.nr_card, offset_inserare);

		fscanf(f, "%[^,],%[^,],%[^,],%f,%[^\n]", card.nr_card, titular,
			card.expira_la, &(card.sold), card.moneda); // citire nr card de pe linia urmatoare
	}
	fclose(f);


	return 0;
}