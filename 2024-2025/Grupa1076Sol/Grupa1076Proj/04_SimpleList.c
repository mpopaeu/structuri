#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define CARD_NUMBER_LENGTH 16
#define EXPIRING_DATE_FORMAT_LENGTH 5 // MM/YY

struct BankCard
{
	char* holder;
	char card_no[CARD_NUMBER_LENGTH + 1];
	float balance; 
	char exp_date[EXPIRING_DATE_FORMAT_LENGTH + 1]; 
	char* currency; 
}; 

typedef struct BankCard BankCard;

struct Node
{
	BankCard data;
	struct Node* next; // mem address of the next item (node) in the chain
};

typedef struct Node Node;

// insert a node into a simple list
Node* insert_node(Node* list, BankCard bc)
{
	Node* t = list;

	if (t)
	{
		// list contains one node at least
		while (t->next != NULL)
			t = t->next;
	}
	
	Node* new_node = malloc(sizeof(Node));
	new_node->data = bc;
	new_node->next = NULL;

	if (t)
	{
		// there is one single node at least
		t->next = new_node;
		return list;
	}
	else
	{
		return new_node;
	}

}

int main()
{
	FILE* f = fopen("CardData.txt", "r");

	Node* head = NULL;

	unsigned char buffer[200];
	while (fgets(buffer, sizeof(buffer), f))
	{
		BankCard card;
		char seps[] = ",\n";
		char* token = strtok(buffer, seps);
		strcpy(card.card_no, token);

		token = strtok(NULL, seps); // continue the splitting
		strcpy(card.exp_date, token);

		token = strtok(NULL, seps);
		card.holder = malloc(strlen(token) + 1);
		strcpy(card.holder, token);

		token = strtok(NULL, seps);
		card.currency = malloc(strlen(token) + 1);
		strcpy(card.currency, token);

		token = strtok(NULL, seps);
		card.balance = (float)atof(token);

		// insert card data into a simple list
		head = insert_node(head, card);
	}

	fclose(f);

	// insert a node in the middle of the list (define criteria!), delete a node at the begining and the end of the list

	return 0;
}