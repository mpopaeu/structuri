#include "Structs.h"

Node* insert_begining(Node* list, BankAccount ba)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = ba;
	newNode->next = list;

	return newNode;
}

Node* swap(Node* list, char* sIBAN)
{
	if (list == NULL || list->next == NULL)
		return list;

	// the list has 2 node at least
}

// [sIBAN1, sIBAN2] OR [sIBAN2, sIBAN1]
Node* swap_general(Node* list, char* sIBAN1, char* sIBAN2)
{

}

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	char buffer[256];
	
	Node* head = NULL;

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

		// insert tBankAccount data into the simple list handled by head 
		// new node addded to the begining of the simple list
		head = insert_begining(head, tBankAccount);
	}

	printf("The list after creation:\n");
	Node* temp = head;
	while (temp)
	{
		printf("%s %s\n", temp->data.iban, temp->data.owner_name);

		temp = temp->next;
	}

	// deallocation of the simple list
	while (head)
	{
		temp = head;		// temp is the actual 1st node in the list
		head = head->next;	// head moved to the 2nd node in the list
		
		free(temp->data.owner_name);
		free(temp->data.currency);
		free(temp);
	}

	fclose(f);
	return 0;
}