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

struct NodeBankAccount {
	struct BankAccount bankAccount;
	struct NodeBankAccount *next, *prev; // relations with the next and previous nodes in double list
};

struct DoubleList
{
	struct NodeBankAccount* head, *tail;
};


struct DoubleList insertAscending(struct DoubleList list, struct BankAccount ba)
{
	struct NodeBankAccount* newNode = (struct NodeBankAccount*)malloc(sizeof(struct NodeBankAccount));
	newNode->bankAccount = ba; // bank account data are saved into the new node to be inserted
	
	if (list.head) { // check if there is one node at least
		if (newNode->bankAccount.balance < list.head->bankAccount.balance) {
			newNode->next = list.head; // the next node of the new inserted node is the current head
			newNode->prev = NULL; // the previous node must not exist after insertion
			list.head->prev = newNode; // the current head must point to the new node
			list.head = newNode; // update the head of the double list
		}

		else {
			struct NodeBankAccount* t = list.head;

			while (t->next && t->next->bankAccount.balance < newNode->bankAccount.balance) {
				t = t->next;
			}

			if (t->next)
			{ // insertion inside the double list
				newNode->next = t->next;
				newNode->prev = t;
				struct NodeBankAccount* s = t->next;
				t->next = newNode;
				s->prev = newNode;
			}
			else
			{
				// insertion at the end of the list; newNode will be the new tail of the list
				newNode->next = NULL;
				newNode->prev = list.tail;
				list.tail->next = newNode;
				list.tail = newNode;
			}
		}
	}
	else {
		// double list is empty
		// newNode will be the single node in the double list
		// the both managing pointers contain the addres of newNode
		newNode->next = NULL;
		newNode->prev = NULL;
		list.head = list.tail = newNode;
	}

	return list;
}

// delete a node in double list by specifying the owner's name

// switch two nodes in double list based on postion

int main()
{

	FILE* f;
	f = fopen("Account.txt", "r");

	unsigned char buffer[BUFFER_SIZE];
	char sep_list[] = ",\n";

	struct DoubleList DList;
	DList.head = DList.tail = NULL; // mark the double list as empty


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

		// insert the bank account into a double list node
		DList = insertAscending(DList, ba);
	}

	fclose(f);
	return 0;
}
