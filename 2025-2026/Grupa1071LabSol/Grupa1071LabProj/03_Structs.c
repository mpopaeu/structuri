#include <stdio.h>

struct Employee
{
	unsigned short int id;
	char* name;
	float salary;
	unsigned char age;
	char hire_date[11];
};

typedef struct Employee Employee;

int main()
{
	Employee emp_1;

	printf("Size of structure Employee is: %d bytes\n", sizeof(Employee));

	return 0;
}