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
struct DoubleList delete_node_string(struct DoubleList list, char* name)
{
	struct NodeBankAccount* temp;
	while (list.head && strcmp(list.head->bankAccount.owner, name) == 0)
	{
		temp = list.head;
		list.head = list.head->next;
		list.head->prev = NULL;

		free(temp->bankAccount.owner);
		free(temp);
	}

	if (list.head)
	{
		// stiil there are some nodes in my double list
		// the first node does not contain the bank account with searched owner to be deleted
		temp = list.head->next; // starting with the 2nd node
		while (temp)
		{
			if (strcmp(temp->bankAccount.owner, name) == 0)
			{
				struct NodeBankAccount* p, * q;
				p = temp->prev;
				q = temp->next;

				p->next = q;
				if (q != NULL)
				{
					// temp is not the last node (not on tail of the double list)
					q->prev = p;
				}
				else
				{
					// temp is the last node
					list.tail = p;
				}

				free(temp->bankAccount.owner);
				free(temp);

				temp = q;
			}
			else
			{
				temp = temp->next;
			}
		}
	}
	else
	{
		list.tail = NULL; // the list became empty
	}

	return list;
}

// switch two nodes in double list based on their position

// double list parsing on bi-directional way
void parsing_biway(struct DoubleList list)
{
	struct NodeBankAccount* temp = list.head;
	printf("\nDouble list parsing head->to->tail:\n");
	while (temp)
	{
		printf("%s %.2f\n", temp->bankAccount.owner, temp->bankAccount.balance);

		temp = temp->next;
	}

	temp = list.tail;
	printf("\nDouble list parsing tail->to->head:\n");
	while (temp)
	{
		printf("%s %.2f\n", temp->bankAccount.owner, temp->bankAccount.balance);

		temp = temp->prev;
	}
}

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

	parsing_biway(DList);

	DList = delete_node_string(DList, "Popescu George");
	printf("\nDouble list after deletion:\n");
	parsing_biway(DList);

	return 0;
}
