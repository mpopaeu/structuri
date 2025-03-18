#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define DIM_CARD_BANCAR 16
#define DIM_DATA_EXPIRARE 7
#define DIM_MONEDA 3
#define DIM_VECTOR_CARDBANCAR 25

struct CardBancar
{
	char nr_card[DIM_CARD_BANCAR + 1]; // +1 pentru terminator string; 20 bytes (17 + 3 padding)
	char* titular; // 4 bytes
	char data_expirare[DIM_DATA_EXPIRARE + 1]; // +1 pentru terminator string; 12 bytes (9 + 3 padding) 
	float sold; // 4 bytes
	char moneda[DIM_MONEDA + 1]; // cod moneda; 4 bytes (no padding)
};

typedef struct CardBancar CardBancar;

int main()
{
	CardBancar v_card[DIM_VECTOR_CARDBANCAR];
	CardBancar* pv_card = NULL;
	printf("Dimensiune structura CardBancar = %d bytes\n", sizeof(CardBancar));
	printf("Dimensiune vector v_card = %d bytes\n", sizeof(v_card));
	printf("Dimensiune pointer pv_card = %d bytes\n", sizeof(pv_card));

	// preluare date din fisiere pentru carduri bancare
	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	char buffer[150];
	char sep[] = ";\n";
	unsigned char count = 0; // nr efectiv de elemente din vector
	fgets(buffer, sizeof(buffer), f);

	while (!feof(f) && count < DIM_VECTOR_CARDBANCAR)
	{
		char* token = NULL;
		token = strtok(buffer, sep);
		strcpy(v_card[count].nr_card, token);

		token = strtok(NULL, sep);
		v_card[count].titular = malloc(strlen(token) + 1);
		strcpy(v_card[count].titular, token);

		token = strtok(NULL, sep);
		strcpy(v_card[count].data_expirare, token);

		token = strtok(NULL, sep);
		v_card[count].sold = (float)atof(token);

		token = strtok(NULL, sep);
		strcpy(v_card[count].moneda, token);

		// incrementare counter (pozitie curenta in vector)
		count += 1;
		// incercare preluare linie urmatoare (daca exista)
		fgets(buffer, sizeof(buffer), f);
	}

	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", v_card[i].nr_card, v_card[i].titular);
	}

	pv_card = v_card;
	printf("\n\nCarduri bancare stocate in stack (v_card)\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", pv_card[i].nr_card, pv_card[i].titular);
	}


	pv_card = malloc(count * sizeof(CardBancar));

	for (unsigned char i = 0; i < count; i++)
	{
		pv_card[i] = v_card[i]; // partajare titulat intre pv_card[i] si v_card[i]

		// separare zone de heap pentru titular (eliminare partajare)
		pv_card[i].titular = malloc(strlen(v_card[i].titular) + 1);
		strcpy(pv_card[i].titular, v_card[i].titular);
	}
	printf("\n\nCarduri bancare stocate in heap (pv_card)\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", pv_card[i].nr_card, pv_card[i].titular);
	}

	// dezalocare titulari vector stack v_card
	for (unsigned char i = 0; i < count; i++)
		free(v_card[i].titular);

	// dezalocare vector pv_card
	// pasul 1: dezalocare titulari
	for (unsigned char i = 0; i < count; i++)
		free(pv_card[i].titular);
	// pasul 2: dezalocare vector acrduri bancare
	free(pv_card);


	fclose(f);

	return 0;
}