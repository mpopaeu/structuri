#include <stdio.h>
#include <malloc.h>
#include <string.h>

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

struct NodD
{
	CardBancar card;
	struct NodD* next, *prev;
};
typedef struct NodD NodD;


struct ListaDubla
{
	NodD* prim, * ultim; // adrese catre primul, respectiv ultimul nod din lista dubla
};

typedef struct ListaDubla ListaDubla;

// functie de inserare nod la inceputul listei duble
ListaDubla inserare_inceput(ListaDubla lista, CardBancar data)
{
	NodD* nou = malloc(sizeof(NodD));
	nou->card = data; // salvare date din card bancar
	nou->prev = NULL; // predecesor obligatoriu NULL
	nou->next = lista.prim; // succesor obligatoriu actual inceput de lista dubla

	if (lista.prim == NULL)
	{
		// nu exista noduri in lista dubla
		lista.ultim = nou;
	}
	else
	{
		// exista cel putin un nod in lista dubla
		// se actualizeaza actual predecesor pentru primul nod din lista dubla
		lista.prim->prev = nou;
	}
	lista.prim = nou;

	return lista;
}

// functie de traversare lista dubla
void traversare_listadubla(ListaDubla lista)
{
	NodD* temp = lista.prim;
	printf("\nTraversare prim->ultim:\n");
	while (temp != NULL)
	{
		printf("%s %s\n", temp->card.nr_card, temp->card.detinator);
		temp = temp->next;
	}

	temp = lista.ultim;
	printf("\n\nTraversare ultim->prim:\n");
	while (temp != NULL)
	{
		printf("%s %s\n", temp->card.nr_card, temp->card.detinator);
		temp = temp->prev;
	}
}

// functie de stergere nod la sfarsitul listei duble
ListaDubla stergere_sfarsit(ListaDubla lista)
{

}

// functie de stergere a nodurilor cu acelasi detinator de card bancar

// functie de sortare a nodurilor din lista dubla (sold card bancar)

// functie de intreschimbare doua noduri adiacente in lista dubla

int main()
{
	FILE* f; // pointer la structura FILE (handler de fisier)
	ListaDubla listaD; // variabila de acces la capetele unei liste duble
	listaD.prim = NULL;
	listaD.ultim = NULL;

	f = fopen("CarduriBancare.txt", "r");

	char titular[150];
	CardBancar card;
	fscanf(f, "%[^,],%[^,],%[^,],%f,%[^\n]", card.nr_card, titular,
		card.expira_la, &(card.sold), card.moneda);
	while (!feof(f)) // 1. conditie aplicata dupa o incercare de a citi nr card bancar
	{
		card.detinator = malloc(strlen(titular) + 1); // +1 pt terminatorul de string (byte 0x00)
		strcpy(card.detinator, titular); // copiere string nume detinator in variabila temporara card

		fscanf(f, "\n");

		// inserare in lista simpla card bancar "pregatit" in variabila temporara card
		listaD = inserare_inceput(listaD, card);

		fscanf(f, "%[^,],%[^,],%[^,],%f,%[^\n]", card.nr_card, titular,
			card.expira_la, &(card.sold), card.moneda); // citire nr card de pe linia urmatoare
	}
	fclose(f);
	printf("Lista dubla dupa creare:\n");
	traversare_listadubla(listaD);

	// stergere nod la sfarsitul listei duble
	listaD = stergere_sfarsit(listaD);

	printf("\n\nLista dubla dupa stergerea ultimului nod:\n");
	traversare_listadubla(listaD);

	// dezalocare structura lista dubla
	while (listaD.prim != NULL)
	{
		listaD = stergere_sfarsit(listaD);
	}

	printf("\n\nLista dubla dupa dezalocarea:\n");
	traversare_listadubla(listaD);

	return 0;
}
