#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct BankAccount {
	char iban[25];
	char* owner;
	float balance;
	char currency[4];
};

struct NodBST {
	struct BankAccount ba;
	struct NodBST* left, * right;
};


struct NodBST* insert_node(struct NodBST* r, struct BankAccount bank_account, unsigned char* er)
{
	if (r == NULL) {
		struct NodBST* nou = (struct NodBST*)malloc(sizeof(struct NodBST));
		nou->right = NULL;
		nou->left = NULL;
		nou->ba = bank_account;
		r = nou;
	}
	else if (strcmp(r->ba.iban, bank_account.iban) == 0) *er = 1;
	else if (strcmp(r->ba.iban, bank_account.iban) > 0)
		r->left = insert_node(r->left, bank_account, er);
	else
		r->right = insert_node(r->right, bank_account, er);
	return r;
}

void inorder(struct NodBST* r)
{
	if (r) {
		inorder(r->left);
		printf("\n%s %s\n", r->ba.iban, r->ba.owner);
		inorder(r->right);
	}
}

int main() {

	struct BankAccount ba;
	struct NodBST* root = NULL;

	FILE* f;
	f = fopen("Accounts.txt", "r");

	char* token, buffer[LINESIZE], sep_list[] = ",\n";

	while (fgets(buffer, sizeof(buffer), f)) {
		token = strtok(buffer, sep_list); // owner's name
		ba.owner = (char*)malloc(strlen(token) + 1);
		strcpy(ba.owner, token); // there is no conversion

		token = strtok(NULL, sep_list);
		strcpy(ba.iban, token); // no conversion; text-to-text

		token = strtok(NULL, sep_list);
		ba.balance = (float)atof(token); // conversion text-to-binary(as float)

		token = strtok(NULL, sep_list);
		strcpy(ba.currency, token); // no conversion; text-to-text

		unsigned char error = 0;
		root = insert_node(root, ba, &error);
		if (error == 1)
		{
			printf("Insertion failed - duplicated IBAN.\n");
		}
		else
		{
			printf("Successful insert operation into the binary search tree.\n");
		}
	}

	fclose(f);

	printf("\nParse the binary search tree");
	inorder(root);

	// stergere nod in arbore binar de cautare
	// dezalocare structura arbore binar de cautare

	return 0;
}

