#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define BA_ARRAY_SIZE 20

struct BankAccount {
	char iban[24];
	char* owner;
	float balance;
	char currency[4];
};

struct Node
{
	char currency[4];
	double total_balance;
	struct Node *next;
};

// write the function to compute total balance per currency
// input is taken from a bank account array
// output ???

struct Node* compute_balances_per_currency(struct BankAccount v[], unsigned int vba_size)
{
	struct Node* first = NULL;

	for (unsigned int i = 0; i < vba_size; i++)
	{
		struct Node* t = first;
		unsigned char is_currency = 0;

		while (t && (is_currency == 0))
		{
			if (strcmp(v[i].currency, t->currency) == 0) // v[i].currency already stored by the simple list
			{
				t->total_balance += v[i].balance; //update the current total balance
				is_currency = 1; // change the flag to enforce the exit from while
			}

			t = t->next;
		}

		if (is_currency == 0)
		{
			struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // alocation of a new Node in heap mem

			strcpy(newNode->currency, v[i].currency); // copy the currency into the new node
			newNode->total_balance = v[i].balance; // initialize the balance of the new node
			newNode->next = first; // the next node is the current starting node of the list

			first = newNode; // update the starting node of the list
		}
	}

	return first; // it stores the mem address of the 1st item in the list of currencies
}

int main()
{

	FILE* f;
	f = fopen("Account.txt", "r");

	unsigned char buffer[BUFFER_SIZE];
	char sep_list[] = ",\n";

	struct BankAccount vba[BA_ARRAY_SIZE];
	unsigned int i = 0;

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		struct BankAccount ba;
		char* token = strtok(buffer, sep_list); // first token (iban) is starting from adress token
		strcpy(ba.iban, token); // iban from the file is copied into ba.iban (it is a text, no conversion)

		token = strtok(NULL, sep_list);
		ba.owner = malloc(strlen(token) + 1);
		strcpy(ba.owner, token); // no conversion for the owner's name

		token = strtok(NULL, sep_list);
		ba.balance = atof(token); // cpnversion from ASCII to float internal represetation

		token = strtok(NULL, sep_list);
		strcpy(ba.currency, token); // no conversion for currency

		vba[i++] = ba;
	}

	unsigned int size = i;

	struct Node* firstNode = compute_balances_per_currency(vba, size);
	printf("Total balance per currency:\n");
	struct Node* t = firstNode;
	while (t)
	{
		printf("Currency: %s, Total balance: %.2lf\n", t->currency, t->total_balance);

		t = t->next;
	}

	fclose(f);


	// deallocate simple list firstNode
	return 0;
}