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
	char* holder;	// 4 bytes
	char card_no[CARD_NUMBER_SIZE + 1]; // 17 bytes
	Date exp_date;  // 2 bytes -> no alignment (month and year are char)
	char* issuer;   // 4 bytes -> enforce alignment by adding +1 byte to card_no
	float balance;  // 4 bytes
}; // 31 bytes (sum of all structure fields); actual length is 32 bytes

typedef struct BankCard BankCard;

struct Node
{
	BankCard data;
	struct Node* next; // the mem address of the next item (node) in the chain
};

typedef struct Node Node;

// insert one node into a simple list after an existing holder's name
// if list is empty, then perform the operation
// if there is no node with the holder's name, drop off the insert opeation
Node* insert_node(Node* list, BankCard bc, char * holder_name)
{
	if (list == NULL)
	{
		// the list is empty
		Node* new_node = malloc(sizeof(Node));
		new_node->data = bc;
		new_node->next = NULL;
		list = new_node;
	}
	else
	{
		// the list contains one node at least
		Node* temp = list; // temp used to parse the list node by node
		char stop_parsing_flag = 0;
		while (temp != NULL && stop_parsing_flag == 0)
		{
			if (strcmp(temp->data.holder, holder_name) == 0)
			{
				// the node with the holders' name has been found out in the list (temp)
				Node* new_node = malloc(sizeof(Node));
				new_node->data = bc;
				new_node->next = temp->next;
				temp->next = new_node;
				stop_parsing_flag = 1;
			}

			temp = temp->next;
		}

		if (stop_parsing_flag == 0)
		{
			// the insert did not take place; we have to deallocate fields holder and issuer in card data bc
			free(bc.holder);
			free(bc.issuer);
		}
	}

	return list; // updated when the list is coming empty to this call
}

// parsing the simple list to print out content from node
void parse(Node* list)
{
	Node* temp = list;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->data.holder, temp->data.card_no);
		temp = temp->next;
	}
}

Node* delete_node_beginning(Node* list)
{
	if (list != NULL)
	{
		// there is one node at least in the simple list
		Node* temp = list; // save the node to be deallocated/deleted
		list = list->next; // the new starting node of the remaining lis
						   // list = temp->next;

		free(temp->data.holder); // deallocate the holder's heap mem
		free(temp->data.issuer); // deallocate the issuer's heap mem
		free(temp); // deallocate the node itself
	}

	return list;
}

// function to delete all nodes having the same card holder (parameter of the function)
// within a simple list

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
		strcpy(card.holder, token);				 // copy the string token into v_card holder's heap area

		token = strtok(NULL, seps);			// get the vard number string
		strcpy(card.card_no, token);

		token = strtok(NULL, seps);			// get the month
		card.exp_date.month = atoi(token);  // convert string month into integer month
		token = strtok(NULL, seps);			// get the year
		card.exp_date.year = atoi(token);	// convert string year into integer year

		token = strtok(NULL, seps);
		card.issuer = malloc(strlen(token) + 1);
		strcpy(card.issuer, token);

		token = strtok(NULL, seps);		   // get the balance
		card.balance = (float)atof(token); // convert string balance into float balance

		// insert card data into a simple list
		list_start = insert_node(list_start, card, "Popescu Marian Alexandru");

		// read the next line in the text file CardData.txt
		fgets(buffer, sizeof(buffer), f);
	}

	fclose(f);

	printf("Simple list after its creation\n");
	parse(list_start);

	list_start = delete_node_beginning(list_start);
	printf("\nSimple list after node delete:\n");
	parse(list_start);

	// deallocation of entire simple list with repeated calls to delete_node_beginning(list_start)


	// migrate all above functions to double lists


	// insert a node into a simple list (at the end, in the middle)
	// delete a node in a simple list (at the end, in the middle)
}