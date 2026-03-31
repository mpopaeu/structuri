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

unsigned short int hash_function(unsigned short int key, unsigned short int size_ht)
{
	return (key % size_ht);
}

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

void insertEmployeeHashTable(Node** HT, unsigned short int size_ht, Employee data)
{
	// 1. compute the position where data must be inserted into
	unsigned short int pos = hash_function(data.id, size_ht);
	// 2. insert data into the simple list glued to the position computed at step 1)
	HT[pos] = insertNodeEnd(HT[pos], data);
}

Employee* searchEmployee(Node** HT, unsigned short int size_ht, unsigned short int search_key)
{
	unsigned short int pos = hash_function(search_key, size_ht);

	if (HT[pos])
	{
		// parsing the simple list where search_key should be stored
		Node* t = HT[pos];
		{
			while (t)
			{
				if (t->emp.id == search_key)
				{
					return &t->emp; // heap seg mem address will be returned to the caller to acces data later
				}
				t = t->next;
			}
		}
	}

	return NULL; // if there is not any employee having search_id
}

int main()
{
	Node* *HashTable = NULL; // array of Node* 
	unsigned short int size_hashTable = 50; // max 50 simple lists linked to HashTable


	// allocare the hash table
	HashTable = malloc(size_hashTable * sizeof(Node*));
	// initialize the hash table
	// all simple lists are marked as empty lists
	for (unsigned short int i = 0; i < size_hashTable; i++)
		HashTable[i] = NULL;

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

		// insert empl data set into a hash table with chaining
		insertEmployeeHashTable(HashTable, size_hashTable, empl);
	}

	fclose(f);

	// parsing the hash table to check the content
	printf("Content of entire Hash Table:\n");
	for (unsigned short int i = 0; i < size_hashTable; i++)
	{
		if (HashTable[i] != NULL)
		{
			// list i contains one node at least
			printf("Employees stored by the list %d\n", i + 1);
			Node* t = HashTable[i]; // first node in the list HashTable[i]
			while (t)
			{
				printf("%d %s\n", t->emp.id, t->emp.name);
				t = t->next;

			}
		}
	}

	// search a particular employee based on the hash table key
	Employee* pEmp = searchEmployee(HashTable, size_hashTable, 2012);

	printf("\n\n Employee search in the Hash Table:\n");
	if (pEmp != NULL)
		printf("%d %s\n", pEmp->id, pEmp->name);
	else
		printf("\nEmployee does not exist in the Hash Table.\n\n");

	// deletion of an employee based on id (the key of Hash Table)

	return 0;
}