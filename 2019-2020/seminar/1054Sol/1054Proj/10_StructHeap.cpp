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
	int hKey;
};

NodHeap* inserareNodHeap(NodHeap* strHeap, NodHeap nodInserat, int nrNoduri) {

}

void main() {

	NodHeap * vHeap;
	NodHeap nodStud;

	// alocare spatiu tabela de dispersie
	vHeap = (NodHeap*)malloc(sizeof(NodHeap) * DIM_VECTOR);
	// numarul de noduri existent in structura arbore Heap
	int nrNoduri = 0;


	FILE * f;
	f = fopen("StudHeap.txt", "r");
	char studBuff[20];

	char * token, file_buf[LINESIZE], sep_list[] = ",";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		nodStud.stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		nodStud.stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(nodStud.stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(nodStud.stud.nrGrupa, token);

		token = strtok(NULL, sep_list);
		nodStud.hKey = atoi(token);

		// inserare Student in structura Heap
		inserareNodHeap(vHeap, nodStud, nrNoduri);

		nodStud.stud.nume = NULL; // evitare partajare zona heap pentru nume student
	}

	fclose(f);
}