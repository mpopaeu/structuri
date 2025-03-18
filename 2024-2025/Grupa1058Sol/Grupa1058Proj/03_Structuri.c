#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define DIM_NR_CARD 16
#define DIM_DATA_EXPIRARE 5
#define NR_ELEMENTE_VECTOR 30

struct CardBancar
{
	char* titular; // 4 bytes
	char nr_card[DIM_NR_CARD + 1]; // +1 pt byte terminator de string; 20 bytes (17 + 3 padding)
	float sold; // 4 bytes
	char* emitent; // 4 bytes
	char data_expirare[DIM_DATA_EXPIRARE + 1]; // LL/AA; 8 bytes (6 + 2 padding)
};

typedef struct CardBancar CardBancar;

int main()
{
	CardBancar v_card[NR_ELEMENTE_VECTOR];
	CardBancar *pv_card = NULL;

	printf("Dimensiune vector v_card = %d\n", sizeof(v_card));
	printf("Dimensiune structura CardBancar= %d\n", sizeof(CardBancar));
	printf("Dimensiune pointer pv_card = %d\n", sizeof(pv_card));

	// exemplu de populare a vectorului v_card cu date din fisier

	FILE* f = NULL;
	f = fopen("CarduriBancare.txt", "r");

	unsigned char count = 0; // nr efectiv de elemente din vectorul v_card
	char temp_buff[100]; // buffer temporar pentru stocare linii preluate din fisier text
	fgets(temp_buff, sizeof(temp_buff), f);

	while (!feof(f) && count < NR_ELEMENTE_VECTOR) // exista card bancar de preluat SI vectorul are spatiu pt stocarea sa
	{
		strtok(temp_buff, "\n");
		v_card[count].titular = malloc(strlen(temp_buff) + 1); // alocare mem heap titular element count
		strcpy(v_card[count].titular, temp_buff); // copiere continut titular din buffer in vector pe element count

		fgets(temp_buff, sizeof(temp_buff), f);
		strtok(temp_buff, "\n");
		strcpy(v_card[count].nr_card, temp_buff);

		fgets(temp_buff, sizeof(temp_buff), f);
		strtok(temp_buff, "\n");
		v_card[count].sold = (float)atof(temp_buff); // conversie ASCII-to-Binary pentru float

		fgets(temp_buff, sizeof(temp_buff), f);
		strtok(temp_buff, "\n");
		v_card[count].emitent = malloc(strlen(temp_buff) + 1); // alocare mem heap pentru emitent element count
		strcpy(v_card[count].emitent, temp_buff); // copiere emitent din buffer in emitent element count din vector

		fgets(temp_buff, sizeof(temp_buff), f);
		strtok(temp_buff, "\n");
		strcpy(v_card[count].data_expirare, temp_buff);

		// incrementare element curent in vector
		count += 1;
		// incercare preluare titular card urmator
		fgets(temp_buff, sizeof(temp_buff), f);
	}

	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", v_card[i].titular, v_card[i].nr_card);
	}
	printf("\n\n");
	pv_card = v_card;
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", pv_card[i].titular, pv_card[i].nr_card); // aceleasi locatii ca v_card
	}

	// pv_card alocat in mem heap
	pv_card = malloc(count * sizeof(CardBancar));
	for (unsigned char i = 0; i < count; i++)
	{
		pv_card[i] = v_card[i]; // temporar asumata partajarea de zone heap pentru titular si emitent
		
		// alocare si populare zone separate de heap pentru titular si emitent
		pv_card[i].titular = malloc(strlen(v_card[i].titular) + 1);
		strcpy(pv_card[i].titular, v_card[i].titular);

		pv_card[i].emitent = malloc(strlen(v_card[i].emitent) + 1);
		strcpy(pv_card[i].emitent, v_card[i].emitent);
	}

	printf("\n\nCarduri bancare stocate in heap\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", pv_card[i].titular, pv_card[i].nr_card); // aceleasi locatii ca v_card
	}

	// dezalocare vectori de structuri CardBancar
	for (unsigned char i = 0; i < count; i++)
	{
		free(v_card[i].titular);
		free(v_card[i].emitent);
	}

	// pasul 1: dezalocarea zonelor cele mai indepartate (string-uri titular si emitent)
	for (unsigned char i = 0; i < count; i++)
	{
		free(pv_card[i].titular);
		free(pv_card[i].emitent);
	}
	//pasul 2: dezalocare vectorului de elemente CardBancar
	free(pv_card);

	fclose(f);
	return 0;
}

