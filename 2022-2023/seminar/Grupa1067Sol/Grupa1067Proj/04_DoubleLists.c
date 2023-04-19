#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define ACCOUNT_NUMBER 20

struct BankAccount
{
	char* owner;
	char iban[25]; // + 1 for string standard terminat (the byte 0x00 at phisical level)
	float balance;
	char currency[4];
};

struct BankAccountNode
{
	struct BankAccount ba;
	struct BankAccountNode *next, *prev;
};

struct DoubleList
{
	struct BankAccountNode* head, * tail;
};

struct DoubleList insertSortedList(struct DoubleList list, struct BankAccount ba_data)
{
	struct BankAccountNode* newNode = (struct BankAccountNode*)malloc(sizeof(struct BankAccountNode));
	newNode->ba = ba_data;

	if (list.head == NULL)
	{
		// the list is empty; newNode will be the single node in the list
		newNode->next = newNode->prev = NULL;
		list.head = list.tail = newNode;
	}
	else
	{
		// there is one node at least
		if (list.head->ba.balance > newNode->ba.balance)
		{
			// newNode must be inserted before the actual starting node of the list (list.head)
			newNode->next = list.head;
			newNode->prev = NULL;
			list.head->prev = newNode; // the actual head of the list becomes the 2nd node after insertion
			list.head = newNode; // the new head of the list
		}
		else
		{
			struct BankAccountNode* t = list.head;
			while (t->next && t->next->ba.balance < newNode->ba.balance)
			{
				t = t->next;
			}

			if (t->next)
			{
				// insertion is done within the list
				struct BankAccountNode* s = t->next;
				newNode->next = s;
				newNode->prev = t;
				t->next = newNode;
				s->prev = newNode;
			}
			else
			{
				// insertion done at the end of the list
				newNode->next = NULL;
				newNode->prev = list.tail;
				list.tail->next = newNode; // next node of the actual tail will be newNode after insertion
				list.tail = newNode; // update the tail of the double list
			}
		}
	}

	return list;
}

// deletion of a node by specifing the currency

// switch 2 nodes based on their positions in the list
// switch implemented by changing the next and prev relations

int main()
{
	FILE* f;
	f = fopen("Accounts.txt", "r");

	unsigned char buffer[BUFFER_SIZE];
	char sep_list[] = ",";

	struct DoubleList dList;
	dList.head = dList.tail = NULL; // initially, the double list is empty

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

		// insert data loaded into ba as a node in double list dList
		dList = insertSortedList(dList, ba);
	}

	fclose(f);

	// parsing the double list
	struct BankAccountNode* t = dList.head;
	printf("Double list head to tail:\n");
	while (t)
	{
		printf(" %s %.2f\n", t->ba.owner, t->ba.balance);
		t = t->next;
	}

	t = dList.tail;
	printf("\nDouble list tail to head:\n");
	while (t)
	{
		printf(" %s %.2f\n", t->ba.owner, t->ba.balance);
		t = t->prev;
	}

	// deallocate the double list

	return 0;
}
