#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee
{
	unsigned short int id; // 2 bytes
	char* name;			   // 4 bytes (x86 target platform)
	float salary;		   // 4 bytes
	unsigned char age;	   // 1 byte
	char hire_date[11];	   // 11 bytes (including the null byte as string terminator)
	// TOTAL of 22 bytes as sum of fields, but 24 bytes as allocated memory area
};

typedef struct Employee Employee;

struct BSTNode
{
	Employee emp;
	struct BSTNode* left, *right;
};

typedef struct BSTNode BSTNode;


BSTNode* insertEmployeeBST(BSTNode* node, Employee emp, unsigned char *flag_insert)
{
	if (node != NULL)
	{
		if (emp.id < node->emp.id)
		{
			node->left = insertEmployeeBST(node->left, emp, flag_insert);
		}
		else
		{
			if (emp.id > node->emp.id)
			{
				node->right = insertEmployeeBST(node->right, emp, flag_insert);
			}
			else
			{
				*flag_insert = 0; // the employee having same id with the new one already exists in BST
				return node;
			}
		}
	}
	else
	{
		// the final and right place (NULL position within the BST) has touched
		*flag_insert = 1; // successful insertion of new data set  (param emp)
		node = malloc(sizeof(BSTNode));
		node->emp = emp;
		node->left = NULL;
		node->right = NULL;
	}

	return node;
}

void BSTParse(BSTNode* node)
{
	if (node != NULL)
	{
		BSTParse(node->left); // process the nodes from left sub-tree
		printf("%d %s\n", node->emp.id, node->emp.name); // process the node itself
		BSTParse(node->right); // process the nodes from the right sub-tree
	}
}

Employee* searchEmployee(BSTNode* node, unsigned short int search_key)
{
	Employee* emp_result = NULL;
	if (node != NULL)
	{
		if (search_key < node->emp.id)
		{
			emp_result = searchEmployee(node->left, search_key);
		}
		else
		{
			if (search_key > node->emp.id)
			{
				emp_result = searchEmployee(node->right, search_key);
			}
			else
			{
				return &node->emp;
			}
		}
	}

	return emp_result;
}

BSTNode* deallocateBST(BSTNode *node)
{
	if (node != NULL)
	{
		node->left = deallocateBST(node->left);
		node->right = deallocateBST(node->right);

		free(node->emp.name);
		free(node);

		node = NULL;
	}

	return node;
}

BSTNode* deleteNodeBST(BSTNode * node, unsigned short int search_key, Employee* empl)
{
	if (node != NULL)
	{
		if (node->emp.id == search_key)
		{
			// node must be deleted
			// employee's data must be stored by empl

			*empl = node->emp; // save employee's data to be pushed back
			BSTNode* left_subtree = node->left;
			BSTNode* right_subtree = node->right;

			// parse the right sub-tree till the leftmost node with minimum value of the employee's id
			BSTNode* temp = right_subtree;
			while (temp->left != NULL)
				temp = temp->left;

			temp->left = left_subtree;
			free(node); 

			node = right_subtree;
		}
		else
		{
			if (node->emp.id > search_key)
			{
				node->left = deleteNodeBST(node->left, search_key, empl);
			}
			else
			{
				node->right = deleteNodeBST(node->right, search_key, empl);
			}
		}
	}

	return node;
}

// function to delete the leaf nodes where the employee's age is over a threshold 
// specified as input parameter

int main()
{
	BSTNode* root = NULL; // root of the BST


	FILE* f = fopen("Employees.txt", "r"); // fill the structure FILE with needed data to handle access to file

	char buffer[256]; // buffer to store content read from text file
	char seps[] = ",\n"; // list of separators between sub-strings to be identified for mapping the structure Employee

	while (fgets(buffer, sizeof(buffer), f)) // read content from the text file (one single line ended by 0x0d 0x0a (ENTER in Win)
	{
		Employee empl; // local temporary variable to prepare data according to the definition of structure Employee
		char* token = strtok(buffer, seps); // first call to strtok to identify the first token (based on separator list)
		empl.id = atoi(token); // conversion text-to-integer

		token = strtok(NULL, seps); // starting the 2nd call to strtok, the first argument is passed as NULL to continue token identification from last separator point
		empl.name = malloc(strlen(token) + 1); // +1 because the null byte terminator; name is pointer to char, hence the allocation is mandatory
		strcpy(empl.name, token); // there is no conversion

		token = strtok(NULL, seps);
		empl.salary = (float)atof(token); // conversion text-to-float

		token = strtok(NULL, seps);
		empl.age = atoi(token); // conversion text-to-integer

		token = strtok(NULL, seps);
		strcpy(empl.hire_date, token); // hire_date is a compile-time allocated byte array, hence there is storage and copy is enough

		// insert empl data into a Binary Search Tree
		unsigned char insert;
		root = insertEmployeeBST(root, empl, &insert);

		if (insert != 0)
		{
			// insertion took place
			printf("Sucesful insertion of employee: %d\n", empl.id);
		}
		else
		{
			printf("Deallocations to be done because employee with %d already has been inserted into BST\n", empl.id);
			free(empl.name);
		}
	}

	printf("Content of the BST:\n");
	BSTParse(root);

	Employee* pEmp = searchEmployee(root, 848);
	printf("\n/////////////SEARCH operation////////////////\n");
	if (pEmp != NULL)
	{
		printf("Employee data: %d %s\n", pEmp->id, pEmp->name);
	}
	else
	{
		printf("There is no employee having the specified id in searh operation\n");
	}

	// deletae one single node based on search key
	Employee delete_empl;
	delete_empl.name = NULL;
	root = deleteNodeBST(root, 1012, &delete_empl);
	if (delete_empl.name != NULL)
	{
		printf("Extracted employee data: %d %s\n", delete_empl.id, delete_empl.name);
		free(delete_empl.name);
	}
	else
	{
		printf("There is no employee having the specificed search key.\n");
	}
	printf("Content of the BST after deletion based on employee's id:\n");
	BSTParse(root);

	root = deallocateBST(root);
	printf("Content of the BST aftre structure destroying/deallocation:\n");
	BSTParse(root);
	fclose(f);
}