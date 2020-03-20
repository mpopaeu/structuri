#include <stdio.h>


struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};


void main() {
	Student s; // 

	printf("Lungime zona memorie Student: %d bytes\n", sizeof(Student));
}