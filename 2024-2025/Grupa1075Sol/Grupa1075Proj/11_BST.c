#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct Date
{
	char month; // stored as value
	char year;  // stored as value; only last 2 letters are stored
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

void parse_BST_Inorder(BSTNode* node)
{
	if (node != NULL)
	{
		// 1. parse te left subtree same way like the current node
		parse_BST_Inorder(node->left);

		// 2. print out some bank card info
		printf("Card number #%s\n", node->data.card_no);

		// 3. parse the right subtree same way like the current node
		parse_BST_Inorder(node->right);
	}
}

BSTNode* BST_deallocation_Postorder(BSTNode* node)
{
	if (node != NULL)
	{
		
		// 1. parse the left subtree in Postorder to be deallocated
		BST_deallocation_Postorder(node->left);

		// 2. parse the right subtree in Postorder to be deallocated
		BST_deallocation_Postorder(node->right);

		// deallocation of the current node (param node) can be done only
		// after deallocation of both subtrees. That's why the Postorder is the right 
		// way to parse the entire BST in order to be deallocated. Otherwise, we get memory leaks
		// and runtime errors after heap memory free
		// 3. deallocate the current node (param node) with both subtrees as being null pointers

		printf("Card #%s removed fro BST\n", node->data.card_no);
		free(node->data.holder); // deallocate heap memory for card data extension holder
		free(node->data.issuer); // deallocate heap memory for card data extension issuer

		free(node); // deallocate heap memory for the node itself (containing data, left and rigth as fields)
		node = NULL;
	}

	return node; // return to the previous self-call the content of the current node (param node)
}

// count the leaf nodes on a certain BST level
void count_leaf_nodes(BSTNode* node, unsigned char level, unsigned char* count)
{
	if (node != NULL)
	{
		if (level > 0) // current level is above the targeted one
		{
			count_leaf_nodes(node->left, level - 1, count);

			if (level == 1)
			{
				// node is placed on targeted level
				if (node->left == NULL && node->right == NULL)
				{
					//node is a leaf in BST
					*count += 1;
				}
			}

			count_leaf_nodes(node->right, level - 1, count);
		}
		else
		{
			; // no interest to go down the targeted level
		}
	}
}

// save the nodes placed on the path root -> specified card number
struct Node
{
	BSTNode* node_adr;
	struct Node* next;
};

typedef struct Node Node;

Node* insert_node_list(Node* list, BSTNode* node)
{
	Node* temp = list;
	Node* new_node = malloc(sizeof(Node));
	new_node->node_adr = node;
	new_node->next = NULL;
	if (temp != NULL)
	{
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
	else
	{
		list = new_node;
	}
	return list;
}

void save_nodes_path(BSTNode* node, char* card_n, Node** list)
{
	if (node != NULL)
	{
		*list = insert_node_list(*list, node);
		if (strcmp(card_n, node->data.card_no) < 0)
		{
			save_nodes_path(node->left, card_n, list);
		}
		else 
			if (strcmp(card_n, node->data.card_no) > 0)
			{
				save_nodes_path(node->right, card_n, list);
			}
			else
			{
				return; //node cointains the same card no as card_n, we have to stop the chain of calls
			}
	}
	else //deallocate the list since the node with card_n does not exist in the tree
	{
		Node* temp = *list;
		while (temp)
		{
			*list = (*list)->next;
			free(temp);
			temp = *list;
		} 
	}
}

// save the nodes on the same tree level specified as parameter of the function

// delete one single node identified for a specified card number (the key) in the BST

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

	printf("\n\nInorder parsing of the BST:\n");
	parse_BST_Inorder(root);

	printf("\n\nCount the leaf nodes on targeted level:\n");
	unsigned char count = 0;
	count_leaf_nodes(root, 3, &count);
	printf("Number of leaf nodes on targeted level: %u\n", count);

	printf("\n\nSave nodes on the path root->specified node in the tree:\n");
	Node* list = NULL;
	save_nodes_path(root, "6234999912349807", &list);
	printf("\n\nList of nodes on the path root -> card no\n");

	Node* temp = list;
	while(temp)
	{
		printf("Card no %s \n", temp->node_adr->data.card_no);
		temp = temp->next;
	}
	printf("\n\nBST deallocation:\n");
	root = BST_deallocation_Postorder(root);
	printf("\n\nBST after deallocation:\n");
	parse_BST_Inorder(root);

	printf("\n\nList deallocation:\n");
	temp = list;
	while (temp)
	{
		list = list->next;
		free(temp);
		temp = list;
	}
	temp = list;
	printf("\nList after deallocation:\n");
	while (temp)
	{
		printf("Card no %s \n", temp->node_adr->data.card_no);
		temp = temp->next;
	}
}