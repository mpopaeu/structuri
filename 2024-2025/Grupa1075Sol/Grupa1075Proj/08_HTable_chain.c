#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 50

struct Date
{
	char month; // stored as value
	char year; // stored as value; only last 2 letters are stored
};

typedef struct Date Date;

#define CARD_NUMBER_SIZE 16

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
// if there is no node with the holder's name, insert the data at the begining 
Node* insert_node(Node* list, BankCard bc, char* holder_name)
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
			// insert the node at the beggining
			Node* new_node = malloc(sizeof(Node));
			new_node->data = bc;
			new_node->next = list;
			list = new_node;
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

unsigned int hash_function(char* key, unsigned int htable_size)
{
	unsigned int sum = 0;
	for (unsigned int i = 0; i < strlen(key); i++)
		sum += key[i]; // add current ASCII code to the sum of ASCII codes for entire string key

	return (sum % htable_size); // % to be sure the computed offset is valid for my hash table
}

void insert_card_htable(Node** htable, unsigned int htable_size, BankCard data)
{
	// 1. compute the place in htable where data will be inserted (offset of a simple list)
	unsigned int offset = hash_function(data.holder, htable_size);

	// 2. insert the data into simple list computed as offset at step 1.
	htable[offset] = insert_node(htable[offset], data, "");
}

BankCard* search_data(Node** htable, unsigned int htable_size, char* holders_name)
{
	// 1. compute the place in htable where data will be checked (offset of a simple list)
	unsigned int offset = hash_function(holders_name, htable_size);

	// 2. check node by node if the holders_name is stored by the simple list htable[offset]
	Node* temp = htable[offset]; // temp is the first node in the simple list htable[offset]
	while (temp)
	{
		if (strcmp(temp->data.holder, holders_name) == 0)
		{
			// the holders_name is found out within temp
			return &(temp->data); // heap mem address returned from temp
		}

		temp = temp->next;
	}

	return NULL; // there is no holders_name stored by htable
}

// update the search implementation to catch all BankCard data sets for the same holder's name

int main()
{
	Node* *HTable = NULL;

	HTable = malloc(sizeof(Node*) * HASH_TABLE_SIZE); // allocation of hash table where each item is Node* (starting node of a simple list)

	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // initially, all items (simple lists) are empty

	unsigned char buffer[200];
	FILE* f = fopen("CardData.txt", "r");

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

		// insert card data into the hash table
		insert_card_htable(HTable, HASH_TABLE_SIZE, card); 

		// read the next line in the text file CardData.txt
		fgets(buffer, sizeof(buffer), f);
	}

	// search BankCard data for a particular holder
	BankCard* p_card_data = NULL;
	p_card_data = search_data(HTable, HASH_TABLE_SIZE, "Vasilescu Mihai George");

	if (p_card_data != NULL)
	{
		printf("BankCard details: %s %s %s\n", p_card_data->holder, p_card_data->card_no, p_card_data->issuer);
	}
	else
	{
		printf("There is no BankCard data for the specified holder.\n");
	}

	fclose(f);

	// deallocate the hash table


}