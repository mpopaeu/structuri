#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct BankAccount
{
	char iban[21]; 
	char* owner_name;
	float balance;
	char currency[4]; 
};

struct NodeBalancedTree
{
	struct BankAccount info;
	char balance;
	struct NodeBalancedTree* left, * right;
};

typedef struct BankAccount BankAccount;
typedef struct NodeBalancedTree NodeBalancedTree;

// maximum 
int maxim(int a, int b) {
	return a > b ? a : b;
}


// height of (sub)tree r
int h(NodeBalancedTree* r) {
	if (r)
		return 1 + maxim(h(r->left), h(r->right));
	else
		return 0;
}

// balance indicator for node r
void compute_balance(NodeBalancedTree* r) {
	if (r) {
		r->balance = h(r->right) - h(r->left);
	}
}


NodeBalancedTree* rotireSimplaDr(NodeBalancedTree* pivot, NodeBalancedTree* fiuSt) {
	pivot->left = fiuSt->right;
	compute_balance(pivot);
	fiuSt->right = pivot;
	compute_balance(fiuSt);

	return fiuSt;
}

NodeBalancedTree* rotireSimplaSt(NodeBalancedTree* pivot, NodeBalancedTree* fiuDr) {
	pivot->right = fiuDr->left;
	compute_balance(pivot);
	fiuDr->left = pivot;
	compute_balance(fiuDr);

	return fiuDr;
}

NodeBalancedTree* rotireDblStDr(NodeBalancedTree* pivot, NodeBalancedTree* fiuSt) {
	//get the unbalance on the same side
	pivot->left = rotireSimplaSt(fiuSt, fiuSt->right);
	compute_balance(pivot);
	fiuSt = pivot->left;
	//rotation in the pivot
	fiuSt = rotireSimplaDr(pivot, fiuSt);
	compute_balance(fiuSt);

	return fiuSt;
}

NodeBalancedTree* rotireDblDrSt(NodeBalancedTree* pivot, NodeBalancedTree* fiuDr) {
	// get unbalance on the same side
	pivot->right = rotireSimplaDr(fiuDr, fiuDr->left);
	compute_balance(pivot);
	fiuDr = pivot->right;
	// rotation in the pivot
	fiuDr = rotireSimplaSt(pivot, fiuDr);
	compute_balance(fiuDr);

	return fiuDr;
}


NodeBalancedTree* insert_ba_tree(NodeBalancedTree* r, BankAccount tAccount, unsigned char* insert_flag)
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
		NodeBalancedTree* new_node = (NodeBalancedTree*)malloc(sizeof(NodeBalancedTree));
		new_node->info = tAccount;
		new_node->left = NULL;
		new_node->right = NULL;

		*insert_flag = 1; // the insertion is done
		r = new_node;
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

void parse_tree(NodeBalancedTree* r)
{
	if (r != NULL)
	{
		parse_tree(r->left);
		printf("%s %s %d\n", r->info.iban, r->info.owner_name, r->balance);
		parse_tree(r->right);
	}
}

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	NodeBalancedTree* root = NULL; // an empty binary search tree
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

	printf("\nThe Baanced BST after creation:\n");
	parse_tree(root);

	// delete a node in a balanced BST based on key provided to the argument list

	fclose(f);
	return 0;
}