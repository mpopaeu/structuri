#include <stdio.h>

struct Employee
{
	char* name;
	float salary;
	char CNP[14];
	char emp_date[11];
	unsigned short int no_directs;
};

typedef struct Employee Employee;

int main()
{
	printf("Size of Employee is %d bytes\n", sizeof(Employee));


	return 0;
}