#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define NUME_STUDENT_DEFAULT "Anonim"
#define ID_STUDENT_DEFAULT 0
#define GRUPA_STUDENT_DEFAULT "----"
#define DIMENSIUNE_VECTOR 10
#define NR_LINII 4
#define NR_COLOANE 3

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};


void main() {
	Student s;
	Student vS[DIMENSIUNE_VECTOR];
	Student *pS;
	Student **mS; // 2 abordari: matrice (heap) de studenti SAU vector (heap) de pointeri la studenti - variabila vmS
	Student **vmS; // vector (heap) de pointeri la studenti 

	printf("Dimensiune structura Student: %d\n", sizeof(Student));

	s.id = ID_STUDENT_DEFAULT;
	s.nume = (char*)malloc(sizeof(char) * (strlen(NUME_STUDENT_DEFAULT) + 1)); // alocare spatiu
	strcpy(s.nume, NUME_STUDENT_DEFAULT);
	strcpy(s.nrGrupa, GRUPA_STUDENT_DEFAULT);

	for (int i = 0; i < DIMENSIUNE_VECTOR; i++) {
		// vS[i] = s; // s este copiat byte cu byte peste vS[i] => s.nume si vS[i].nume au aceeasi valoare => exista partajari de zone de heap
		vS[i].id = s.id;

		vS[i].nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1)); // zone separate de heap pt nume student; evitare partajari zone heap intre mai multe variabile
		strcpy(vS[i].nume, s.nume);

		strcpy(vS[i].nrGrupa, s.nrGrupa);
	}

	pS = (Student*)malloc(sizeof(Student) * DIMENSIUNE_VECTOR);
	for (int i = 0; i < DIMENSIUNE_VECTOR; i++) {
		// pS[i] = s; // s este copiat byte cu byte peste pS[i] => s.nume si pS[i].nume au aceeasi valoare => exista partajari de zone de heap
		pS[i].id = s.id;

		pS[i].nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1)); // zone separate de heap pt nume student; evitare partajari zone heap intre mai multe variabile
		strcpy(pS[i].nume, s.nume);

		strcpy(pS[i].nrGrupa, s.nrGrupa);
	}

	// matrice (heap) de studenti
	mS = (Student**)malloc(sizeof(Student*) * NR_LINII); // vector de pointeri la linii (structura intermediara)
	for (int i = 0; i < NR_LINII; i++)
		mS[i] = (Student*)malloc(sizeof(Student) * NR_COLOANE); // alocare linie i de studenti

	for (int i = 0; i < NR_LINII; i++)
		for (int j = 0; j < NR_COLOANE; j++) {
			// mS[i][j] = s; // s este copiat byte cu byte peste mS[i][j] => s.nume si mS[i][j].nume au aceeasi valoare => exista partajari de zone de heap
			mS[i][j].id = s.id;

			mS[i][j].nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1)); // zone separate de heap pt nume student; evitare partajari zone heap intre mai multe variabile
			strcpy(mS[i][j].nume, s.nume);

			strcpy(mS[i][j].nrGrupa, s.nrGrupa);
		}

	vmS = (Student**)malloc(sizeof(Student*) * DIMENSIUNE_VECTOR); // DIMENSIUNE_VECTOR elemente de tipul Student*
	for (int i = 0; i < DIMENSIUNE_VECTOR; i++)
		vmS[i] = (Student*)malloc(sizeof(Student) * 1); // 1 singur student de fiecare data

	for (int i = 0; i < DIMENSIUNE_VECTOR; i++) {
		// *(vmS[i]) = s; // s este copiat byte cu byte peste *(vmS[i]) => s.nume si *(vmS[i]).nume au aceeasi valoare => exista partajari de zone de heap
		
		vmS[i]->id = s.id;

		vmS[i]->nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1)); // zone separate de heap pt nume student; evitare partajari zone heap intre mai multe variabile
		strcpy(vmS[i]->nume, s.nume);

		strcpy(vmS[i]->nrGrupa, s.nrGrupa);
	}

	// dezalocari structuri
	free(s.nume);

	for (int i = 0; i < DIMENSIUNE_VECTOR; i++)
		free(vS[i].nume);

	// dezalocare vector (heap)
	for (int i = 0; i < DIMENSIUNE_VECTOR; i++)
		free(pS[i].nume);
	free(pS); // dezalocare vector pS din heap

	// dezalocare matrice(heap)
	for (int i = 0; i < NR_LINII; i++)
		for (int j = 0; j < NR_COLOANE; j++)
			free(mS[i][j].nume);
	for (int i = 0; i < NR_LINII; i++)
		free(mS[i]);
	free(mS);

	// dezalocare vector de pointeri la studenti
	for (int i = 0; i < DIMENSIUNE_VECTOR; i++)
		free(vmS[i]->nume);
	free(vmS);

}