#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define CARD_NUMBER_SIZE 16
#define CARD_ARRAY_SIZE 20

struct Date
{
	char month; // stored as value
	char year; // stored as value; only last 2 letters are stored
};

typedef struct Date Date;

struct BankCard
{
	char* holder; // 4 bytes
	char card_no[CARD_NUMBER_SIZE +1]; // 17 bytes
	Date exp_date; // 2 bytes -> no alignment (month and year are char)
	char* issuer; // 4 bytes -> enforce alignment by adding +1 byte to card_no
	float balance; // 4 bytes
}; // 31 bytes; actual length is 32 bytes

typedef struct BankCard BankCard;

int main()
{
	printf("Size of structure BankCard = %d bytes\n", sizeof(BankCard));
	BankCard v_card[CARD_ARRAY_SIZE], * pv_card;
	printf("Size of structure BankCard = %d bytes\n", sizeof(v_card));
	printf("Size of structure BankCard = %d bytes\n", sizeof(pv_card));

	FILE* f = fopen("CardData.txt", "r");

	unsigned char count = 0;
	unsigned char buffer[200];

	fgets(buffer, sizeof(buffer), f);
	while (!feof(f) && count < CARD_ARRAY_SIZE)
	{
		char seps[] = ",/\n";
		char* token = strtok(buffer, seps);
		v_card[count].holder = malloc(strlen(token) + 1); // +1 for null byte as terminator
		strcpy(v_card[count].holder, token); // copy the string token into v_card holder's heap area

		token = strtok(NULL, seps); // get the vard number string
		strcpy(v_card[count].card_no, token);

		token = strtok(NULL, seps); // get the month
		v_card[count].exp_date.month = atoi(token); // convert string month into integer month
		token = strtok(NULL, seps); // get the year
		v_card[count].exp_date.year = atoi(token);// convert string year into integer year

		token = strtok(NULL, seps);
		v_card[count].issuer = malloc(strlen(token) + 1);
		strcpy(v_card[count].issuer, token);

		token = strtok(NULL, seps); // get the balance
		v_card[count].balance = (float)atof(token); // convert string balance into float balance

		// increase the counter
		count += 1;
		// read the next line in the text file CardData.txt
		fgets(buffer, sizeof(buffer), f);
	}

	fclose(f);

	printf("\n\nCards stored by v_card\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", v_card[i].holder, v_card[i].card_no);
	}

	pv_card = v_card;
	printf("\n\nCards stored by v_card accessed by pv_card\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", pv_card[i].holder, pv_card[i].card_no);
	}

	pv_card = malloc(count * sizeof(BankCard));
	for (unsigned char i = 0; i < count; i++)
	{
		pv_card[i] = v_card[i]; // both arrays share heap mem for holder and issuer; potential issues at deallocation and changing times
		// separate heap mem locations for holder and issuer
		pv_card[i].holder = malloc(strlen(v_card[i].holder) + 1);
		strcpy(pv_card[i].holder, v_card[i].holder);
		pv_card[i].issuer = malloc(strlen(v_card[i].issuer) + 1);
		strcpy(pv_card[i].issuer, v_card[i].issuer);
	}

	printf("\n\nCards stored in heap memory and accessed by pv_card\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", pv_card[i].holder, pv_card[i].card_no);
	}

	v_card[0].holder[0] = 'X';
	printf("\n\nCards stored by v_card after changing the v_card first item\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", v_card[i].holder, v_card[i].card_no);
	}
	printf("\n\nCards stored in heap memory after changing the v_card first item\n");
	for (unsigned char i = 0; i < count; i++)
	{
		printf("%s %s\n", pv_card[i].holder, pv_card[i].card_no);
	}

	// deallocation of v_card extensions to heap mem
	for (unsigned char i = 0; i < count; i++)
	{
		free(v_card[i].holder);
		free(v_card[i].issuer);
	}

	// deallocation of pv_card 
	// step 1: deallocte holder and issuer for each item in pv_card
	for (unsigned char i = 0; i < count; i++)
	{
		free(pv_card[i].holder);
		free(pv_card[i].issuer);
	}
	// step 2: dealocate the array itself
	free(pv_card);


	
	return 0;
}