#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 100

struct BankAccount
{
	char iban[21]; // 20 for iban itself + 1 for end of the string (byte 0x00)
	char* owner_name;
	float balance;
	char currency[4];  // 3 for currency code + 1 for end of the string (byte 0x00)
};

struct Node
{
	struct BankAccount info;
	struct Node* next;
};

typedef struct BankAccount BankAccount;
typedef struct Node Node;

Node* insert_start(Node* list, BankAccount acc)
{

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->info = acc;
	newNode->next = list;

	return newNode;
}

unsigned char hash_function(char* key, unsigned char ht_size)
{
	// 1. convert the string into a number
	unsigned int sum = 0;
	for (unsigned char i = 0; i < (strlen(key) - 1); i++)
		sum += key[i];
	sum += key[strlen(key) - 1] * 13;

	// 2. "translate" the above number into a valid offset for the hash table
	return (sum % ht_size);
}

void insert_ba_data(Node** HT, unsigned char ht_size, BankAccount data)
{
	// 1. compute hash function to get a valid position/offset within HT
	unsigned char offs = hash_function(data.iban, ht_size);

	// 2. insert data into the simple list HT[offs]
	HT[offs] = insert_start(HT[offs], data); // insert BankAccount data into simple list HT[offs]
}

BankAccount* search(Node** HT, unsigned char ht_size, char* key)
{
	// 1. compute hash function to get the offset of the simple list where data with key should be stored
	unsigned char offs = hash_function(key, ht_size);

	// 2. once having the simple list, look for the key for every items (nodes) in that list HT[offs]
	Node* temp = HT[offs];
	while (temp)
	{
		if (strcmp(key, temp->info.iban) == 0)
		{
			// the key matches the iben stored in the node temp
			return &temp->info; // return the heap memory address of the BankAccount
		}

		temp = temp->next;
	}

	return NULL; // the BankAccount with key does not exist in the hash table
}

// create hash table with key owner_name
// search for all Bank Account data for a certain owner provided as parameter to the search function

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	Node** HTable = NULL;
	char buffer[256];

	HTable = (Node**)malloc(HASH_TABLE_SIZE * sizeof(Node*)); // allocate the support array at runtime in heap
	// initially, all lists will be empty
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // HTable[i] is one single simple list which stores the date sets with collisions on i

	while (fgets(buffer, sizeof(buffer), f))
	{
		BankAccount tAccount;
		buffer[strlen(buffer) - 1] = 0; // overwrites the byte 0x0a ('\n') with byte 0x00 ('\n' added to buffer by fgets)
		strcpy(tAccount.iban, buffer);

		fgets(buffer, sizeof(buffer), f); // for the owner's name
		buffer[strlen(buffer) - 1] = 0;
		tAccount.owner_name = (char*)malloc(strlen(buffer) + 1);
		strcpy(tAccount.owner_name, buffer);

		fgets(buffer, sizeof(buffer), f); // for the bank account balance
		buffer[strlen(buffer) - 1] = 0;
		tAccount.balance = (float)atof(buffer);

		fgets(buffer, sizeof(buffer), f); // for the bank account currency
		buffer[strlen(buffer) - 1] = 0;
		strcpy(tAccount.currency, buffer);

		// insert BankAccount data (tAccount) into hash table
		insert_ba_data(HTable, HASH_TABLE_SIZE, tAccount);
	}

	// searching a BankAccount based on key
	BankAccount* p_account_data = search(HTable, HASH_TABLE_SIZE, "Ionescu Georgica");
	if (p_account_data != NULL)
	{
		// BankAccount data exists in hash table
		printf("Bank Account data found out: %s %s\n", p_account_data->iban, p_account_data->owner_name);
	}
	else
	{
		printf("The searched Bank Account does not exist in the hash table!\n");
	}

	// deallocate hash table with chaining
	// 1. deallocate all simple lists linked to the array HTable
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		while (HTable[i] != NULL)
		{
			Node* temp = HTable[i];
			HTable[i] = HTable[i]->next;

			free(temp->info.owner_name); // deallocate the owner's name of the BankAccount stored by temp
			free(temp);					 // deallocate the node temp
		}
	}
	// 2. deallocate the array as support data structure for the hash table
	free(HTable);
	HTable = NULL;


	fclose(f);
	return 0;
}