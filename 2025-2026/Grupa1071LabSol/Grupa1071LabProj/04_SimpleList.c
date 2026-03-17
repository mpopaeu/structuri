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

struct Node
{
	Employee emp;
	struct Node* next;
};

typedef struct Node Node;

Node* insertNodeEnd(Node* list, Employee data)
{
	Node* new_node = malloc(sizeof(Node));
	new_node->emp = data;
	new_node->next = NULL;

	if (list == NULL)
	{
		// list is empty; new node will be the first and unique node in my list
		return new_node;
	}
	else
	{
		// list contains one node at least
		Node* t = list;
		while (t->next != NULL)
			t = t->next;

		t->next = new_node;

		return list;
	}
}

void parseList(Node* list)
{
	Node* t = list;
	while (t != NULL)
	{
		printf("%s %d\n", t->emp.name, t->emp.id);
		t = t->next;
	}
}

Node* deleteNodeEnd(Node* list)
{
	if (list != NULL)
	{
		Node* t = list;
		if (t->next == NULL)
		{
			// there is one single node in the simple list
			free(t->emp.name); // deallocate the employee's name first
			free(t);   // deallpocate the node
			list = NULL; // update the begining of the list as being a NULL pointer (list becomes and empty one)
		}
		else
		{
			// there are 2 nodes at least in the list
			while ((t->next)->next != NULL) // t->next is the node after t; we have to check the field next within t->next
				t = t->next; 
			Node* q = t->next; // q is the last node in the simple list
			free(q->emp.name);
			free(q); // deallocate the last node in the chain

			t->next = NULL; // t becomes the last node in the simple list
		}
	}

	return list;
}

int main()
{
	Node* first = NULL;

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

		// insert empl data set into a simple list handled by first
		first = insertNodeEnd(first, empl);
	}

	fclose(f);

	printf("Simple list just after creation: \n");
	parseList(first);

	first = deleteNodeEnd(first);
	printf("\nSimple list just after deletion of one node:\n");
	parseList(first);

	//first = NULL; // not enough; memory leaks are there

	// deallocation of the simple list by trying to remove one more node at the end till the list becomes empty
	while (first != NULL)
	{
		first = deleteNodeEnd(first);
	}
	printf("\nSimple list just after deallocation:\n");
	parseList(first);

	// migrate the above implementations to double list data structure

	return 0;
}