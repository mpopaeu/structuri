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

struct Nod
{
	CardBancar card;
	struct Nod* next;
};
typedef struct Nod Nod;


// operatii de baza liste simple: inserare nod inceput, inserare nod sfarsit, stergere nod sfarsit, stergere nod din interior

// functie de inserare nod la inceputul listei simple
Nod* inserare_inceput(Nod* lista, CardBancar data)
{
	Nod* nou = malloc(sizeof(Nod)); // alocare nod nou pentru preluarea datelor din param data
	nou->card = data; // salvare date din data (card bancar) in Nod nou
	nou->next = lista; // succesorului lui nou va fi actual inceput de lista simpla (lista)

	return nou; // se returneaza noua adresa de inceput
}

// functie de traversare lista simpla
void traversare_listasimpla(Nod* lista)
{
	Nod* temp = lista;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->card.nr_card, temp->card.detinator);
		
		temp = temp->next; // actualizare pointer temp catre succesor al actualului temp
	}
}

// functie de stergere nod la sfarsitul listei simple
Nod* stergere_sfarsit(Nod* lista)
{
	if (lista->next == NULL)
	{
		// lista simpla contine 1 singur nod
		free(lista->card.detinator); //dezalocare pointer detinator din card bancar
		free(lista); // dezalocarea primului si unicului nod din lista simpla
		lista = NULL;
	}
	else
	{
		Nod* pred, * temp;
		pred = lista; // pred primul nod din lista
		temp = lista->next; // temp nodul 2 din lista
		while (temp->next != NULL) // exista nod succesor pt temp; temp nu este ultimul nod din lista
		{
			pred = temp;
			temp = temp->next;
		}

		// temp este ultimul nod, pred este penultimul nod
		free(temp->card.detinator);
		free(temp);

		pred->next = NULL;
	}

	return lista;
}


int main()
{
	FILE* f; // pointer la structura FILE (handler de fisier)
	Nod* prim = NULL; // initializare lista simpla cu NULL -> lista empty (0 noduri)

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
		prim = inserare_inceput(prim, card);

		fscanf(f, "%[^,],%[^,],%[^,],%f,%[^\n]", card.nr_card, titular,
			card.expira_la, &(card.sold), card.moneda); // citire nr card de pe linia urmatoare
	}
	fclose(f);
	printf("Lista simpla dupa creare:\n");
	traversare_listasimpla(prim);
	// stergere nod la sfarsitul listei simple
	prim = stergere_sfarsit(prim);
	printf("\n\nLista simpla dupa stergerea ultimului nod:\n");
	traversare_listasimpla(prim);

	// dezalocare structura lista simpla
	while (prim != NULL)
	{
		prim = stergere_sfarsit(prim);
	}

	printf("\n\nLista simpla dupa dezalocarea listei simple:\n");
	traversare_listasimpla(prim);

	return 0;
}
