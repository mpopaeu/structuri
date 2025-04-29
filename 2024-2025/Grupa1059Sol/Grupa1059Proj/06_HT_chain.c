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
CardBancar* catuare_card(Nod** tabela, unsigned char tabela_length, char* nr_card)
{
	unsigned char offset = functie_hash(nr_card, tabela_length);//se cauta dupa cheie de cautare
	if (tabela != NULL)//tabela exista(este alocata in memeorie heap)
	{
		Nod* temp = tabela[offset];//se acceseaza lista care ar trebui sa contina datele pt nr_card cautat
		while (temp != NULL)//se verifica prezenta nr card in lista tabel de offset
		{
			if (strcmp(temp->card.nr_card, nr_card) == 0)
			{
				return &(temp->card);
			}
			temp = temp->next;
		}
	}
	return NULL;
}
// stergere card bancar din tabela hash pe baza de cheie (nr_card)
void stergere_card(Nod** tabela, unsigned char tabela_length, char* nr_card)
{
	unsigned char offset = functie_hash(nr_card, tabela_length);//se cauta dupa cheie de cautare
	if (tabela != NULL)//tabela exista(este alocata in memeorie heap)
	{
		Nod* temp = tabela[offset];//se acceseaza lista care ar trebui sa contina datele pt nr_card cautat

		if (strcmp(temp->card.nr_card, nr_card) == 0)
		{
			tabela[offset] = temp->next;//modificare adresa de incaput a listei tabela[offset]
			free(temp->card.detinator);
			free(temp);//dezalocare nod
			return;
		}
	
		Nod* prev = temp;
		temp = temp->next;
		while (temp != NULL)//se verifica prezenta nr card in lista tabel de offset
		{
			if (strcmp(temp->card.nr_card, nr_card) == 0)
			{
				prev->next = temp->next;
				free(temp->card.detinator);
				free(temp);
				return;
			}
			prev = temp;
			temp = temp->next;
		}
	}
}
// dezalocare tabela de dispersie

float sold_mediu(Nod** tabela, unsigned char tabela_length, char* moneda)
{
	float suma = 0;
	unsigned int contor = 0;
	for (int i = 0; i < tabela_length; i++)//se traverseaza toate elem din vectorul de liste(moneda nu este cheie)
	{
		Nod* temp = tabela[i];//suntem pe lista i;se salveaza primul nod din lista i in temp
		while (temp != NULL)//se traverseaza toate nodurile din lista i
		{
			if (strcmp(temp->card.moneda, moneda) == 0)//se compara moneda cautata cu moneda stocata in nodul temp
			{
				suma += temp->card.sold;//se adauga soldul la suma temporara
				contor++;//se incrementaza nr de carduri cu moneda cautata
			}
			temp = temp->next;//se acceseaza nodul succesor din lista i
		}
	}
	if (suma == 0 && contor == 0)
		return -1;//cazul in care nu se gaseste niciun card cun moneda cautata
	else
		return suma /contor;//se calculeaza soldul mediu pe cardurile cu aceeasi moneda
}

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

	float medie = sold_mediu(HT, TABELA_HASH_LENGTH, "RON");
	if (medie == -1)
		printf("Nu a fost gasit niciun card cu moneda cautata\n");
	else
		printf("soldul mediu: %.2f\n", medie);

	CardBancar* c = catuare_card(HT, TABELA_HASH_LENGTH, "6413889977660001");
	if (c == NULL)
		printf("cardul nu a fost gasit\n");
	else
		printf("titularul %s, sold %f\n", c->detinator, c->sold);

	stergere_card(HT, TABELA_HASH_LENGTH, "6413889977660001");
	printf("Cautare card dupa stergere\n");
	c = catuare_card(HT, TABELA_HASH_LENGTH, "6413889977660001");
	if (c == NULL)
		printf("cardul nu a fost gasit\n");
	else
		printf("titularul %s, sold %f\n", c->detinator, c->sold);
	return 0;
}