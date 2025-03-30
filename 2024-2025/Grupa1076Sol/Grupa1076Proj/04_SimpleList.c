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
	new_node->next = NULL; // mandatory NULL because the new node will be the last node after insert

	if (t != NULL)
	{
		// there is one single node at least
		// t is the last node in the list
		t->next = new_node; // new node become the new last node
		return list;
	}
	else
	{
		return new_node; // new node is the first and unique node within the list
	}
}

void parse_list(Node* list)
{
	Node* temp = list;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->data.holder, temp->data.card_no);

		temp = temp->next; // update temp with the next node in the chain
	}
}

Node* delete_node_middle(Node* list, char* card_number)
{
	if (list != NULL)
	{
		// the list is not empty
		if (strcmp(list->data.card_no, card_number) == 0)
		{
			// the node to be deleted is the head of the list
			Node* temp = list;
			list = list->next;

			free(temp->data.holder);	// deallocate holder string
			free(temp->data.currency);	// deallocate currency string
			free(temp);					// deallocate the node itself
		}
		else
		{
			// the node to be deleted is not in the head of the list
			Node* temp = list;
			Node* temp_del = list->next;
			while (temp_del != NULL)
			{
				if (strcmp(temp_del->data.card_no, card_number) == 0)
				{
					temp->next = temp_del->next; // temp is the node just before the temp_del
												 // the new next node node for temp will be the actual next node for temp_del

					free(temp_del->data.holder);
					free(temp_del->data.currency);
					free(temp_del);
					temp_del = NULL;
				}
				else
				{
					temp = temp_del;
					temp_del = temp_del->next;
				}
			}
		}
	}

	return list;
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
		char* token = strtok(buffer, seps); // splitting started from the beginning of buffer array
		strcpy(card.card_no, token);

		token = strtok(NULL, seps); // continue the splitting of buffer from the current point
		strcpy(card.exp_date, token);

		token = strtok(NULL, seps); // continue the splitting of buffer from the current point
		card.holder = malloc(strlen(token) + 1);
		strcpy(card.holder, token);

		token = strtok(NULL, seps); // continue the splitting of buffer from the current point
		card.currency = malloc(strlen(token) + 1);
		strcpy(card.currency, token);

		token = strtok(NULL, seps); // continue the splitting of buffer from the current point
		card.balance = (float)atof(token);

		// insert card data into a simple list
		head = insert_node(head, card);
	}

	fclose(f);

	printf("Simple list after creation:\n");
	parse_list(head);

	head = delete_node_middle(head, "6542777788881908");
	printf("\nSimple list after deletion of one node:\n");
	parse_list(head);

	// deallocate the entire list by calling the one single node deletion
	// for the card number taken from the head everytime
	while (head != NULL)
	{
		head = delete_node_middle(head, head->data.card_no);
	}
	printf("\nSimple list after deallocation:\n");
	parse_list(head);


	// insert a node in the middle of the list (define criteria!)
	// delete a node at the begining and the end of the list

	return 0;
}