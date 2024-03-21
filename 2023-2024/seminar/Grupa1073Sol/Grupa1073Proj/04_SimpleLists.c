#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

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

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	Node* head = NULL;
	char buffer[256];

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

		// insert tAccount data into a new node added to the list handled by variable head
		head = insert_start(head, tAccount);
	}

	// parsing the simple list

	// deallocation of the simple list

	fclose(f);
	return 0;
}