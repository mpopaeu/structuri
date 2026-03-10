#include <stdio.h>
#include <string.h>

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

int main()
{
	Employee emp_1;

	printf("Size of structure Employee is: %d bytes\n", sizeof(Employee));

	emp_1.id = 1001;
	emp_1.name = "Jack Smith";
	emp_1.age = 29;
	emp_1.salary = (float)7450.99;
	strcpy(emp_1.hire_date, "11/07.2023");

	Employee* pEmp = &emp_1;
	// pEmp->age = 12; // (*pEmp).id = 12;

	printf(" Name  = %s, Age = %d\n", pEmp->name, pEmp->age);

	return 0;
}