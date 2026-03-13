#include <stdio.h>
#include <string.h>

struct Employee
{
	char* name;		// 4 bytes
	float salary;	// 4 bytes
	char CNP[14];	// 14 bytes
	char emp_date[11];	// 11 bytes
	unsigned short int no_directs; // 2 bytes
	// TOTAL 35 bytes, but sizeof(Employee) is 36 bytes (internal structure alignments)
};

typedef struct Employee Employee;

int main()
{
	printf("Size of Employee is %d bytes\n", sizeof(Employee));

	Employee emp;

	emp.name = "Popescu William";
	emp.salary = (float)8946.29;
	strcpy(emp.CNP, "1980406420142");
	strcpy(emp.emp_date, "11/11/2023");
	emp.no_directs = 13;

	Employee* pemp = &emp;

	printf("Employee's name = %s\n", pemp->name);
	// *pemp.name = 'W'; // wrong statement to get the first byte of the string
	*((*pemp).name) = 'W'; // runtime error because name is a constant string
	printf("Employee's name = %s\n", pemp->name);

	*(pemp->name) = 'Y'; // runtime error because name is a constant string
	printf("Employee's name = %s\n", pemp->name);

	return 0;
}