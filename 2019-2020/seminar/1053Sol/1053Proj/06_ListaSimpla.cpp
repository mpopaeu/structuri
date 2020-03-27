#include <stdio.h>
#include <malloc.h>
#include <string.h>

//#define NUME_STUDENT_DEFAULT "Anonim"
//#define ID_STUDENT_DEFAULT 0
//#define GRUPA_STUDENT_DEFAULT "----"

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct Nod {
	Student stud; // date de procesat
	Nod* next;	  // date/info de legatura/implementare relatie de ordine intre noduri
};

Nod* insertNodeEnd(Nod* lst, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));

	nou->stud = s; // asumata partajarea lui nume
	nou->next = NULL;
	if (lst == NULL) // lista este goala/empty
		return nou; 
	else {
		// exista cel putin 1 nod in lista
		Nod* temp = lst;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = nou; // legare nodul nou la sfarsitul listei lst
	}

	return lst;
}

// parsare lista simpla

// stergere/deszalocare nod din lista simpla (la inceputul listei)

// dezalocare lista simpla

// interschimb de noduri adiacente prin modificarea adreselor de legatura (prin modificare campuri next)

void main() {
	Nod * prim = NULL; 
	Student s;

	while (fgets(...)) {

		// incarcare date student in variabila s

		// inserare student in lista simpla (prim)
		prim = insertNodeEnd(prim, s);
	}
}