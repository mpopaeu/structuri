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

void parse_ascending_keys(NodeBST* r)
{
	if (r != NULL)
	{
		parse_ascending_keys(r->left);
		printf("%s %s\n", r->data.iban, r->data.owner_name);
		parse_ascending_keys(r->right);
	}
}

NodeBST* deallocate_BST(NodeBST* r)
{
	if (r != NULL)
	{
		r->left = deallocate_BST(r->left);
		r->right = deallocate_BST(r->right);

		// we may dealocate the current node r because r->left and r->right were deallocate by above calls
		free(r->data.owner_name);
		free(r->data.currency);
		free(r);

		r = NULL;
	}

	return r;
}


BankAccount* search_BST_key(NodeBST* r, char* iban_key)
{
	if (r != NULL)
	{
		if (strcmp(r->data.iban, iban_key) == 0)
		{
			return &(r->data); // the bank account data exist in the tree and returned to the caller
		}
		else
		{
			if (strcmp(r->data.iban, iban_key) > 0)
			{
				// continue on the left
				return search_BST_key(r->left, iban_key);
			}
			else
			{
				// continue on the right
				return search_BST_key(r->right, iban_key);
			}
		}
	}

	return NULL;
}

NodeBST* delete_BST_node(NodeBST* r, char* iban_key, BankAccount* out_data)
{
	if (r != NULL)
	{
		if (strcmp(r->data.iban, iban_key) == 0)
		{
			// the node has been identifiied and must be deleted from BST
			if (r->left && r->right)
			{
				// r has 2 child (case #3)
			}
			else
			{
				if (r->left == NULL && r->right == NULL)
				{
					// r is leaf (case #1)
				}
				else
				{
					// r has one single child (case #2)
					// could be lef OR right
				}
			}
		}
		else
		{
			if (strcmp(r->data.iban, iban_key) > 0)
			{
				// continue to the left
				r->left = delete_BST_node(r->left, iban_key, out_data);
			}
			else
			{
				// continue to the right
				r->right = delete_BST_node(r->right, iban_key, out_data);
			}
		}
	}

	return r;
}

// count leaves on a certain level within a BST
unsigned short int count_leaves_level(NodeBST* r, unsigned short int level)
{
	if (r)
	{
		if (level == 1)
		{
			if (r->left == NULL && r->right == NULL)
			{
				return 1;
			}
		}
		else
		{
			if (level > 1)
			{
				return count_leaves_level(r->left, level - 1) + count_leaves_level(r->right, level - 1);
			}
		}
	}
	return 0;
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

	printf("\nPARSING: Content of BST:\n");
	parse_ascending_keys(root);

	// search bank account data based on BST key (IBAN)
	BankAccount *pBankAccount = NULL;
	pBankAccount = search_BST_key(root, "RO04BRDE1234000000999011");
	if (pBankAccount != NULL)
	{
		printf("\nSEARCH: Bank account data has been found out: %s %s\n", pBankAccount->iban, pBankAccount->owner_name);
	}
	else
	{
		printf("\nSEARCH: There is no Bank Account data based on iban key provided to search.\n");
	}

	unsigned short int leaves = count_leaves_level(root, 6);
	printf("No. of leaves = %hu\n", leaves);

	// deallocate the BST
	root = deallocate_BST(root);

	printf("\nDEALLOCATION: Content of BST after deallocation:\n");
	parse_ascending_keys(root);

	fclose(f);

	return 0;
}
