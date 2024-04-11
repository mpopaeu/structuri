#include "Structs.h"

#define HASH_TABLE_SIZE 100

Node* insert_begining(Node* list, BankAccount ba)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = ba;
	newNode->next = list;

	return newNode;
}

unsigned char hash_function(char* key, unsigned char ht_size)
{
	unsigned int sum = 0;
	for (char i = (char)(strlen(key) - 1); i > (char)(strlen(key) - 5) && i >= 0; i--)
	{
		sum += key[i];
	}

	return (unsigned char)(sum % ht_size);
}

void insert_ba_hash_table(Node** HT, unsigned char ht_size, BankAccount ba_data)
{
	// call function to get the hash value
	unsigned char offset = hash_function(ba_data.owner_name, ht_size);
	printf("\nThe key %s goes into list #%d.", ba_data.owner_name, (int)offset);
	// insert into hash table the ba_data on offset computed one line above
	HT[offset] = insert_begining(HT[offset], ba_data);
}

Node* search_first_ba(Node** HT, unsigned char ht_size, char* name)
{
	// call function to hash compute
	unsigned char offset = hash_function(name, ht_size);

	// once offset computed, the node must be searched item by item in the simple list
	Node* temp = HT[offset];
	while (temp)
	{
		if (strcmp(temp->data.owner_name, name) == 0)
			return temp; // only the first identified node is returned 
		temp = temp->next;
	}

	return temp; // NULL
}

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	char buffer[256];

	Node** HTable = (Node**)malloc(HASH_TABLE_SIZE * sizeof(Node*)); // allocation of the support array for hash table
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL; // HTable[i] is the starting address of a simple list

	while (fgets(buffer, sizeof(buffer), f)) // buffer must contain iban
	{
		BankAccount tBankAccount;
		strncpy(tBankAccount.iban, buffer, strlen(buffer) - 1);
		tBankAccount.iban[strlen(buffer) - 1] = 0;

		fgets(buffer, sizeof(buffer), f); // buffer must contain owner's name
		tBankAccount.owner_name = (char*)malloc(strlen(buffer));
		strncpy(tBankAccount.owner_name, buffer, strlen(buffer) - 1);
		tBankAccount.owner_name[strlen(buffer) - 1] = 0;

		fgets(buffer, sizeof(buffer), f); // buffer must contain balance data (as string)
		tBankAccount.balance = atof(buffer);

		fgets(buffer, sizeof(buffer), f); // buffer must contain currency
		tBankAccount.currency = (char*)malloc(strlen(buffer));
		strncpy(tBankAccount.currency, buffer, strlen(buffer) - 1);
		tBankAccount.currency[strlen(buffer) - 1] = 0;

		// insert tBankAccount data into hast table with chaining
		insert_ba_hash_table(HTable, HASH_TABLE_SIZE, tBankAccount);
	}

	// search the first bank account which meets the key
	Node* temp = search_first_ba(HTable, HASH_TABLE_SIZE, "Popescu Mircea");
	if (temp)
	{
		printf("Bank Account has been founded out: %s %s\n", temp->data.owner_name, temp->data.iban);
	}

	// TODO: search for all bank account which meets the key; the founded bank accounts will be stored
	// into a separate simple list; the separate simple list does not share heap memory locations
	// with the simple lists built in hash table with chaining

	// TODO: deallocation of hash table
	// TODO: deallocation of simple list with all bank account data for the same key (function 
	// according to requirements at line #90)
	fclose(f);
	return 0;
}