#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define CARD_NUMBER_LENGTH 16
#define EXPIRING_DATE_FORMAT_LENGTH 5 // MM/YY

struct BankCard
{
	char* holder;
	char card_no[CARD_NUMBER_LENGTH + 1];
	float balance;
	char exp_date[EXPIRING_DATE_FORMAT_LENGTH + 1];
	char* currency;
};

typedef struct BankCard BankCard;

struct BSTNode
{
	BankCard data;
	struct BSTNode* left, *right; 
};

typedef struct BSTNode BSTNode;

BSTNode* insert_node_BST(BSTNode *node, BankCard data, unsigned char* success_flag)
{
	if (node != NULL)
	{
		if (strcmp(data.card_no, node->data.card_no) < 0)
		{
			node->left = insert_node_BST(node->left, data, success_flag); // continue to search on the left subtree
		}
		else
		{
			if (strcmp(data.card_no, node->data.card_no) > 0)
			{
				node->right = insert_node_BST(node->right, data, success_flag); // continue to search on the right subtree
			}
			else
			{
				// there is a duplicated key in BST
				// drop off the insertion
				*success_flag = 0;
			}
		}
	}
	else
	{
		// we get to to the null position where the new node must be added to the tree structure
		node = malloc(sizeof(BSTNode));

		node->data = data;
		node->left = NULL;
		node->right = NULL;

		*success_flag = 1;
	}

	return node; // return the current node to be placed on the left/right of its parent in the previous call in the chain
}

void parse_BST_Inorder(BSTNode* node)
{
	if (node != NULL)
	{
		// 1. parse the left subtree in the same approach (recursivelly)
		parse_BST_Inorder(node->left);

		// 2. process the node
		printf("Card no: %s\n", node->data.card_no);

		// 3. parse same way on the right subtree
		parse_BST_Inorder(node->right);
	}
}


BSTNode* deallocate_BST_Postorder(BSTNode* node)
{
	if (node != NULL)
	{
		// 1. parse the left subtree
		node->left = deallocate_BST_Postorder(node->left);

		// 2. parse the right subtree
		node->right = deallocate_BST_Postorder(node->right);

		// 3. deallocate the current node
		printf("Card %s is deallocationg\n", node->data.card_no);
		free(node->data.currency);	// deallocate currency extension to heap
		free(node->data.holder);	// deallocate holder extension to heap
		free(node);			// deallocate the BST node

		node = NULL;
	}

	return node;
}

// number of nodes on a certain level specified as parameter

// number of nodes placed on the path from root till a certain node specified by the key

// number of leafs placed on the last level of the BST

int main()
{
	FILE* f = fopen("CardData.txt", "r");

	BSTNode* root = NULL; // initially, the BST has no nodes

	unsigned char buffer[200];
	while (fgets(buffer, sizeof(buffer), f))
	{
		BankCard card;
		char seps[] = ",\n";
		char* token = strtok(buffer, seps); // splitting started from the beginning of buffer array
		strcpy(card.card_no, token);

		token = strtok(NULL, seps); // continue the splitting of buffer from the current point
		strcpy(card.exp_date, token);

		token = strtok(NULL, seps); // continue the splitting of buffer from the current point
		card.holder = malloc(strlen(token) + 1);
		strcpy(card.holder, token);

		token = strtok(NULL, seps); // continue the splitting of buffer from the current point
		card.currency = malloc(strlen(token) + 1);
		strcpy(card.currency, token);

		token = strtok(NULL, seps); // continue the splitting of buffer from the current point
		card.balance = (float)atof(token);

		// insert card data in BST
		unsigned char inserted_flag;
		root = insert_node_BST(root, card, &inserted_flag);

		if (inserted_flag != 0)
		{
			printf("Card no# %s has been succesfully inserted into BST.\n", card.card_no);
		}
		else
		{
			printf("Card no# %s has NOT successfully inserted into BST.\n", card.card_no);

			// deallocate heap memory extensions for card data components are not used by BST
			// because data has not been inserted into BST
			free(card.holder);
			free(card.currency);
		}
	}

	fclose(f);

	printf("\nBST just after building (inorder parsing):\n");
	parse_BST_Inorder(root);

	// deallocate the BST
	printf("\nBST deallocation just started:\n");
	root = deallocate_BST_Postorder(root);
	printf("\nBST just deallocated (inorder parsing):\n");
	parse_BST_Inorder(root);
}
