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

struct NodeBST
{
	struct BankAccount info;
	struct NodeBST* left, *right;
};


struct Node
{
	char IBAN[21];
	struct Node* next;
};

typedef struct BankAccount BankAccount;
typedef struct NodeBST NodeBST;
typedef struct Node Node;

NodeBST* insert_ba_tree(NodeBST* r, BankAccount tAccount, unsigned char *insert_flag)
{
	if (r != NULL)
	{
		// the search of the NULL place in the tree is continuing
		if (strcmp(r->info.iban, tAccount.iban) > 0)
		{
			// go on the below level on the left
			r->left = insert_ba_tree(r->left, tAccount, insert_flag);
		}
		else
		{
			if (strcmp(r->info.iban, tAccount.iban) < 0)
			{
				// go to the right subtree
				r->right = insert_ba_tree(r->right, tAccount, insert_flag);
			}
			else
			{
				// there is the key already stored within the BST
				*insert_flag = 0; // the insertion is cancelled
			}
		}
	}
	else
	{
		// this is the place where the new node must be allocated and initialized
		NodeBST* new_node = (NodeBST*)malloc(sizeof(NodeBST));
		new_node->info = tAccount;
		new_node->left = NULL;
		new_node->right = NULL;

		*insert_flag = 1; // the insertion is done
		r = new_node;
	}

	return r;
}

void parse_tree(NodeBST *r)
{
	if (r != NULL)
	{
		parse_tree(r->left);
		printf("%s %s\n", r->info.iban, r->info.owner_name);
		parse_tree(r->right);
	}
}

// create a simple list with IBANs of the bank accounts being
// on the reverse path from a certain node in BST up to the root of the BST

Node* search_reverse_path(NodeBST* r, char* search_IBAN)
{

}

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	NodeBST* root = NULL; // an empty binary search tree
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

		// insert BankAccount data (tAccount) into binary search tree
		unsigned char insert_flag = 0;
		root = insert_ba_tree(root, tAccount, &insert_flag);

		if (insert_flag != 0)
		{
			printf("Bank account %s has been sucessfully inserted!\n", tAccount.iban);
		}
		else
		{
			printf("Bank account %s has not been inserted!\n", tAccount.iban);
			free(tAccount.owner_name); // deallocate because the bank account was not inserted into BST
		}
	}
	
	printf("\nThe BST after creation:\n");
	parse_tree(root);

	// count BAs with the same currency within the BST
	// count BAs as leafs within the BST

	Node* head = search_reverse_path(root, "RO98BTRL010101432168");
	if (head != NULL)
	{
		// the bank account data was found out within BST
	}
	else
	{
		// the bank account data with the specified IBAN is not stored by BST
	}

	// BST deallocation

	fclose(f);
	return 0;
}