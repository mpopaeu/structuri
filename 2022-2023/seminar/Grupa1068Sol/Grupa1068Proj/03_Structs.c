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

struct Node
{
	char currency[4];
	double total_balance;
	struct Node *next;
};
struct NodeBankAccount {
	struct BankAccount bankAccount;
	struct NodeBankAccount* next;
};

struct NodeStack
{
	struct NodeBankAccount* node_address;
	struct NodeStack* next;
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

// insert a node into a simple list ensuring an ascending sorting of the nodes based on balance
struct NodeBankAccount* insertAscending(struct NodeBankAccount* first, struct BankAccount bankAccount) {
	struct NodeBankAccount* newNode = (struct NodeBankAccount*)malloc(sizeof(struct NodeBankAccount));
	newNode->bankAccount = bankAccount;
	newNode->bankAccount.owner = (char*)malloc(sizeof(char) * (strlen(bankAccount.owner) + 1));
	strcpy(newNode->bankAccount.owner, bankAccount.owner);
	if (first) {
		if (newNode->bankAccount.balance < first->bankAccount.balance) {
			newNode->next = first;
			first = newNode;
		}

		else {
			struct NodeBankAccount* t = first;

			while (t->next && t->next->bankAccount.balance < newNode->bankAccount.balance) {
				t = t->next;
			}

			newNode->next = t->next;
			t->next = newNode;

		}
	}
	else {
		newNode->next = NULL;
		first = newNode;
	}
	return first;
}

struct NodeStack* push(struct NodeStack* stack, struct NodeBankAccount* add_NBA)
{
	struct NodeStack* newNode = (struct NodeStack*)malloc(sizeof(struct NodeStack));
	newNode->node_address = add_NBA;
	newNode->next = stack;

	return newNode; // new top of the stack
}

struct NodeStack* pop(struct NodeStack* stack, struct NodeBankAccount* *get_NBA)
{
	if (stack)
	{
		*get_NBA = stack->node_address;
		struct NodeStack* t = stack;
		stack = stack->next; // new top of the stack

		free(t);
	}
	return stack;
}


//struct BankAccount function_1()
//{
//	//....
//}

// all operations above on double lists

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


	// create a list of bank accounts (from the array vba) where the nodes are sorted ascending
	struct NodeBankAccount* listBA = NULL;
	for (i = 0; i < size; i++) {
		listBA = insertAscending(listBA, vba[i]);
	}
	struct NodeBankAccount* t2 = listBA;
	printf("ascending list of bank accounts: \n");
	while (t2) {
		printf("%s, %.2f\n", t2->bankAccount.iban, t2->bankAccount.balance);
		
		t2 = t2->next;
	}


	// build the stack of addresses of node in listBA
	t2 = listBA;
	struct NodeStack* stack = NULL;
	while (t2)
	{
		stack = push(stack, t2);

		t2 = t2->next;
	}

	printf("descending processing of nodes in list of bank accounts: \n");
	while (stack)
	{
		stack = pop(stack, &t2);

		printf("%s, %.2f\n", t2->bankAccount.iban, t2->bankAccount.balance);
	}

	fclose(f);


	// deallocate all needed dynamic data structures
	return 0;
}