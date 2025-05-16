#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct Date
{
	char month; // stored as value
	char year; // stored as value; only last 2 letters are stored
};

typedef struct Date Date;

#define CARD_NUMBER_SIZE 16

struct BankCard
{
	char* holder;	// 4 bytes
	char card_no[CARD_NUMBER_SIZE + 1]; // 17 bytes
	Date exp_date;  // 2 bytes -> no alignment (month and year are char)
	char* issuer;   // 4 bytes -> enforce alignment by adding +1 byte to card_no
	float balance;  // 4 bytes
}; // 31 bytes (sum of all structure fields); actual length is 32 bytes

typedef struct BankCard BankCard;

struct BSTNode
{
	BankCard data;
	struct BSTNode* left, *right; 
};

typedef struct BSTNode BSTNode;

BSTNode* insert_node_BST(BSTNode *node, BankCard data, unsigned char * insert_flag)
{
	// node is a BST node placed on the path from the BST root node till a null position in BST
	if (node != NULL)
	{
		// there is a current node to be checked against the key for data I want to insert in BST
		// I have to check and maybe continue to search the place to insert the new data
		if (strcmp(data.card_no, node->data.card_no) < 0)
		{
			node->left = insert_node_BST(node->left, data, insert_flag); // continue to searvh for the insertion place on the left subtree
		}
		else
		{
			if (strcmp(data.card_no, node->data.card_no) > 0)
			{
				node->right = insert_node_BST(node->right, data, insert_flag); // continue to searvh for the insertion place on the left subtree
			}
			else
			{
				// the keys (stored in BST and the new one to be inserted) are the same
				// cancel the insert operation because BST does not allow duplicated keys
				*insert_flag = 0; 
			}
		}
	}
	else
	{
		// a null position is toouched down in the BST
		// this is the place where the new data will be put and glued to the BST
		node = malloc(sizeof(BSTNode)); // alocation of the new node
		node->data = data;
		node->left = NULL;
		node->right = NULL;

		*insert_flag = 1; // succesful allocation/insertion
	}

	return node;
}

int main()
{
	BSTNode* root = NULL; // mandatory to mark an empty Binary Search Tree
	unsigned char buffer[200];
	FILE* f = fopen("CardData.txt", "r");

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

		// insert card data into a Binary Search Tree
		unsigned char was_inserted = 0;
		root = insert_node_BST(root, card, &was_inserted);

		if (was_inserted != 0)
		{
			printf("Card %s has been succesfully inserted into BST.\n", card.card_no);
		}
		else
		{
			printf("Card %s has not succesfully inserted into BST.\n", card.card_no);
			// follow-up actions
			free(card.holder);
			free(card.issuer);
		}

		// read the next line in the text file CardData.txt
		fgets(buffer, sizeof(buffer), f);
	}

	fclose(f);
}