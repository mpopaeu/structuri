#include "Structs.h"

// maximum of two integeres
int maxim(int a, int b) {
	return a > b ? a : b;
}


// height of (sub)tree r
int h(BalancedNode* r) {
	if (r)
		return 1 + maxim(h(r->left), h(r->right));
	else
		return 0;
}

// balance indicator for node r
void compute_balance(BalancedNode* r) {
	if (r) {
		r->balance = h(r->right) - h(r->left);
	}
}


BalancedNode* rotireSimplaDr(BalancedNode* pivot, BalancedNode* fiuSt) {
	pivot->left = fiuSt->right;
	compute_balance(pivot);
	fiuSt->right = pivot;
	compute_balance(fiuSt);

	return fiuSt;
}

BalancedNode* rotireSimplaSt(BalancedNode* pivot, BalancedNode* fiuDr) {
	pivot->right = fiuDr->left;
	compute_balance(pivot);
	fiuDr->left = pivot;
	compute_balance(fiuDr);

	return fiuDr;
}

BalancedNode* rotireDblStDr(BalancedNode* pivot, BalancedNode* fiuSt) {
	//get the unbalance on the same side
	pivot->left = rotireSimplaSt(fiuSt, fiuSt->right);
	compute_balance(pivot);
	fiuSt = pivot->left;
	//rotation in the pivot
	fiuSt = rotireSimplaDr(pivot, fiuSt);
	compute_balance(fiuSt);

	return fiuSt;
}

BalancedNode* rotireDblDrSt(BalancedNode* pivot, BalancedNode* fiuDr) {
	// get unbalance on the same side
	pivot->right = rotireSimplaDr(fiuDr, fiuDr->left);
	compute_balance(pivot);
	fiuDr = pivot->right;
	// rotation in the pivot
	fiuDr = rotireSimplaSt(pivot, fiuDr);
	compute_balance(fiuDr);

	return fiuDr;
}

BalancedNode* insert_ba_balanced_binary_tree(BalancedNode* r, BankAccount ba, char* insert_flag)
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
				r->left = insert_ba_balanced_binary_tree(r->left, ba, insert_flag);
			}
			else
			{
				// continue on the right
				r->right = insert_ba_balanced_binary_tree(r->right, ba, insert_flag);
			}
		}
	}
	else
	{
		// r is NULL; this is the place to create the new node
		BalancedNode* new_node = (BalancedNode*)malloc(sizeof(BalancedNode)); // allocation of the new node
		new_node->data = ba; // store data from the function input
		new_node->left = new_node->right = NULL; // new node must be leaf in the tree after insertion

		*insert_flag = 1; // flag shows the successful insert operation
		r = new_node; // r is returned updated to the previous call in order overwrite the parent on left OR on right
	}

	// re-balance all upper sub-trees till the root
// this is one single rotation applied for the subtree r
	compute_balance(r);
	if (r->balance == 2) {
		if (r->right->balance == -1) {
			//mixed unbalance rigth-left
			r = rotireDblDrSt(r, r->right);
		}
		else {
			//unbalance to right only
			r = rotireSimplaSt(r, r->right);
		}
	}
	else {
		if (r->balance == -2) {
			if (r->left->balance == 1) {
				//mixed unbalance left-right
				r = rotireDblStDr(r, r->left);
			}
			else {
				//unbalance to left only
				r = rotireSimplaDr(r, r->left);
			}
		}
	}


	return r;
}

void parse_ascending_keys(BalancedNode* r)
{
	if (r != NULL)
	{
		parse_ascending_keys(r->left);
		printf("%s %s %d\n", r->data.iban, r->data.owner_name, r->balance);
		parse_ascending_keys(r->right);
	}
}


int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	char buffer[256];

	BalancedNode* root = NULL;

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
		root = insert_ba_balanced_binary_tree(root, tBankAccount, &flag);
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


	fclose(f);

	return 0;
}
