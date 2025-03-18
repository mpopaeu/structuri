#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define NR_CIFRE_CARD 16
#define DIM_MONEDA 3
#define DIM_VECTOR_CARDBANCAR 27

struct DataExpirare
{
	unsigned short int anul;
	unsigned char luna;
};

typedef struct DataExpirare DataExpirare;

struct CardBancar
{
	char nr_card[NR_CIFRE_CARD + 1]; // +1 pentru terminatot de string util in cazul utilizarii ca string
	char* titular;
	DataExpirare data;
	float sold;
	char moneda[DIM_MONEDA + 1]; // RON, EUR, USD
};

typedef struct CardBancar CardBancar;

int main()
{
	CardBancar v_card[DIM_VECTOR_CARDBANCAR];
	CardBancar* pv_card = NULL;

	printf("Dimensiune vector v_card = %d\n", sizeof(v_card));
	printf("Dimensiune pointer v_card = %d\n", sizeof(pv_card));
	printf("Dimensiune structura CardBancar = %d\n", sizeof(CardBancar));
	printf("Dimensiune structura DataExpirare = %d\n", sizeof(DataExpirare));

	FILE* f = NULL;

	f = fopen("CarduriBancare.txt", "r");
	// secventa de parsare a fisierului .txt si incarcarea datelor in vectorul v_card
	unsigned char i = 0;

	char buffer[200];
	fgets(buffer, sizeof(buffer), f);

	while (!feof(f) && i < DIM_VECTOR_CARDBANCAR)
	{
		buffer[sizeof(v_card[i].nr_card) - 1] = 0;
		strtok(buffer, "\n");
		strcpy(v_card[i].nr_card, buffer);

		fgets(buffer, sizeof(buffer), f);
		strtok(buffer, "\n");
		v_card[i].titular = malloc(strlen(buffer) + 1); // +1 terminator de string
		strcpy(v_card[i].titular, buffer);

		fgets(buffer, sizeof(buffer), f);
		strtok(buffer, "\n");
		sscanf(buffer, "%hu%hhu", &v_card[i].data.anul, &v_card[i].data.luna);
		
		fgets(buffer, sizeof(buffer), f);
		strtok(buffer, "\n");
		v_card[i].sold = (float)atof(buffer);

		fgets(buffer, sizeof(buffer), f);
		strtok(buffer, "\n");
		strcpy(v_card[i].moneda, buffer);

		i += 1;
		fgets(buffer, sizeof(buffer), f);
	}

	unsigned char vector_size = i;

	for (i = 0; i < vector_size; i++)
	{
		printf("%s %s\n", v_card[i].nr_card, v_card[i].titular);
	}


	pv_card = v_card;

	pv_card = malloc(vector_size * sizeof(CardBancar));

	for (i = 0; i < vector_size; i++)
	{
		pv_card[i] = v_card[i]; // partajare temporara mem heap pt titular pt a copia toate elementele din v_card[i]
		// separare titular pe cele doua structuri prin alocare mem heap aferenta titularului din pv_card[i]
		pv_card[i].titular = malloc(strlen(v_card[i].titular) + 1);
		strcpy(pv_card[i].titular, v_card[i].titular);
	}

	// prelucrarea date carduri bancare

	//dezalocare pv_card
	for (i = 0; i < vector_size; i++)
	{
		free(pv_card[i].titular);
	}
	free(pv_card);

	for (i = 0; i < vector_size; i++)
	{
		free(v_card[i].titular);
	}

	// Liste simple: inserare nod in interior, stergere nod sfarsit lista simpla

	fclose(f);
}