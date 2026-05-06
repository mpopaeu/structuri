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


BSTNode* insertEmployeeBST(BSTNode* node, Employee emp)
{
	if (node != NULL)
	{
		if (emp.id < node->emp.id)
		{
			node->left = insertEmployeeBST(node->left, emp);
		}
		else
		{
			if (emp.id > node->emp.id)
			{
				node->right = insertEmployeeBST(node->right, emp);
			}
			else
			{
				return node;
			}
		}
	}
	else
	{
		// the final and right place (NULL position within the BST) has touched
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
		root = insertEmployeeBST(root, empl);
		
	}

	printf("Content of the BST:\n");
	BSTParse(root);

	fclose(f);
}