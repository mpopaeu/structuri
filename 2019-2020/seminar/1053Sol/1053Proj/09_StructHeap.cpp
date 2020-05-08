#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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

void filtrareBottomUp(NodHeap *sHeap, int nrNoduri) {
	int offset_curent = nrNoduri - 1;
	int offset_parinte = (offset_curent - 1) / 2;

	while ((offset_curent != offset_parinte) && (sHeap[offset_curent].cheie > sHeap[offset_parinte].cheie)) {
		// 1. interschimb curent cu parinte
		int auxt;
		char* numet;
		char grupat[5];

		auxt = sHeap[offset_parinte].stud.id;
		sHeap[offset_parinte].stud.id = sHeap[offset_curent].stud.id;
		sHeap[offset_curent].stud.id = auxt;

		numet = sHeap[offset_parinte].stud.nume;
		sHeap[offset_parinte].stud.nume = sHeap[offset_curent].stud.nume;
		sHeap[offset_curent].stud.nume = numet;

		strcpy(grupat,sHeap[offset_parinte].stud.nrGrupa);
		strcpy(sHeap[offset_parinte].stud.nrGrupa, sHeap[offset_curent].stud.nrGrupa);
		strcpy(sHeap[offset_curent].stud.nrGrupa, grupat);

		auxt = sHeap[offset_parinte].cheie;
		sHeap[offset_parinte].cheie = sHeap[offset_curent].cheie;
		sHeap[offset_curent].cheie = auxt;

		// 2. actualizare offset-i pentru cele doua noduri: nod curent si nod parinte
		offset_curent = offset_parinte;
		offset_parinte = (offset_curent - 1) / 2;
	}
}

// inserare nod in structura Heap
NodHeap* inserareNodHeap(NodHeap *sHeap, int &nrNoduri, int &capacitate, NodHeap newStud) {
	if (nrNoduri == capacitate) {
		// alocare noua structura de capacitate marita
		capacitate += DIM_VECTOR;
		NodHeap* sNewHeap = (NodHeap*)malloc(capacitate * sizeof(NodHeap));

		// copiere elemente din vechea structura in noua structura
		for (int i = 0; i < nrNoduri; i++) {
			sNewHeap[i].stud.id = sHeap[i].stud.id;
			sNewHeap[i].stud.nume = sHeap[i].stud.nume;
			strcpy(sNewHeap[i].stud.nrGrupa,sHeap[i].stud.nrGrupa);
			sNewHeap[i].cheie = sHeap[i].cheie;
		}

		// dezalocare structura veche
		free(sHeap);

		// actualizare parametru pt gestionarea noii structuri
		sHeap = sNewHeap;
	}

	// 1. inserare nodu nou (student) in structura Heap
	sHeap[nrNoduri].stud.id = newStud.stud.id;
	sHeap[nrNoduri].stud.nume = newStud.stud.nume;
	strcpy(sHeap[nrNoduri].stud.nrGrupa, newStud.stud.nrGrupa);
	sHeap[nrNoduri].cheie = newStud.cheie;

	nrNoduri += 1; // nr de noduri efectiv stocate in structura Heap este incrementat dupa inserarea lui newStud

	// 2. procedura de filtrare bottom-up
	filtrareBottomUp(sHeap, nrNoduri);

	return sHeap;
}

// TEMA: implementare filtrare top-down si stergere nod in Structura Heap
void filtrareTopDown(NodHeap *sHeap, int nrNoduri) {
	// 1. initializare offset-i: curent = 0 (tot timpul este nodul radacina), stanga, dreapta

	// 2. atat timp cat exista stanga sau dreapta SI nu se respecta relatia de ordine curent fata de max(stanga, dreapta)
	// se procedeaza la interschimb
	// stanga SAU dreapta exista daca offset_stanga / offset_dreapta < nrNoduri
	// dupa interschimb trebuie sa actualizez offset_curent cu offset_stanga / offset_dreapta
	// dupa actualizare offset_curent, se recalculeaza offset_stanga SI offset_dreapta
}

Student stergereNodHeap(NodHeap *sHeap, int &nrNoduri) {
	// 1. interschimb primul cu ultimul element din sHeap (0, nrNoduri - 1)

	// 2. "extragerea" studentului din ultimul element: salvare date student intr-o variabila locala

	// 3. actualizare numar de noduri din structura Heap (decrementare nrNoduri)

	// 4. aplicare procedura de filtrare top-down

	// 5. se face return pe student "extras" la punctul 2.

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
		sHeap = inserareNodHeap(sHeap, nrNoduri, capacitate, nodStudent);
		printf("\n Student %s inserat", nodStudent.stud.nume);

		nodStudent.stud.nume = NULL;
	}

	printf("\nStructura Heap dupa creare:\n");
	int nivel = 0;
	for (int i = 0; i < nrNoduri; i++) {
		if ((i + 1) == pow(2, nivel)) {
			printf("\n");
			nivel += 1;
		}
		printf("%d ", sHeap[i].cheie);
	}
	printf("\n\n");


	fclose(f);
}