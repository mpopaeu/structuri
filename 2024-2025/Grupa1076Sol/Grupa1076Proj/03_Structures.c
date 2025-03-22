#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define CARD_NUMBER_LENGTH 16
#define EXPIRING_DATE_FORMAT_LENGTH 5 // MM/YY
#define CARD_ARRAYS_LENGTH 20

struct BankCard
{
	char* holder; // 4 bytes
	char card_no[CARD_NUMBER_LENGTH + 1];// +1 for null terminator byte; 17 bytes
	float balance; // 4 bytes
	char exp_date[EXPIRING_DATE_FORMAT_LENGTH + 1]; // +1 for null terminator byte; 6 bytes
	char* currency; // 4 bytes
}; // 35 bytes ?! -> 40 bytes

typedef struct BankCard BankCard;

int main()
{
	BankCard v_card[CARD_ARRAYS_LENGTH];
	BankCard* p_card = NULL;
	printf("Size of the structure BankCard is = %d bytes\n", sizeof(BankCard));
	printf("Size of the array v_card is = %d bytes\n", sizeof(v_card));
	printf("Size of the pointer p_card is = %d bytes\n", sizeof(p_card));

	FILE* f = fopen("CardData.txt", "r");

	unsigned char count = 0;
	unsigned char buffer[200];
	while (fgets(buffer, sizeof(buffer), f) && count < CARD_ARRAYS_LENGTH)
	{
		char seps[] = ",\n";
		char* token = strtok(buffer, seps);
		strcpy(v_card[count].card_no, token);

		token = strtok(NULL, seps); // continue the splitting
		strcpy(v_card[count].exp_date, token);

		token = strtok(NULL, seps);
		v_card[count].holder = malloc(strlen(token) + 1);
		strcpy(v_card[count].holder, token);

		token = strtok(NULL, seps);
		v_card[count].currency = malloc(strlen(token) + 1);
		strcpy(v_card[count].currency, token);

		token = strtok(NULL, seps);
		v_card[count].balance = (float)atof(token);

		count += 1; // the next offset to be considered for the next line in the text file
	}

	fclose(f);

	printf("Card data from v_card array:\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", v_card[i].card_no, v_card[i].holder);
	}

	p_card = v_card;
	printf("\nCard data from v_card array by using p_card pointer:\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", p_card[i].card_no, p_card[i].holder);
	}

	p_card = malloc(count * sizeof(BankCard));
	for (unsigned char i = 0; i < count; i++)
	{
		p_card[i] = v_card[i]; // v_card and p_card share the same heap mem areas for holder and currency
		// create separate hep mem locations for p_card
		p_card[i].holder = malloc(strlen(v_card[i].holder) + 1);
		strcpy(p_card[i].holder, v_card[i].holder);
		p_card[i].currency = malloc(strlen(v_card[i].currency) + 1);
		strcpy(p_card[i].currency, v_card[i].currency);
	}

	printf("\nCard data from p_card array in heap mem:\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", p_card[i].card_no, p_card[i].holder);
	}

	v_card[0].holder[0] = 'X';
	printf("\nArrays after changing the holder's first letter of the first item\n");
	printf("Card data from v_card array after change:\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", v_card[i].card_no, v_card[i].holder);
	}
	printf("\nCard data from p_card array in heap mem after change:\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", p_card[i].card_no, p_card[i].holder);
	}

	// deallocations of arrays
	// v_card allocated on stack seg
	for (unsigned char i = 0; i < count; i++)
	{
		free(v_card[i].holder);
		free(v_card[i].currency);
	}

	// p_card allocated onm heap seg
	// step 1: deallocate holder and currency
	for (unsigned char i = 0; i < count; i++)
	{
		free(p_card[i].holder);
		free(p_card[i].currency);
	}
	// step 2: deallocate the array of cards
	free(p_card);


	return 0;
}