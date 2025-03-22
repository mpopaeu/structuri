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
	char card_no[CARD_NUMBER_SIZE + 1]; // 17 bytes
	Date exp_date; // 2 bytes -> no alignment (month and year are char)
	char* issuer; // 4 bytes -> enforce alignment by adding +1 byte to card_no
	float balance; // 4 bytes
}; // 31 bytes; actual length is 32 bytes

typedef struct BankCard BankCard;

struct Node
{
	BankCard data;
	struct Node* next; // the mem address of the next item (node) in the chain
};

typedef struct Node Node;

// insert one node into a simple list
Node* insert_node(Node* list, BankCard bc)
{

}

int main()
{
	FILE* f = fopen("CardData.txt", "r");
	Node* list_start = NULL;

	unsigned char buffer[200];

	fgets(buffer, sizeof(buffer), f);
	while (!feof(f))
	{
		BankCard card;
		char seps[] = ",/\n";
		char* token = strtok(buffer, seps);
		card.holder = malloc(strlen(token) + 1); // +1 for null byte as terminator
		strcpy(card.holder, token); // copy the string token into v_card holder's heap area

		token = strtok(NULL, seps); // get the vard number string
		strcpy(card.card_no, token);

		token = strtok(NULL, seps); // get the month
		card.exp_date.month = atoi(token); // convert string month into integer month
		token = strtok(NULL, seps); // get the year
		card.exp_date.year = atoi(token);// convert string year into integer year

		token = strtok(NULL, seps);
		card.issuer = malloc(strlen(token) + 1);
		strcpy(card.issuer, token);

		token = strtok(NULL, seps); // get the balance
		card.balance = (float)atof(token); // convert string balance into float balance

		// insert card data into a simple list
		list_start = insert_node(list_start, card);

		// read the next line in the text file CardData.txt
		fgets(buffer, sizeof(buffer), f);
	}

	fclose(f);

	// insert node into a simple list (at the end, in the middle), delete a node in a simple list (at the end, in the middle)
}