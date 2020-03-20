#include <stdio.h>
#include <malloc.h>

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};


void main() {
	Student s;
	Student vS[10];
	Student *pS;
	Student **mS;

	printf("Dimensiune structura Student: %d\n", sizeof(Student));
}