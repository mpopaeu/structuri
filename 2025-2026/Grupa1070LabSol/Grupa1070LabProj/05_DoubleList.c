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

Employee deleteDNode(DList *list, unsigned char pos)
{
	Employee emp_result;
	emp_result.name = NULL;

	if (list->head != NULL)
	{
		unsigned char counter = 1;
		NodeD* t = list->head;
		while ((t != NULL) && (counter < pos))
		{
			t = t->next;
			counter += 1;
		}

		if (t != NULL)
		{
			NodeD* p,* q;
			p = t->prev; // the node before the one to be deleted
			q = t->next; // the node after the one to be deleted

			if (p != NULL && q != NULL)
			{
				// p and q are not endpoints of the double list
				p->next = q;
				q->prev = p;
			}
			else
			{
				if (p == NULL && q == NULL)
				{
					// there is one single node in the double list to be deleted
					list->head = list->tail = NULL; // double list becomes empty
				}
				else
				{
					if (p == NULL)
					{
						// pos is 1; t is the head of the double list to be deleted
						q->prev = p;
						list->head = q; // the new head of the double list
					}
					else
					{
						// t is the last node in the double list
						p->next = q;
						list->tail = p; // the new tail of the double list
					}
				}
			}

			emp_result = t->emp; // save data to be returned to the caller
			free(t); // deallocate the node t
		}

	}

	return emp_result;

}

// function to remove all employess having the salary over a specified threshold
// removed employees will be inserted into a different/separate double list
DList deleteSalaryNodes(DList* list, float threshold)
{
	DList secondList;
	secondList.head = NULL;
	secondList.tail = NULL;

	if (list->head)
	{
		int counter = 1;
		NodeD* temp = list->head;
		while (temp)
		{
			if (temp->emp.salary > threshold)
			{
				temp = temp->next;
				Employee empToD = deleteDNode(list, counter);
				secondList = insertNodeD(secondList, empToD);
			
			}
			else
			{
				temp = temp->next;
				counter += 1;
			}
			
		}
	}


	return secondList;
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

	DList secondSalaryList;
	secondSalaryList = deleteSalaryNodes(&double_list, 10000);
	printf("\nSecond double list is:\n");
	parsingDList(secondSalaryList);


	// delete a node on a certain position in double list
	Employee result = deleteDNode(&double_list, 2);
	if (result.name != NULL)
		printf("\nDeleted employee: %s %s\n", result.CNP, result.name);
	else
		printf("\nNo employee deletion\n");
	free(result.name); // deallocate the employee's name 
	printf("\n\nDouble list after node deletion (both directions):\n");
	parsingDList(double_list);
	

	// deallocate the entire double list
	while (double_list.head)
	{
		result = deleteDNode(&double_list, 1);
		free(result.name); // deallocate the employee's name
	}
	printf("\n\nDouble list after list deallocation (both directions):\n");
	parsingDList(double_list);

	return 0;
}