#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define BA_ARRAY_SIZE 20

struct BankAccount {
	char iban[25];
	char* owner;
	float balance;
	char currency[4];
};

struct NodeBankAccount { // simple list node structure to store data sets into hash table with chaining
	struct BankAccount bankAccount;
	struct NodeBankAccount* next; 
};

unsigned int hash_function(char key[], unsigned int htable_size)
{
	unsigned int sum = 0;
	for (unsigned int i = 0; i < strlen(key); i++)
		sum += key[i];

	// sum contains the valuae aftera adding ASCII codes for all input symbols in parameter key
	return sum % htable_size;
}

struct NodeBankAccount* insert_begin(struct NodeBankAccount* list, struct BankAccount new_ba)
{
	struct NodeBankAccount* newNode = (struct NodeBankAccount*)malloc(sizeof(struct NodeBankAccount));
	newNode->bankAccount = new_ba;
	newNode->next = list;

	return newNode; // new beginning of the simple list
}

void insert_htable(struct NodeBankAccount** HTable, unsigned int htable_size, struct BankAccount ba)
{
	unsigned int position = hash_function(ba.iban, htable_size); //position of the simple list where ba will be stored into

	HTable[position] = insert_begin(HTable[position], ba); // ba data inserted into the simple list linked to the position computed before
}

struct BankAccount search_ba(struct NodeBankAccount** HTable, unsigned int htable_size, char iban_key[])
{
	unsigned int position = hash_function(iban_key, htable_size);

	struct NodeBankAccount* temp = HTable[position];
	while (temp)
	{
		if (strcmp(temp->bankAccount.iban, iban_key) == 0)
		{
			return temp->bankAccount;
		}

		temp = temp->next;
	}

	struct BankAccount ba;
	ba.owner = NULL;

	return ba;
}

int main()
{

	FILE* f;
	f = fopen("Account.txt", "r");

	unsigned char buffer[BUFFER_SIZE];
	char sep_list[] = ",\n"; 
	struct BankAccount ba;

	// the hash table
	struct NodeBankAccount** HTable = NULL; // array of items NodeBankAccount* (simple lists)
	// allocation of the hash table into heap mem at runtime
	HTable = (struct NodeBankAccount**)malloc(BA_ARRAY_SIZE * sizeof(struct NodeBankAccount*));
	for (unsigned int i = 0; i < BA_ARRAY_SIZE; i++)
		HTable[i] = NULL; // item i is NULL; that means an empty simple list is linked to offset i

	while (fgets(buffer, BUFFER_SIZE, f))
	{		
		char* token = strtok(buffer, sep_list); // first token (iban) is starting from adress token
		strcpy(ba.iban, token); // iban from the file is copied into ba.iban (it is a text, no conversion)

		token = strtok(NULL, sep_list);
		ba.owner = malloc(strlen(token) + 1);
		strcpy(ba.owner, token); // no conversion for the owner's name

		token = strtok(NULL, sep_list);
		ba.balance = atof(token); // cpnversion from ASCII to float internal represetation

		token = strtok(NULL, sep_list);
		strcpy(ba.currency, token); // no conversion for currency

		// insert the bank account into hash table with chaining
		insert_htable(HTable, BA_ARRAY_SIZE, ba);
	}

	// validation of hash tabel content
	printf("The content of the entire hash table:\n");
	for (unsigned int i = 0; i < BA_ARRAY_SIZE; i++)
	{
		if (HTable[i] != NULL)
		{
			// there is a simple list linked to position/offset/item i
			printf("Simple list linked to position/offset %d in the hash table:\n", i);
			struct NodeBankAccount* temp = HTable[i]; // HTable[i] is the head of the list linked to position i
			while (temp)
			{
				printf("%s %s\n", temp->bankAccount.iban, temp->bankAccount.owner);
				temp = temp->next;
			}
		}
	}

	// search into a hash table with chaining
	ba = search_ba(HTable, BA_ARRAY_SIZE, "RO15RNCB1234567891160980");
	if (ba.owner != NULL)
	{
		printf("Bank account found: %s %s %.2f\n", ba.iban, ba.owner, ba.balance);
	}
	else
	{
		printf("There is no bank account with iban provided before:\n");
	}

	// delete a bank account in a hash table with chaining

	// deallocate the hash table: deallocation of the simple lists + deallocation of the array
	fclose(f);
}