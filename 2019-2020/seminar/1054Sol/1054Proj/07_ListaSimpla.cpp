#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128


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
	// nou->stud = s; // copiere inclusiv nrGrupa !!!
	nou->stud.id = s.id;
	nou->stud.nume = s.nume; // asumare s.nume va fi copiat peste nou->nume
	strcpy(nou->stud.nrGrupa, s.nrGrupa);
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
Nod* stergereNodInceput(Nod* lst) {
	Nod * temp = lst;

	if (lst) {
		lst = lst->next; // actualizare nod de inceput lista

		free(temp->stud.nume); // dezalocare mem heap pt nume student
		free(temp);			// dezalocare mem heap pt nod din lista
	}

	return lst;
}

// deteminare numar noduri in lista
int nrNoduri(Nod* lst) {
	int n = 0;

	Nod * temp = lst;
	while (temp) {
		n += 1; // exista nod curent, nr curent de noduri este incrementat

		temp = temp->next; // temp este mutat pe nod succesor
	}

	return n;
}

// interschimb noduri adiacente lista simpla (cu modificarea adrese de legatura -> next)
Nod* interschimbAdiacente(Nod* lst, int idStud) {
	Nod *p, *q, *r, *s;

	// cazuri particulare
	//		1. lista contine cel mult 1 nod - se abandoneaza operatia
	if (lst == NULL || lst->next == NULL)
		return lst;
	
	//		2. primul nod din interschimb este lst (se interschimba nodul 1 cu 2) - are loc interschimb, se returneaza noul inceput de lista
	if (lst->stud.id == idStud) {
		// initializam cele 3 noduri implicate in interschimb
		q = lst;
		r = lst->next;
		s = r->next;
	}

	//		3. primul nod din interschimb este ultimul din lista (nu exista nodul 2) - se abandoneaza operatia

	// caz general

	return lst;
}

// interschimb noduri oarecare in lista simpla (cu modificare de adrese de legatura)

// sortarea unei liste simple (cu apel functie/functii de interschimb noduri dezvoltate/implementate mai sus)

void main() {
	Nod* prim = NULL;
	Student s;

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		// alocare (nume) si initializare student
		token = strtok(file_buf, sep_list);
		s.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		s.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(s.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(s.nrGrupa, token);

		token = strtok(NULL, sep_list); // verificare existenta token dupa medie in linia curenta file_buf
		if (token)
			printf("\nEroare preluare token!");
		// apel functie inserare nod in lista simpla
		prim = inserareSfarsitLista(prim, s);

		s.nume = NULL;
	}

	// parsare lista simpla pentru validare inserari
	printf("Traversare lista simpla dupa creare:\n");
	Nod* temp = prim;
	while (temp != NULL) {
		printf(" Student id: %d, %s, %s", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa); // \n dupa fiecare nr grupa deoarece fgets pune LF (0x0a) in ultimul token de pe fiecare linie

		temp = temp->next;
	}

	printf("\nNumarul de noduri din lista simpla dupa creare: %d\n", nrNoduri(prim));

	// dezalocare lista simpla
	while (prim)
		prim = stergereNodInceput(prim);

	printf("\nTraversare lista simpla dupa dezalocare:\n");
	temp = prim;
	while (temp != NULL) {
		printf(" Student id: %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

		temp = temp->next;
	}

	fclose(f);

}