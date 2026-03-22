#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct Employee
{
	char* name;		// 4 bytes
	float salary;	// 4 bytes
	char CNP[14];	// 14 bytes
	char emp_date[11];	// 11 bytes
	unsigned short int no_directs; // 2 bytes
};

typedef struct Employee Employee;

struct NodeD
{
	Employee emp;
	struct NodeD * next, *prev;
};

typedef struct NodeD NodeD;

struct DList {
	NodeD* head, * tail;
};
typedef struct DList DList;


DList insertNodeD(DList list, Employee data)
{
	NodeD* new_node = malloc(sizeof(NodeD));
	new_node->emp = data;
	new_node->next = list.head;
	new_node->prev = NULL;

	if (list.head == NULL)
	{
		list.head = list.tail = new_node;
	}
	else
	{
		list.head->prev = new_node;
		list.head = new_node;
	}

	return list;
}

void parsingDList(DList list)
{
	NodeD* t = list.head;
	printf("Double list head->tail:\n");
	while (t != NULL)
	{
		printf("%s %s\n", t->emp.CNP, t->emp.name);

		t = t->next;
	}

	t = list.tail;
	printf("Double list tail->head:\n");
	while (t != NULL)
	{
		printf("%s %s\n", t->emp.CNP, t->emp.name);

		t = t->prev;
	}
}

int main()
{
	FILE* f;

	f = fopen("Employees.txt", "r");

	DList double_list; //local variable containing the both pointers to get access to the double list
	double_list.head = double_list.tail = NULL; // mark my double list as an empty one

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

		// data has been prepated within temporary local variable temp; ready to send data to simple list
		double_list = insertNodeD(double_list, temp);
	}

	fclose(f);

	printf("Double list after creation (both directions):\n");
	parsingDList(double_list);

	// delete a node on a certain position in double list
	// deallocate the entire double list

	return 0;
}