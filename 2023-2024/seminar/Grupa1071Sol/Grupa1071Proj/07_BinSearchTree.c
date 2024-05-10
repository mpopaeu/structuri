#include "Structs.h"


NodeBST* insert_ba_binary_search_tree(NodeBST* r, BankAccount ba, char *insert_flag)
{
	if (r != NULL)
	{
		// r exists, so we have to continue to search the place where the node must be added to the tree
		if (strcmp(r->data.iban, ba.iban) == 0)
		{
			*insert_flag = 0; // no insertion due to duplicated key within the tree
		}
		else
		{
			if (strcmp(r->data.iban, ba.iban) > 0)
			{
				// continue on the left
				r->left = insert_ba_binary_search_tree(r->left, ba, insert_flag);
			}
			else
			{
				// continue on the right
				r->right = insert_ba_binary_search_tree(r->right, ba, insert_flag);
			}
		}
	}
	else
	{
		// r is NULL; this is the place to create the new node
		NodeBST* new_node = (NodeBST*)malloc(sizeof(NodeBST)); // allocation of the new node
		new_node->data = ba; // store data from the function input
		new_node->left = new_node->right = NULL; // new node must be leaf in the tree after insertion

		*insert_flag = 1; // flag shows the successful insert operation
		r = new_node; // r is returned updated to the previous call in order overwrite the parent on left OR on right
	}

	return r;
}

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	char buffer[256];

	NodeBST* root = NULL;

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

		// insert tBankAccount data into binary search tree
		char flag;
		root = insert_ba_binary_search_tree(root, tBankAccount, &flag);
		if (flag == 1)
		{
			printf("Succesful insertion: %s %s\n", tBankAccount.iban, tBankAccount.owner_name);
		}
		else
		{
			printf("Insertion has been failed!\n");
			// bank account not added to the tree
			// deallocate al heap memory location used by tBankAccount
			free(tBankAccount.currency);
			free(tBankAccount.owner_name);
		}
	}


	fclose(f);

	return 0;
}
