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

struct NodeD
{
	struct BankAccount *info;
	struct NodeD * next, *prev;
};

typedef struct BankAccount BankAccount;
typedef struct NodeD NodeD;

struct DoubleList
{
	NodeD* head, * tail;
};

typedef struct DoubleList DoubleList;

DoubleList insert_start(DoubleList list, BankAccount * pba)
{
	NodeD* newNode = (NodeD*)malloc(sizeof(NodeD));
	newNode->info = pba;
	newNode->next = list.head;
	newNode->prev = NULL;

	if (list.head == NULL)
	{
		// the double list is empty
		list.head = list.tail = newNode;
	}
	else
	{
		list.head->prev = newNode;
		list.head = newNode;
	}

	return list;
}

DoubleList deallocate_list(DoubleList list)
{
	while (list.head != NULL)
	{
		// there is one node (at least) in the double list
		NodeD* temp = list.head; // save the heap address of the 1st node into a temporary local variable
		list.head = list.head->next; // list stores the address of the 2nd node in the list

		free(temp->info->owner_name); // release the 3rd level heap allocated location (string for owner's name)
		free(temp->info);			  // release the BankAccount structure (2nd allocation level in heap)
		free(temp);					 // release the 1st level heap allocated location (NodeD)
	}

	list.tail = NULL;

	return list;
}

DoubleList swap(DoubleList list, unsigned char position_first)
{
	if (list.head == NULL || list.head->next == NULL)
		return list;

	NodeD* temp = list.head;
	unsigned char counter = 0;
	while (temp!=list.tail && counter <= position_first)
	{

	}

	return list;
}

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	DoubleList DList;
	DList.head = DList.tail = NULL; // the double list is initially empty
	char buffer[256];

	while (fgets(buffer, sizeof(buffer), f))
	{
		BankAccount tAccount, *pAccount;
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

		// allocate heap memory for BankAccount
		pAccount = (BankAccount*)malloc(sizeof(BankAccount));
		// copy data from tAccount (stack seg) to *pAccount (heap seg)
		*pAccount = tAccount;

		// call insert double node at the begining of the double list
		DList = insert_start(DList, pAccount);
	}

	printf("Double list after creation:\n");
	NodeD* temp = DList.tail;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->info->iban, temp->info->owner_name);
		temp = temp->prev;
	}

	DList = deallocate_list(DList);

	printf("Double list after deallocation:\n");
	temp = DList.head;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->info->iban, temp->info->owner_name);
		temp = temp->next;
	}


	fclose(f);
	return 0;
}