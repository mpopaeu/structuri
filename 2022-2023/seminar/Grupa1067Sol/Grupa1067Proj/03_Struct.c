#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define ACCOUNT_NUMBER 20

struct BankAccount
{
	char* owner;
	char iban[24];
	float balance;
	char currency[4];
};

// function to compute the number of currencies for each bank account owner
// the banck account data is taken from an array (vba)

struct OwnerNode {
	char* name;
	struct CurrencyNode* currency_list;
	struct OwnerNode* next;
};

struct CurrencyNode
{
	char currency[4];
	struct CurrencyNode* next;
};


struct OwnerNode* create_owner_list(struct BankAccount v[], unsigned int v_size)
{
	struct OwnerNode* first = NULL;

	for (unsigned int i = 0; i < v_size; i++)
	{
		struct OwnerNode* t = first;
		unsigned char is_there = 0;
		while (t && (is_there == 0))
		{
			if (strcmp(v[i].owner, t->name) == 0)
			{
				is_there = 1; // the owner is already placed in the list
			}

			t = t->next;
		}

		if (is_there == 0)
		{
			// the owner was not found out in the owners' list
			// a new node is added to the owners' list
			struct OwnerNode* new_node = (struct OwnerNode*)malloc(sizeof(struct OwnerNode));

			new_node->name = (char*)malloc(strlen(v[i].owner) + 1);
			strcpy(new_node->name, v[i].owner);

			new_node->currency_list = NULL; // empty list of currencies to be attached to current owner
			new_node->next = first; // next item of the new node is the existing starting itemt

			first = new_node; // new 1st item of the list
		}
	}

	return first;
}

struct CurrencyNode* create_currency_list(struct BankAccount v[], unsigned int v_size)
{
	struct CurrencyNode* first = NULL;

	for (unsigned int i = 0; i < v_size; i++)
	{
		struct CurrencyNode* t = first;
		unsigned char is_there = 0;
		while (t && (is_there == 0))
		{
			if (strcmp(v[i].currency, t->currency) == 0)
			{
				is_there = 1; // the currency is already placed in the list
			}

			t = t->next;
		}

		if (is_there == 0)
		{
			// the currency was not found out in the currency list
			// a new node is added to the currency list
			struct CurrencyNode* new_node = (struct CurrencyNode*)malloc(sizeof(struct CurrencyNode));
			strcpy(new_node->currency, v[i].currency);
			new_node->next = first; // next item of the new node is the existing starting itemt

			first = new_node; // new 1st item of the list
		}
	}

	return first;
}

void attach_currencies_to_owners(struct OwnerNode* list, struct BankAccount v[], unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
	{
		unsigned char is_there = 0;
		struct OwnerNode* t = list;
		while (t && (is_there == 0))
		{
			if (strcmp(t->name, v[i].owner) == 0)
			{
				is_there = 1;
				// t is the node in the list of owners to be check against the list of currencies
				struct CurrencyNode* tcurrency = t->currency_list;
				// parse the list of currencies
				unsigned char is_currency = 0;
				while (tcurrency && (is_currency == 0))
				{
					// check each node agaisnt the v[i]. currency
					if (strcmp(tcurrency->currency, v[i].currency) == 0)
					{
						// there is the v[i] currency in the list of currencies attached t the node t (t->name)
						is_currency = 1;
					}
					else
					{
						tcurrency = tcurrency->next;
					}
				}
				
				if (is_currency == 0)
				{
					// add a new node in this list currencies 
					// (the currency coming from v[i] is not yet associated to currency list 
					// for the owner t->name)

					// the new currency node will be added at the beginning of the currency list
					struct CurrencyNode* newCurrencyNode = (struct CurrencyNode*)malloc(sizeof(struct CurrencyNode));
					strcpy(newCurrencyNode->currency, v[i].currency);
					newCurrencyNode->next = t->currency_list;
					t->currency_list = newCurrencyNode;
				}
			}

			t = t->next;
		}
	}
}

// compute number of currencies per each owner in simple list

// create double linked list of bank accounts from the vector vba
// the nodes are ascending sorted (field balance) in the double linked list

// deallocation of a double list of bank accounts

int main()
{
	FILE* f;
	f = fopen("Accounts.txt", "r");

	unsigned char buffer[BUFFER_SIZE];
	char sep_list[] = ",";

	struct BankAccount vba[ACCOUNT_NUMBER];
	unsigned int i = 0;

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		struct BankAccount ba;
		char* token = strtok(buffer, sep_list); // owner's name
		ba.owner = (char*)malloc(strlen(token) + 1);
		strcpy(ba.owner, token); // there is no conversion

		token = strtok(NULL, sep_list);
		strcpy(ba.iban, token); // no conversion; text-to-text

		token = strtok(NULL, sep_list);
		ba.balance = atof(token); // conversion text-to-binary(as float)

		token = strtok(NULL, sep_list);
		strcpy(ba.currency, token); // no conversion; text-to-text

		vba[i++] = ba;
	}

	unsigned int array_size = i; // number of bank accounts read from the file Accounts.txt

	struct OwnerNode* owner_list, *towner;
	owner_list = create_owner_list(vba, array_size);
	printf("List of bank account owners: \n");
	towner = owner_list;
	while (towner)
	{
		printf("Name: %s\n", towner->name);

		towner = towner->next;
	}

	struct CurrencyNode* currency_list, *tcurrency;
	currency_list = create_currency_list(vba, array_size);
	printf("List of bank account currencies: \n");
	tcurrency = currency_list;
	while (tcurrency)
	{
		printf("Currency: %s\n", tcurrency->currency);

		tcurrency = tcurrency->next;
	}

	// attach currencies to the owners' list
	attach_currencies_to_owners(owner_list, vba, array_size);
	printf("List of bank account owners + currencies: \n");
	towner = owner_list;
	while (towner)
	{
		printf("\nName: %s", towner->name);
		tcurrency = towner->currency_list;
		while (tcurrency)
		{
			printf(" %s ", tcurrency->currency);
			tcurrency = tcurrency->next;
		}

		towner = towner->next;
	}
	printf("\n\n");

	// deallocate all structures created in heap mem

	while (owner_list) {
		while (owner_list->currency_list) {
			struct CurrencyNode* temp = owner_list->currency_list;
			owner_list->currency_list = temp->next;
			free(temp);
		}
		struct OwnerNode* temp2 = owner_list;
		owner_list = temp2->next;
		free(temp2->name);
		free(temp2);

	}

	while (currency_list) {
	
		struct CurrencyNode* temp = currency_list;
		currency_list = temp->next;
		free(temp);

	}
	printf("List of bank account owners + currencies after deallocation: \n");
	towner = owner_list;
	while (towner)
	{
		printf("\nName: %s", towner->name);
		tcurrency = towner->currency_list;
		while (tcurrency)
		{
			printf(" %s ", tcurrency->currency);
			tcurrency = tcurrency->next;
		}

		towner = towner->next;
	}
	printf("\n\n");

	printf("List of bank account currencies after deallocation: \n");
	tcurrency = currency_list;
	while (tcurrency)
	{
		printf("Currency: %s\n", tcurrency->currency);

		tcurrency = tcurrency->next;
	}


	fclose(f);
	return 0;
}