#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct Employee
{
	char* name;			// 4 bytes
	float salary;		// 4 bytes
	char CNP[14];		// 14 bytes
	char emp_date[11];	// 11 bytes
	unsigned short int no_directs; // 2 bytes
};

typedef struct Employee Employee;

struct NodeBST
{
	Employee emp;
	struct NodeBST* left, *right;
};

typedef struct NodeBST NodeBST;

NodeBST* insertNodeBST(NodeBST *node, Employee data, unsigned char * insert_flag)
{
	if (node != NULL)
	{
		if (strcmp(data.CNP, node->emp.CNP) == -1)
		{
			// data.CMP < node->emp.CNP
			node->left = insertNodeBST(node->left, data, insert_flag);
		}
		else
		{
			if (strcmp(data.CNP, node->emp.CNP) == 1)
			{
				// 1st arg "over" the 2nd argument
				node->right = insertNodeBST(node->right, data, insert_flag);
			}
			else
			{
				// the two strings are identical
				*insert_flag = 0; // insertion does not take place because data has a CNP stored before in BST
				return node; // the function execution is stopped because data.CNP exists in BST and cannot ve added to BST
			}
		}
	}
	else
	{
		// node placed in the NULL position will be replaced by the new node in BST
		NodeBST* newNode = malloc(sizeof(NodeBST));
		newNode->emp = data;
		// new node will be added as leaf within the BST
		newNode->left = NULL;
		newNode->right = NULL;

		*insert_flag = 1;

		return newNode;
	}

	return node;
}


Employee* searchEmployeeBST(NodeBST* node, char* search_key) // search key is the employee's id (CNP)
{
	if (node != NULL)
	{
		if (strcmp(search_key, node->emp.CNP) == -1)
		{
			// search_key < node->emp.CNP
			return searchEmployeeBST(node->left, search_key);
		}
		else
		{
			if (strcmp(search_key, node->emp.CNP) == 1)
			{
				// 1st arg "over" the 2nd argument
				return searchEmployeeBST(node->right, search_key);
			}
			else
			{
				// the two strings are identical
				return &node->emp; 
			}
		}
	}

	return NULL; // the employee date set with search_key as CNP does not exist in BST
}


void Inorder(NodeBST* node)
{
	if (node != NULL)
	{
		Inorder(node->left); // process nodes on the left sub-tree

		printf("%s %s\n", node->emp.CNP, node->emp.name); // process the current node

		Inorder(node->right); // proces nodes on the right sub-tree
	}
}

NodeBST* deleteBST(NodeBST* node)
{
	if (node != NULL)
	{
		node->left = deleteBST(node->left); // delete nodes on the left sub-tree
		node->right = deleteBST(node->right); // delete nodes on the right sub-tree

		free(node->emp.name); // deallocate employee's extension into heap mem
		free(node);   // deallocate the node itself

		node = NULL;
	}

	return node;
}

// no of leaves

// height of the BST

// nodes places on a certain level within the BST

// count leaves over a certain level within the BST

// no of emplyess having salary under average

int main()
{
	FILE* f;

	f = fopen("Employees.txt", "r");

	NodeBST* root = NULL;  // root - mem address to access the tree root (acces point to BST)

	char buffer[256];
	char sep_list[] = ",\n";
	while (fgets(buffer, sizeof(buffer), f)) // buffer stores one single line (0x0d 0x0a as ENTER in Win) taken from file
	{
		Employee temp; // Stack seg memory location to be filled in according to Employee structure definition
		char* token = strtok(buffer, sep_list); // parsing buffer to identify tokens (sub-strings)
		// token is a pointer storing the stack seg memory address in buffer where the current token starts from
		temp.name = malloc(strlen(token) + 1); // allocate heap seg to store the employee's name
		strcpy(temp.name, token); // copy the string for the employee's name into byte array allocated before

		token = strtok(NULL, sep_list); // first arg as NULL to continue the splitting of buffer into tokens
		temp.salary = (float)atof(token); // conversion text-to-binary (float)

		token = strtok(NULL, sep_list);
		strcpy(temp.CNP, token); // copy string into byte array CNP; no allocation is needed (see definition of CNP)

		token = strtok(NULL, sep_list);
		strcpy(temp.emp_date, token); // copy string into byte array emp_date; no allocation needed before

		token = strtok(NULL, sep_list);
		temp.no_directs = atoi(token); // conversion text-to-binary (integer)

		// insert employee's data into BST
		unsigned char insert_flag;
		root = insertNodeBST(root, temp, &insert_flag);

		if (insert_flag == 0)
		{
			printf("Insertion has not been done due to duplicate key as CNP: %s %s.\n", temp.CNP, temp.name);
			free(temp.name); // to avoid mem leaks, temp being over-written by the next employee date set read from file
		}
	}

	fclose(f);


	printf("BST content after inorder parsing:\n");
	Inorder(root);

	Employee* pEmp = searchEmployeeBST(root, "1901224080650");
	printf("\n//////////////// SEARCH BASED on key ///////////////\n");
	if (pEmp != NULL)
	{
		printf("Employee has been found: %s %s\n", pEmp->CNP, pEmp->name);
	}
	else
	{
		printf("There is no employee with CNP provdided as argument\n");
	}

	root = deleteBST(root);
	printf("\n//////////////// BST DEALLOCATION ///////////////\n");
	printf("BST content after tree deallocation:\n");
	Inorder(root);

	return 0;
}