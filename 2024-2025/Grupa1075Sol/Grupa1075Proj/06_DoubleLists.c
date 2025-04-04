#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define CARD_NUMBER_SIZE 16
#define CARD_ARRAY_SIZE 20

struct Date
{
	char month; // stored as value
	char year; // stored as value; only last 2 letters are stored
};

typedef struct Date Date;

struct BankCard
{
	char* holder;	
	char card_no[CARD_NUMBER_SIZE + 1]; 
	Date exp_date;  
	char* issuer;   
	float balance;  
}; 

typedef struct BankCard BankCard;

struct NodeD
{
	BankCard data;
	struct NodeD* next, *prev; 
};

typedef struct NodeD NodeD;

struct DoubleList
{
	NodeD* head, * tail;
}; // structure to handle the both endpoints of the double list: head and tail

typedef struct DoubleList DoubleList;

DoubleList insert_card_double_list(DoubleList list, BankCard data)
{
	NodeD* new_node = malloc(sizeof(NodeD));
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = list.tail; // current tail of the double list; can be NULL when double list is empty

	if (list.tail == NULL)
	{
		// the double is empty
		list.head = new_node;
		list.tail = new_node; // new_node becomes the first, the last and the uniques node in my double list
	}
	else
	{
		// there is one node at least in my double list
		list.tail->next = new_node; // add new_node to the end of the list
		list.tail = new_node; // update the tail of the double list to the new_node added to the list
	}

	return list;
}

void parse_double_list(DoubleList list)
{
	printf("Double list head-to-tail:\n");
	NodeD* temp = list.head;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->data.holder, temp->data.card_no);
		temp = temp->next;
	}

	printf("\nDouble list tail-to-head:\n");
	temp = list.tail;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->data.holder, temp->data.card_no);
		temp = temp->prev;
	}
}

DoubleList delete_head_double_list(DoubleList list)
{

	if (list.head != NULL)
	{
		// there is one node at least in double list
		NodeD* temp = list.head;
		list.head = list.head->next; // update the head of the list to the second node in the list

		if (list.head == NULL)
		{
			// double list becomes empty after delettion
			list.tail = NULL; 
		}
		else
		{
			list.head->prev = NULL;
		}

		free(temp->data.holder); // deallocate string for holder
		free(temp->data.issuer); // deallocate string fo issuer
		free(temp); // deallocate the node iteself
	}

	return list;
}

// swap two nodes in a double list

// deallocate the double list

int main()
{
	FILE* f = fopen("CardData.txt", "r");

	unsigned char buffer[200];
	DoubleList double_list; // local variable to store the head and tail of one single double list data structure

	double_list.head = NULL; // head does not exist for an empty double list
	double_list.tail = NULL; // tail does not exist for an empty double list

	fgets(buffer, sizeof(buffer), f);
	while (!feof(f))
	{
		BankCard card;
		char seps[] = ",/\n";
		char* token = strtok(buffer, seps);
		card.holder = malloc(strlen(token) + 1); // +1 for null byte as terminator
		strcpy(card.holder, token);				 // copy the string token into v_card holder's heap area

		token = strtok(NULL, seps);			// get the vard number string
		strcpy(card.card_no, token);

		token = strtok(NULL, seps);			// get the month
		card.exp_date.month = atoi(token);  // convert string month into integer month
		token = strtok(NULL, seps);			// get the year
		card.exp_date.year = atoi(token);	// convert string year into integer year

		token = strtok(NULL, seps);
		card.issuer = malloc(strlen(token) + 1);
		strcpy(card.issuer, token);

		token = strtok(NULL, seps);		   // get the balance
		card.balance = (float)atof(token); // convert string balance into float balance

		// insert card data into a double list
		double_list = insert_card_double_list(double_list, card);

		// read the next line in the text file CardData.txt
		fgets(buffer, sizeof(buffer), f);
	}

	fclose(f);


	printf("Data content of double list:\n");
	parse_double_list(double_list);

}