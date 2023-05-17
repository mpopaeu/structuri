#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define ACCOUNT_NUMBER 20

struct BankAccount
{
	char* owner;
	char iban[25]; // + 1 for string standard terminator (the byte 0x00 at the end of the string)
	float balance;
	char currency[4];
};

struct BankAccountNode
{
	struct BankAccount ba;
	struct BankAccountNode* next;
};

unsigned int hash_function(char str[], unsigned int htable_size)
{
	unsigned int sum = 0;
	for (unsigned int i = 0; i < strlen(str); i++)
		sum += str[i];

	return sum % htable_size;
}


struct BankAccountNode* insert_list(struct BankAccountNode* list, struct BankAccount data)
{
	struct BankAccountNode* new_node = (struct BankAccountNode*)malloc(sizeof(struct BankAccountNode));

	new_node->ba = data;
	new_node->next = list;

	return new_node;
}

void insert_ba_hash_table(struct BankAccountNode** HTable, unsigned int ht_size, struct BankAccount data)
{
	unsigned int position = hash_function(data.iban, ht_size);

	HTable[position] = insert_list(HTable[position], data);
}

struct BankAccount search_ba_hash_table(struct BankAccountNode** HTable, unsigned int htable_size, char iban_key[])
{
	unsigned int position = hash_function(iban_key, htable_size);

	if (HTable[position] != NULL)
	{
		struct BankAccountNode* temp = HTable[position];
		while (temp)
		{
			if (strcmp(iban_key, temp->ba.iban) == 0)
			{
				// there is a bank account with searched iban
				return temp->ba;
			}
			temp = temp->next;
		}
	}

	struct BankAccount ba;
	ba.owner = NULL; // flag for a fake bank account

	return ba;
}

int main()
{
	FILE* f;
	f = fopen("Accounts.txt", "r");

	unsigned char buffer[BUFFER_SIZE];
	char sep_list[] = ",";
	struct BankAccount ba;

	struct BankAccountNode** HTable; // vector/array of items as starting addresses in simple lists
	// allocate the array
	HTable = (struct BankAccountNode**)malloc(ACCOUNT_NUMBER * sizeof(struct BankAccountNode*));
	for (unsigned int i = 0; i < ACCOUNT_NUMBER; i++)
		HTable[i] = NULL; // list i is marked as empty by using NULL

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		char* token = strtok(buffer, sep_list); // owner's name
		ba.owner = (char*)malloc(strlen(token) + 1);
		strcpy(ba.owner, token); // there is no conversion

		token = strtok(NULL, sep_list);
		strcpy(ba.iban, token); // no conversion; text-to-text

		token = strtok(NULL, sep_list);
		ba.balance = atof(token); // conversion text-to-binary(as float)

		token = strtok(NULL, sep_list);
		strcpy(ba.currency, token); // no conversion; text-to-text

		// insert data loaded into ba as an item of hash table
		insert_ba_hash_table(HTable, ACCOUNT_NUMBER, ba);
	}

	fclose(f);

	printf("Content of hash table after creation:\n");
	for (unsigned int i = 0; i < ACCOUNT_NUMBER; i++)
	{
		if (HTable[i] != NULL) // the list i has one node at least
		{
			struct BankAccountNode* temp = HTable[i];
			printf("List %u with bank accounts:\n", i);
			while (temp)
			{
				printf("%s %s\n", temp->ba.iban, temp->ba.owner);

				temp = temp->next;
			}
		}
	}

	// search a certains bank account based in iban
	ba = search_ba_hash_table(HTable, ACCOUNT_NUMBER, "RO11BTRL1000100099998788");

	if (ba.owner != NULL)
	{
		printf("Bank account identified: %s %s %.2f\n", ba.iban, ba.owner, ba.balance);
	}
	else
	{
		printf("There is no bank account with iban provided above.\n");
	}


	// delete bank account from hash table (iban)
	// de-allocate the entire hash table
}