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


// the first appearance of BankAccount meeting the name 
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

// function to create an array of BankAccount addresses will meet the key (searching_name)
// function returns the memory address of the array + the actual size of that array 
// created array contains references to BankAccount data found in hash table
//
// I/: HT - hash table
// I/: ht_size - size of the array as implementation support for the hash table (chaining)
// I/: searching_name - key used to identify BankAccount with the same owner's name
// O/: array_size - actual size of the array created for the found BankAccount data in hash table
// return: starting memory address of the array with references to BankAccount data
BankAccount** search_all_ba(Node** HT, unsigned char ht_size, char* searching_name, 
						   unsigned char* array_size)
{
	// call function to hash computation
	unsigned char offset = hash_function(searching_name, ht_size);

	// initialize the size of the output array
	*array_size = 0;

	// once offset computed, the node must be searched item by item in the simple list
	Node* temp = HT[offset];
	while (temp)
	{
		if (strcmp(temp->data.owner_name, searching_name) == 0)
			(*array_size) += 1; // add to counter the number of BankAccount data
		temp = temp->next;
	}

	// allocate the output array
	BankAccount** out_array = NULL; 
	
	if (*array_size != 0)
	{
		out_array = (BankAccount**)malloc(*array_size * sizeof(BankAccount*));

		// parse again the simple list HT[offset] to store address of BankAccount data
		unsigned char i = 0;
		temp = HT[offset];
		while (temp)
		{
			if (strcmp(temp->data.owner_name, searching_name) == 0)
			{
				out_array[i] = &temp->data;
				i += 1; // next storage item is the next iterator in the output array
			}
			temp = temp->next;
		}
	}

	return out_array;
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
		printf("\nBank Account has been founded out: %s %s\n", temp->data.owner_name, temp->data.iban);
	}

	printf("\n\nSearching all BankAccount data for a certain owner's name:\n");
	unsigned char size_all_ba;
	BankAccount** array_all_ba = search_all_ba(HTable, HASH_TABLE_SIZE, "Vasilescu Miruna", &size_all_ba);
	if (array_all_ba != NULL)
	{
		// at least, there is one single BankAccount with searching key (for the owner's name)
		for (unsigned char i = 0; i < size_all_ba; i++)
			printf("Bank account: %s %s\n", array_all_ba[i]->iban, array_all_ba[i]->owner_name);
	}
	else
	{
		printf("There is no BankAccount data to match the searching owner's name!\n");
	}

	// TODO #1: search for all bank accounts which meet the key; the founded bank accounts will be stored
	// into a separate simple list; the separate simple list does not share heap memory locations
	// with the simple lists built in hash table with chaining

	// TODO: deallocation of hash table
	// TODO: deallocation of simple list with all bank account data for the same key (function 
	// according to requirements above TODO #1)
	fclose(f);
	return 0;
}