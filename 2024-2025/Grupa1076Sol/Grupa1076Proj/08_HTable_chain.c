#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define CARD_NUMBER_LENGTH 16
#define EXPIRING_DATE_FORMAT_LENGTH 5 // MM/YY
#define HASH_TABLE_SIZE 50

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

unsigned int hash_function(char* key, unsigned int htable_size)
{
	unsigned int sum = 0;
	for (unsigned int i = 0; i < strlen(key); i++)
		sum += key[i]; // add current ASCII code to te sum 

	return (sum % htable_size);
}

void insert_data_htable(Node** htable, unsigned int htable_size, BankCard data)
{
	// 1. call the hash function to get the offset of the simple list where data will be inserted into
	unsigned int offset = hash_function(data.card_no, htable_size);

	// 2. insert the data in that list established at 1.
	htable[offset] = insert_node(htable[offset], data);
}

BankCard* search_card_data(Node** htable, unsigned int htable_size, char* card_number)
{
	// 1. call the hash function to get the simple list where card data should be stored
	unsigned int offset = hash_function(card_number, htable_size);

	// 2. compare the card_number with each card_no stored in the nodes of the simple list
	Node* temp = htable[offset]; // temp used to parse the entire simple list
	while (temp != NULL)
	{
		if (strcmp(card_number, temp->data.card_no) == 0)
		{
			return &(temp->data); // heap mem address of BankCard data to be used later outside the function
		}

		temp = temp->next;
	}

	return NULL; // no match related to card_number
}

// delete card data based on card number 

// deallocate the hash table

// create array of card data for a currency specified as paramater of the function
BankCard* new_array(Node** hashtable, unsigned int size, char* currency, unsigned int* no_matches) {
	*no_matches = 0;
	for (unsigned int i = 0; i < size; i++) { //Parse the entire hashtable. Currency is not the key.
		Node* temp = hashtable[i]; //hashtable[i] stores the adress of the first node in list i for the hashtable.
		while (temp) {
			if (strcmp(temp->data.currency, currency) == 0) { //Check if the currency matches.
				*no_matches += 1; //Number of matches counts the matching cards on currency.
			}
			temp = temp->next;
		}
	} 
	
	if(*no_matches > 0){ 
		BankCard* new_verified_array = malloc(sizeof(BankCard) * *no_matches); //Allocation of the result array.
		unsigned int temp_index = 0;
		for (unsigned int i = 0; i < size; i++) {//Parse the entire hashtable. Currency is not the key.
			Node* temp = hashtable[i];
			while (temp) {
				if (strcmp(temp->data.currency, currency) == 0) {
					new_verified_array[temp_index] = temp->data;//Store the card data into the result array.Array and hash table share some heap locations.
					temp_index += 1;
				}
				temp = temp->next;
			}
		}
		return new_verified_array;
	}else { return NULL; }//No array if there is no match.
}


int main()
{
	FILE* f = fopen("CardData.txt", "r");

	Node* *HTable = NULL; // hash table support as array of simple linked lists
	HTable = malloc(HASH_TABLE_SIZE * sizeof(Node*)); // allocation of the array as support for the hash table
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		HTable[i] = NULL; // each simple list HTable[i] is marked as null/empty list
	}

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

		// insert card data into hash table with chaining
		insert_data_htable(HTable, HASH_TABLE_SIZE, card);
	}

	fclose(f);

	BankCard* p_data = search_card_data(HTable, HASH_TABLE_SIZE, "6523667711220099");
	if (p_data != NULL)
	{
		printf("Card data info: %s %s\n", p_data->holder, p_data->card_no);
	}
	else
	{
		printf("The card data does not exist in hash table.\n");
	}
	unsigned int temp_size;
	BankCard* card_array = new_array(HTable, HASH_TABLE_SIZE, "Romanian Leu", &temp_size);

	
	printf("Array of Card Data with same currency: \n");
	for (unsigned int i = 0; i < temp_size; i++) {
		printf("Card data info: %s %s\n", card_array[i].card_no, card_array[i].currency);
	}

	//Deallocation of the hashtable.
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++) {
		while (HTable[i]) {
			Node* temp = HTable[i];
			HTable[i] = HTable[i]->next;
			free(temp->data.currency);
			free(temp->data.holder);
			free(temp);
		}
	}
	//Deallocation of card_array.
	free(card_array);

	return 0;
}