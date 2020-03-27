#include <stdio.h>
#include <malloc.h>
#include <string.h>

//#define VECTOR_SIZE 10
//
//#define ID_STUDENT 0
//#define NUME_STUDENT "student"
//#define NUMAR_GRUPA "----"
//#define NR_LINII 3
//#define NR_COLOANE 4

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct Nod {
	Student stud;
	Nod* next;
};

Nod* inserareNodSfarsit(Nod* lista, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));

	nou->stud = s; // copiere byte cu byte a lui s peste nou->st; partajare temporara nume student ca si locatie de heap
	nou->next = NULL; // nou devine ultimul nod in lista simpla

	if (lista == NULL) // nu exista nici un nod in lista
		return nou;
	else {
		// lista are cel putin 1 nod
		Nod* temp = lista;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = nou; // actualizare legatura sfarsit de lista catre nodul care se insereaza
	}

	return lista;
}

// stergere nod pe baza de id student

// dezalocare lista simpla

// interschimb noduri adiacente cu modificarea adreselor de legatura

void main() {
	Nod* prim = NULL;
	Student s;
	FILE* f;
	f = fopen("Studenti.txt", "r");

	while (fgets(...)) {
		// preluare continut fisier studenti; se initializeaza temporarul s
		...
			// apel functie de inserare nod in lista simpla
			prim = inserareNodSfarsit(prim, s);
	}


	fclose(f);
}