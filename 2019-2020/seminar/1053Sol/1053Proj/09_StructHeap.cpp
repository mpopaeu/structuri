#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128
#define DIM_VECTOR 100

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodHeap {
	Student stud;
	int cheie;
};

// inserare nod in structura Heap
NodHeap* inserareNodHeap(NodHeap *sHeap, int &nrNoduri, int &capacitate) {

}

void main() {

	NodHeap *sHeap;
	NodHeap nodStudent;

	// alocare spatiu vector suport pentru structura
	sHeap = (NodHeap*)malloc(DIM_VECTOR * sizeof(NodHeap)); // DIM_VECTOR - capacitate de stocare curenta

	int nrNoduri = 0; // numar de noduri in structura Heap la un moment dat la run-time
	int capacitate = DIM_VECTOR; // capacitatea maxima de stocare a structurii Heap

	FILE * f;
	f = fopen("StudHeap.txt", "r");
	char studBuff[20];

	char * token, file_buf[LINESIZE], sep_list[] = ",";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		nodStudent.stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		nodStudent.stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(nodStudent.stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(nodStudent.stud.nrGrupa, token);

		token = strtok(NULL, sep_list);
		nodStudent.cheie = atoi(token);

		// inserare nod (Student + cheie) in structura Heap 
		sHeap = inserareNodHeap(sHeap, nrNoduri, capacitate);
		printf(" Student %s inserat", stud.nume);

		stud.nume = NULL;
	}

	fclose(f);
}