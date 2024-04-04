#include "Structs.h"

DoubleList insert_begining(DoubleList list, BankAccount *pba)
{
	NodeD* newNode = (NodeD*)malloc(sizeof(NodeD));

	newNode->pdata = pba;
	newNode->next = list.head;
	newNode->prev = NULL;

	if (list.head != NULL)
	{
		// there is 1 node (at least)
		list.head->prev = newNode;
		list.head = newNode;		// new begining of the double list
	}
	else
	{
		// double list is empty
		list.head = list.tail = newNode;
	}

	return list;
}

DoubleList swap(DoubleList list, char* sIBAN)
{

}

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	char buffer[256];

	DoubleList DList;
	DList.head = DList.tail = NULL;

	while (fgets(buffer, sizeof(buffer), f)) // buffer must contain iban
	{
		BankAccount tBankAccount, *pBankAccount;
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

		// allocate heap mem for BankAccount data
		pBankAccount = (BankAccount*)malloc(sizeof(BankAccount));
		*pBankAccount = tBankAccount;

		// pass pointer to BankAccount to add a new node in the double list
		DList = insert_begining(DList, pBankAccount);
	}

	printf("The double list after creation (head-to-tail):\n");
	NodeD* temp = DList.head;
	while (temp)
	{
		printf("%s %s\n", temp->pdata->iban, temp->pdata->owner_name);

		temp = temp->next;
	}

	// TODO: deallocation of the double list

	fclose(f);
	return 0;
}