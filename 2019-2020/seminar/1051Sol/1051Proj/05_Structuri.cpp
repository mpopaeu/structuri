#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define VECTOR_SIZE 10

#define ID_STUDENT 0
#define NUME_STUDENT "student"
#define NUMAR_GRUPA "----"
#define NR_LINII 3
#define NR_COLOANE 4

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};


void main() {
	Student s; // variabila (unica) de tip Student
	Student vS[VECTOR_SIZE];
	Student *pS; // pointer catre 1 sau m Studenti
	Student **mS; // matrice de studenti
	Student ** pvS; // vector de pointeri la studenti (fiecare pointer din vector trimite la un singur student)

	printf("Lungime zona memorie Student: %d bytes\n", sizeof(Student));

	s.id = ID_STUDENT;
	s.nume = (char*)malloc(sizeof(char) * (strlen(NUME_STUDENT) + 1));
	strcpy(s.nume, NUME_STUDENT);
	strcpy(s.nrGrupa, NUMAR_GRUPA);

	for (int i = 0; i < VECTOR_SIZE; i++) {
		// vS[i] = s; // copiere byte cu byte s peste vS[i]; problema: partajarea aceleasi zone de heap pentru nume student

		vS[i].id = s.id;
		vS[i].nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
		strcpy(vS[i].nume, s.nume);
		strcpy(vS[i].nrGrupa, s.nrGrupa);
	}

	// vector de studenti alocat in heap
	pS = (Student*)malloc(VECTOR_SIZE * sizeof(Student));
	for (int i = 0; i < VECTOR_SIZE; i++) {
		// pS[i] = s; // copiere byte cu byte s peste pS[i]; problema: partajarea aceleasi zone de heap pentru nume student

		pS[i].id = s.id;
		pS[i].nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
		strcpy(pS[i].nume, s.nume);
		strcpy(pS[i].nrGrupa, s.nrGrupa);
	}

	// matrice de studenti alocata in heap
	mS = (Student**)malloc(sizeof(Student*) * NR_LINII); // alocare structura intermediara: vector de pointeri la linii
	for (int i = 0; i < NR_LINII; i++)
		mS[i] = (Student*)malloc(sizeof(Student) * NR_COLOANE); // alocare linie i in matrice
	// initializare studenti in matrice
	for(int i=0; i<NR_LINII; i++)
		for (int j = 0; j < NR_COLOANE; j++) {
			// mS[i][j] = s; // copiere byte cu byte s peste mS[i][j]; problema: partajarea aceleasi zone de heap pentru nume student
			
			mS[i][j].id = s.id;
			mS[i][j].nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
			strcpy(mS[i][j].nume, s.nume);
			strcpy(mS[i][j].nrGrupa, s.nrGrupa);
		}

	// vector de pointeri la studenti (1 singur student la fiecare pointer)
	pvS = (Student**)malloc(sizeof(Student*) * VECTOR_SIZE); // alocare vector de pointeri la studenti
	for (int i = 0; i < VECTOR_SIZE; i++) {
		pvS[i] = (Student*)malloc(1 * sizeof(Student)); // alocare unui singur student
	}

	for (int i = 0; i < VECTOR_SIZE; i++) {
		// *(pvS[i]) = s; // copiere byte cu byte s peste *(pvS[i]); problema: partajarea aceleasi zone de heap pentru nume student

		pvS[i]->id = s.id; 
		// (*(pvS[i])).id = s.id;
		pvS[i]->nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
		strcpy(pvS[i]->nume, s.nume);
		strcpy(pvS[i]->nrGrupa, s.nrGrupa);
	}

	// dezalocare structuri
	free(s.nume);

	for (int i = 0; i < VECTOR_SIZE; i++)
		free(vS[i].nume);

	// dezalocare vector studenti alocat in heap
	for (int i = 0; i < VECTOR_SIZE; i++)
		free(pS[i].nume);
	free(pS);

	// dezalocare matrice de studenti
	for (int i = 0; i < NR_LINII; i++)
		for (int j = 0; j < NR_COLOANE; j++)
			free(mS[i][j].nume); // dezalocare nume pentru fiecare student din matrice
	for (int i = 0; i < NR_LINII; i++)
		free(mS[i]); // dezalocare linie i
	free(mS); // dezalocare structura intermediara (vector de pointeri la linii)

	// dezalocare vector de pointeri la studenti
	for (int i = 0; i < VECTOR_SIZE; i++)
		free(pvS[i]->nume); // dezalocare nume student i din vectorul de pointeri
	free(pvS);
}