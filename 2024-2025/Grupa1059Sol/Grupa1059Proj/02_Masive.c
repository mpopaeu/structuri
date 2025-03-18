#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define CARD_NO_LENGTH 16
#define MONEDA_COD_LENGTH 3
#define VECTOR_LENGTH 20

struct CardBancar
{
	char nr_card[CARD_NO_LENGTH + 1]; //  +1 pt terminator de string (char[])
	char* detinator;
	char expira_la[6];
	float sold;
	char moneda[MONEDA_COD_LENGTH + 1];
};

typedef struct CardBancar CardBancar;

int main()
{
	CardBancar v_cards[VECTOR_LENGTH];
	CardBancar* pv_cards = NULL;

	printf("Dimensiune CardBancar = %d\n", sizeof(CardBancar));
	printf("Dimensiune vector v_cards = %d\n", sizeof(v_cards));
	printf("Dimensiune pointer pv_cards = %d\n", sizeof(pv_cards));

	// preluarea datelor din fisierul CarduriBancare.txt si incarcarea acestora in vectorul v_cards

	FILE* f; // pointer la structura FILE (handler de fisier)

	f = fopen("CarduriBancare.txt", "r");

	unsigned char i = 0;
	char titular[150];
	fscanf(f, "%[^,],%[^,],%[^,],%f,%[^\n]", v_cards[i].nr_card, titular, 
									  v_cards[i].expira_la, &(v_cards[i].sold), v_cards[i].moneda);
	while (!feof(f) && i < VECTOR_LENGTH) // 1. conditie aplicata dupa o incercare de a citi nr card bancar
										  // 2. i nu poate depasi numarul maxim de elemente definit pt v_cards
	{
		//fscanf(f, "%[^,]", &titular);
		v_cards[i].detinator = malloc(strlen(titular) + 1); // +1 pt terminatorul de string (byte 0x00)
		strcpy(v_cards[i].detinator, titular); // copiere string nume detinator in vector, offset i, campul detinator

		//fscanf(f, "%[^,]s", v_cards[i].expira_la);
		//fscanf(f, "%f", &(v_cards[i].sold));
		//fscanf(f, "%[^\n]s", v_cards[i].moneda);

		i += 1; // acces la urmatorul card bancar
		fscanf(f, "\n");
		fscanf(f, "%[^,],%[^,],%[^,],%f,%[^\n]", v_cards[i].nr_card, titular,
			v_cards[i].expira_la, &(v_cards[i].sold), v_cards[i].moneda); // citire nr card de pe linia urmatoare
	}

	unsigned char vector_size = i;
	for (i = 0; i < vector_size; i++)
	{
		printf("%s %s\n", v_cards[i].nr_card, v_cards[i].detinator);
	}


	// pointer pv_cards la vectorul de carduri v_cards
	pv_cards = v_cards;
	for (i = 0; i < vector_size; i++)
	{
		printf("%s %s\n", pv_cards[i].nr_card, pv_cards[i].detinator);
	}

	pv_cards = malloc(vector_size * sizeof(CardBancar));

	for (i = 0; i < vector_size; i++)
	{
		pv_cards[i] = v_cards[i]; // temporar avem partajare de memorie heap pt detinator
		// eliminare partajare de mem heap intre doi vectori v_cards si pv_cards
		pv_cards[i].detinator = malloc(strlen(v_cards[i].detinator) + 1);
		strcpy(pv_cards[i].detinator, v_cards[i].detinator);
	}
	

	// prelucrare date de tip CardBancar

	// dezalocare vector din heap
	for (i = 0; i < vector_size; i++)
	{
		free(pv_cards[i].detinator);
	}
	free(pv_cards);
	// dezalocare stringuri detinator pentru elementele din v_cards
	for (i = 0; i < vector_size; i++)
	{
		free(v_cards[i].detinator);
	}
	fclose(f);
	return 0;
}