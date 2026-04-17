#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 59

struct Employee
{
	char* name;			// 4 bytes
	float salary;		// 4 bytes
	char CNP[14];		// 14 bytes
	char emp_date[11];	// 11 bytes
	unsigned short int no_directs; // 2 bytes
};

typedef struct Employee Employee;

struct Node
{
	Employee emp;
	struct Node* next;
};

typedef struct Node Node;

// insert a new Employee data set at the begining of the simpla list 
Node* insertNode(Node* list, Employee data)
{
	Node* new_node = malloc(sizeof(Node)); // allocation of the new node in heap seg

	new_node->emp = data; // put data byte-by-byte into emp
	new_node->next = list; // link the new node to the current head of the list; hence, new node must be the new start of the list

	return new_node; // update in the caller the head of the list to be new node
}

unsigned char hashFunction(char* key)
{
	unsigned int sum = 0;
	for (unsigned char i = 0; i < strlen(key); i++)
		sum += key[i];

	return (sum % HASH_TABLE_SIZE);
}

void insertEmployeeHashTable(Node** HT, Employee data)
{
	// 1. compute the position within HT where data must be inserted
	// computation done by hash function
	unsigned char ht_position = hashFunction(data.CNP); // CNP is the searching key used for this hash table (HT)

	// 2. insert in the list linked to HT on position calculated at previous step
	HT[ht_position] = insertNode(HT[ht_position], data); // HT[ht_position] is a single simple list
}

void parsingList(Node* list)
{
	Node* t = list;
	while (t != NULL)
	{
		printf("%s %s\n", t->emp.CNP, t->emp.name);

		t = t->next;
	}
}

Employee* searchEmployee(Node** HT, char* key)
{
	// 1. calculate the hash function
	unsigned char ht_position = hashFunction(key);

	// 2. check node by the node the simple list linked to offset calculated before
	Node* temp = HT[ht_position];
	while (temp != NULL)
	{
		if (strcmp(key, temp->emp.CNP) == 0)
			return &temp->emp; // returns the heap mem address within the node where the employee having key is stored into
		temp = temp->next;
	}

	return NULL; // there is no employee with key stored by the hash table
}

int main()
{
	FILE* f;

	f = fopen("Employees.txt", "r");

	Node** HashTable = NULL; // array to support implementation of hash table with chaining

	HashTable = malloc(HASH_TABLE_SIZE * sizeof(Node*)); // allocation of the hash table as array of simple lists
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HashTable[i] = NULL; // each list i in the hash table is marked as empty list

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
		temp.no_directs = atoi(token); // coversion text-to-binary (integer)

		// data has been prepated within temporary local variable temp; ready to send data to hash table
		insertEmployeeHashTable(HashTable, temp);
	}

	fclose(f);

	// validate the content of tha hash table
	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (HashTable[i] != NULL)
		{
			printf("\nContent of the list %d in hash table: \n", i + 1);
			parsingList(HashTable[i]);
		}
	}


	Employee* pEmployee = searchEmployee(HashTable, "2890214083358");
	if (pEmployee != NULL)
	{
		printf("Employees stored within the hash table: %s %s\n", pEmployee->CNP, pEmployee->name);
	}
	else
	{
		printf("\n\nThere is no employee with provided CNP.\n");
	}

	// delete one employee in the hash table based on the key (CNP)
	// implementation very similar to insert employee into hash table, by replacing the insert node with delete node


	// deallocate the entire hash table data structure (by reusing the delete nod/employee developed above)
	// do not forget to deallocate the entire array of Node*


	return 0;
}
