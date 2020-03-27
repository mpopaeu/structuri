#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MY_STRING "Anonymous"
#define ID_STUDENT 0
#define NR_GRUPA "0000"

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct Nod {
	Student stud; // date propriu-zise
	Nod* next; // date de legatura (relatie de ordine pe elemente de tip Nod)
};


Nod* inserareSfarsitLista(Nod* p, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod)); // alocare nod nou
	nou->stud = s; // asumare s.nume va fi copiat peste nou->nume
	nou->next = NULL; 

	if (p == NULL) // lista nu contine nici un nod/element
		return nou; 
	else {
		// parsare lista pana pe ultimul element
		Nod* temp = p;
		while (temp->next != NULL)
			temp = temp->next;
		// legare ultimul nod din lista la nodul nou
		temp->next = nou;
	}

	return p;
}

// stergere nod din lista

// deteminare numar noduri in lista

// dezalocare lista

// interschimb noduri adiacente lista simpla (cu modificarea adrese de legatura -> next)


void main() {
	Nod* prim = NULL;
	Student s;

	while (fgets(.....)) {
		// alocare (nume) si initializare student

		// apel functie inserare nod in lista simpla
		prim = inserareSfarsitLista(prim, s);
	}

	// parsare lista simpla pentru validare inserari
	Nod* temp = prim;
	while (temp != NULL) {
		printf(" Student id: %d\n", temp->stud.id);
	}

}