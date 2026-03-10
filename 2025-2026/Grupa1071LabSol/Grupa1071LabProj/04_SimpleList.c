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
	// TOTAL of 22 bytes as sum of fields, but 24 bytes as memory allocated area
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
	Node* first = NULL;

	FILE* f = fopen("Employees.txt", "r");

	char buffer[256];
	char seps[] = ",";

	while (fgets(buffer, sizeof(buffer), f))
	{
		Employee empl;
		char* token = strtok(buffer, seps);
		empl.id = atoi(token); // conversion text-to-integer

		token = strtok(NULL, seps);
		empl.name = malloc(strlen(token) + 1); // +1 because the null byte terminator
		strcpy(empl.name, token); // there is no conversion

		token = strtok(NULL, seps);
		empl.salary = atof(token); // conversion text-to-float

		token = strtok(NULL, seps);
		empl.age = atoi(token); // conversion text-to-integer

		token = strtok(NULL, seps);
		strcpy(empl.hire_date, token);

	}

	fclose(f);

	return 0;
}