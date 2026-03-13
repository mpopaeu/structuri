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

struct Node
{
	Employee emp;
	struct Node* next;
};

typedef struct Node Node;

int main()
{
	FILE* f;

	f = fopen("Employees.txt", "r");

	char buffer[256];
	char sep_list[] = ",";
	while (fgets(buffer, sizeof(buffer), f))
	{
		Employee temp;
		char* token = strtok(buffer, sep_list);
		temp.name = malloc(strlen(token) + 1); 
		strcpy(temp.name, token);

		token = strtok(NULL, sep_list);
		temp.salary = (float)atof(token);

		token = strtok(NULL, sep_list);
		strcpy(temp.CNP, token);

		token = strtok(NULL, sep_list);
		strcpy(temp.emp_date, token);

		token = strtok(NULL, sep_list);
		temp.no_directs = atoi(token);
	}

	fclose(f);

	return 0;
}