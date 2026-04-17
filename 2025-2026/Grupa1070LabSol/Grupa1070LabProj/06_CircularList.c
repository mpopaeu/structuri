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

struct Node
{
	Employee emp;
	struct Node* next;
};

typedef struct Node Node;

Node* insertNodeCircular(Node* list, Employee data)
{
	Node* new_node = malloc(sizeof(Node)); // allocation of the new node in heap seg

	new_node->emp = data; // put data buye-by-byte into emp
	if (list == NULL)
	{
		// the circular list is empty
		new_node->next = new_node; // the first node must point to itself
	}
	else
	{
		new_node->next = list; // the next node must be the current head
		Node* t = list;
		while (t->next != list) // t must be the last node in the circular list
			t = t->next;

		t->next = new_node;
	}

	return new_node; // update in the caller the head of the list to be new node
}


Node* deleteNodeCircularPosition(Node* list, unsigned short int pos)
{
	if (list != NULL)
	{
		// there is a node at least in circular list
		if (pos == 1)
		{
			// delete the head of the list
			Node* t = list; // the node to be deleted

			Node* p = list->next;
			while (p->next != list)
				p = p->next;

			if (list != list->next)
			{
				// list contains 2 nodes at least
				list = list->next;
				p->next = list;
			}
			else
			{
				// lista contains one single node and becomes empty after deletion
				list = NULL; 
			}

			// delete node t
			free(t->emp.name);
			free(t);
		}
		else
		{
			// pos inside the circular list
			Node* t = list; // t node before the one to be deleted
			unsigned char counter = 1;
			while (t->next != list && counter < pos - 1)
			{
				t = t->next;
				counter += 1;
			}

			if (t->next != list)
			{
				// there is position pos in the list
				Node* p = t->next; // the node to be deleted
				Node* r = p->next; // the node after the one to be deleted

				t->next = r;

				free(p->emp.name);
				free(p);
			}
		}
	}

	return list;
}

// swap nodes (i, i+1) in a circular list

int main()
{
	FILE* f;

	f = fopen("Employees.txt", "r");

	Node* head = NULL;

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
		head = insertNodeCircular(head, temp);
	}

	fclose(f);

	Node* t;
	printf("Circular list content after creation:\n");
	if (head != NULL)
	{
		printf("%s %s\n", head->emp.CNP, head->emp.name);
		t = head->next;
		while (t != head)
		{
			printf("%s %s\n", t->emp.CNP, t->emp.name);
			t = t->next;
		}
	}

	head = deleteNodeCircularPosition(head, 6);
	if (head != NULL)
	{
		printf("Circular list content after deletion of one node based on its position within the list:\n");
		printf("%s %s\n", head->emp.CNP, head->emp.name);
		t = head->next;
		while (t != head)
		{
			printf("%s %s\n", t->emp.CNP, t->emp.name);
			t = t->next;
		}
	}

	// deallocate the entire circular list
	while (head != NULL)
	{
		head = deleteNodeCircularPosition(head, 1);
	}

	printf("Circular list content after data structure deallocation:\n");
	if (head != NULL)
	{
		printf("%s %s\n", head->emp.CNP, head->emp.name);
		t = head->next;
		while (t != head)
		{
			printf("%s %s\n", t->emp.CNP, t->emp.name);
			t = t->next;
		}
	}

	return 0;
}