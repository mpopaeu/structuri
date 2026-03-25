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

struct DNode
{
	Employee emp;
	struct DNode* next, *prev;
};

typedef struct DNode DNode;

struct DoubleList // pack the endpoints into a structure
{
	DNode* first, * last;
};

typedef struct DoubleList DoubleList;

DoubleList insertNodeEnd(DoubleList list, Employee empl)
{
	DNode* new_node = malloc(sizeof(DNode));
	new_node->emp = empl;
	new_node->next = NULL; // new_node will be the last one in double list
	new_node->prev = list.last;

	if (list.first == NULL)
	{
		list.first = list.last = new_node; // new_node will be the first, the last and the unique node in double list
	}
	else
	{
		// there is a node at least in the double list
		list.last->next = new_node;
		list.last = new_node;
	}

	return list;
}

void parseDList(DoubleList list)
{
	printf("Double List first->last:\n");
	DNode* t = list.first;
	while (t != NULL)
	{
		printf("%d %s\n", t->emp.id, t->emp.name);
		t = t->next;
	}

	printf("\nDouble List last->first:\n");
	t = list.last;
	while (t)
	{
		printf("%d %s\n", t->emp.id, t->emp.name);
		t = t->prev;
	}
}

DoubleList deleteNodeEnd(DoubleList list)
{
	if (list.first)
	{
		// double list contains one node at least
		DNode* t = list.last; // t is the last node to be deleted

		if (t == list.first)
		{
			// t is also first node in the double list
			// after deletion of t, double list becomes empty
			free(t->emp.name); // deallocate the extension from employee stored by t
			free(t);		   // deallocate the node itself
			list.first = list.last = NULL;
		}
		else
		{
			list.last = t->prev; // update the last node of the double list to be the one before the current last one
			list.last->next = NULL;

			free(t->emp.name);
			free(t);
		}
	}
	return list;
}

int main()
{
	DoubleList DList;
	DList.first = DList.last = NULL; // double list is empty when both pointers are NULL

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

		// insert empl data set into a double list handled by DList
		DList = insertNodeEnd(DList, empl);
	}

	printf("Double list just after creation:\n\n");
	parseDList(DList);

	DList = deleteNodeEnd(DList);
	printf("\n\nDouble list just after the deletion of the last node:\n\n");
	parseDList(DList);

	while (DList.last != NULL)
	{
		DList = deleteNodeEnd(DList);
	}
	printf("\n\nDouble list just after list deallocation:\n\n");
	parseDList(DList);

	// migrate fundamental operations over a circular list

	fclose(f);
}
