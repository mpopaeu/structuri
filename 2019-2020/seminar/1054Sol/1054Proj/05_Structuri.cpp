#include <stdio.h>

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

void main() {
	Student s; // variabila tip Student; alocata la compilare in frame-ul de seg stack aferent lui main
	Student vStud[10]; // variabila masiv de tip Student; 10 locatii alocate la compilare, fiecare locatie este Student

	printf("Dimensiune structura student in nr de bytes: %d\n", sizeof(Student));
}