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

struct NodAVL {
	struct BankAccount ba;
	int GE;
	struct NodAVL* left, * right;
};

// maximum valuar for two integers 
int maxim(int a, int b) {
	return a > b ? a : b;
}

typedef struct BankAccount BankAccount;
typedef struct NodAVL NodAVL;

// subtree height
int h(struct NodAVL* r) {
	if (r)
		return 1 + maxim(h(r->left), h(r->right));
	else
		return 0;
}


// balance degree
void calculGENod(struct NodAVL* r) {
	if (r) {
		//prelucrare (calcul GE)
		r->GE = h(r->left) - h(r->right);
	}
}

// rotire simpla la dreapta (dezechilibru de tip -2, -1)
NodAVL* rotireSimplaDr(NodAVL* pivot, NodAVL* fiuSt) {
	pivot->left = fiuSt->right;
	calculGENod(pivot);
	fiuSt->right = pivot;
	calculGENod(fiuSt);

	return fiuSt;
}

// rotire simpla la stanga (dezechilibru de tip +2, +1)
NodAVL* rotireSimplaSt(NodAVL* pivot, NodAVL* fiuDr) {
	pivot->right = fiuDr->left;
	calculGENod(pivot);
	fiuDr->left = pivot;
	calculGENod(fiuDr);

	return fiuDr;
}

// rotire dubla stanga-dreapta
NodAVL* rotireDblStDr(NodAVL* pivot, NodAVL* fiuSt) {
	//aducerea dezechilibrului pe aceeasi directie
	pivot->left = rotireSimplaSt(fiuSt, fiuSt->right);
	calculGENod(pivot);
	fiuSt = pivot->left;
	//rotire propriu-zisa in pivot
	fiuSt = rotireSimplaDr(pivot, fiuSt);
	calculGENod(fiuSt);

	return fiuSt;
}

// rotire dubla dreapta-stanga
NodAVL* rotireDblDrSt(NodAVL* pivot, NodAVL* fiuDr) {
	// aducerea dezechilibrului pe aceeasi directie
	pivot->right = rotireSimplaDr(fiuDr, fiuDr->left);
	calculGENod(pivot);
	fiuDr = pivot->right;
	// rotire propriu-zisa in pivot
	fiuDr = rotireSimplaSt(pivot, fiuDr);
	calculGENod(fiuDr);

	return fiuDr;
}

struct NodAVL* insert_node(struct NodAVL* r, struct BankAccount bank_account, unsigned char* er)
{
	if (r == NULL) {
		struct NodAVL* nou = (struct NodAVL*)malloc(sizeof(struct NodAVL));
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

	// recalculez grad de echilibru pt nodul curent
	calculGENod(r);
	if (r->GE == 2) {
		if (r->right->GE == -1) {
			//dezechilibru dreapta-stanga
			r = rotireDblDrSt(r, r->right);
		}
		else {
			//dezechilibru dreapta
			r = rotireSimplaSt(r, r->right);
		}
	}
	else {
		if (r->GE == -2) {
			if (r->left->GE == 1) {
				//dezechilibru combinat stanga-dreapta
				r = rotireDblStDr(r, r->left);
			}
			else {
				//dezechilibru stanga
				r = rotireSimplaDr(r, r->left);
			}
		}
	}

	return r;
}

void inorder(struct NodAVL* r)
{
	if (r) {
		inorder(r->left);
		printf("\n%s %d\n", r->ba.iban, r->GE);
		inorder(r->right);
	}
}

int main() {

	struct BankAccount ba;
	struct NodAVL* root = NULL;

	FILE* f;
	f = fopen("Account.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list); // first token (iban) is starting from adress token
		strcpy(ba.iban, token); // iban from the file is copied into ba.iban (it is a text, no conversion)

		token = strtok(NULL, sep_list);
		ba.owner = malloc(strlen(token) + 1);
		strcpy(ba.owner, token); // no conversion for the owner's name

		token = strtok(NULL, sep_list);
		ba.balance = (float)atof(token); // cpnversion from ASCII to float internal represetation

		token = strtok(NULL, sep_list);
		strcpy(ba.currency, token); // no conversion for currency

		unsigned char error;
		root = insert_node(root, ba, &error);
		if (error == 1)
		{
			printf("Insertion did not occur - duplicated IBAN.\n");
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

