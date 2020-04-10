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

struct NodD {
	Student stud; // date propriu-zise
	NodD *next, *prev; // date de legatura (relatii de ordine pe elemente de tip NodD)
};

struct ListaDubla {
	NodD *prim, *ultim;
};

ListaDubla inserareSfarsitListaDubla(ListaDubla lst, Student s) {
	NodD* nou;
	nou = (NodD*)malloc(sizeof(NodD)); 

	nou->stud.id = s.id;
	nou->stud.nume = s.nume; // asumare s.nume va fi copiat peste nou->nume
	strcpy(nou->stud.nrGrupa, s.nrGrupa);
	nou->next = NULL;
	nou->prev = lst.ultim;

	if (lst.prim == NULL) { // lista dubla nu contine nici un nod/element
		lst.prim = lst.ultim = nou;
	}
	else {
		// legare ultimul nod din lista la nodul nou
		lst.ultim->next = nou;
		lst.ultim = nou;
	}

	return lst;
}

// interschimb noduri adiacente in lista dubla

ListaDubla interschimbAdiacente(ListaDubla lst, int idStud) {
	NodD *p, *q, *r, *s;

	// cazuri particulare
	//		1. lista contine cel mult 1 nod - se abandoneaza operatia
	if (lst.prim == NULL || lst.prim->next == NULL)
		return lst;

	//		2. primul nod din interschimb este lst (se interschimba nodul 1 cu 2) - are loc interschimb, se returneaza noul inceput de lista
	if (lst.prim->stud.id == idStud) {
		// initializam cele 3 noduri implicate in interschimb
		q = lst.prim; // nodul 1
		r = lst.prim->next; // nodul 2
		s = r->next; // nodul 3/NULL

		if (s != NULL) { // r nu este ultimul nod din lista dubla
			q->next = s; // q devine nodul 2
			r->next = q; // r devine nodul 1

			// actualizare predecesori pentru nodurile q, r si s
			q->prev = r;
			r->prev = NULL;
			s->prev = q;
			// actualizare inceput de lista dubla
			lst.prim = r;
		}
		else {
			// caz particular 5: exista 2 noduri in lista dubla care se interschimba
			// se actualizeaza ambele capete de lista dubla
			q->next = s; // q devine nodul 2
			r->next = q; // r devine nodul 1
			// actualizare predecesori DOAR pentru nodurile q si r
			q->prev = r;
			r->prev = NULL;
			// actualizare inceput si sfarsit de lista dubla
			lst.prim = r;
			lst.ultim = q;
		}
		return lst; // actualizare adresa de inceput de lista in apelator
	}

	//		3. primul nod din interschimb este ultimul din lista (nu exista nodul 2) - se abandoneaza operatia
	//		4. primul nod din interschimb nu este identificat - nu are sens operatia de interschimb
	// caz general
	// traversre lista in vederea identificarii primului nod din interschimb (q)
	p = lst.prim;
	while (p->next) {
		q = p->next;
		if (q->stud.id == idStud) {
			// am identificat primul nod din interschimb
			// caz 3 / caz general
			if (q->next != NULL) { // daca FALSE -> caz particular 3; q este ultimul nod din lista, nu exista r pt interschimb
								   // caz general
				r = q->next;
				s = r->next;

				if (s != NULL) {
					p->next = r;
					r->next = q;
					q->next = s;

					q->prev = r;
					r->prev = p;
					s->prev = q;
				}
				else {
					// caz particular 6
					// s == NULL, r este de fapt ultimul nod din lista dubla -> se actualizeaza sfarsitul de lista
					p->next = r;
					r->next = q;
					q->next = s;

					q->prev = r;
					r->prev = p;

					// actualizarea sfarisutlui de lista dubla
					lst.ultim = q;
				}
			}

			return lst;
		}

		p = p->next;
	}

	//p->next == NULL -> q == NULL, deci caz particular 4
	return lst;
}


// interschimb noduri oarecare in lista dubla
// sortare noduri lista dubla

// implementare QuickSort -> stiva/stive

void main() {
	ListaDubla ld;
	ld.prim = ld.ultim = NULL; // lista dubla este goala / empty
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
		// apel functie inserare nod in lista dubla
		ld = inserareSfarsitListaDubla(ld, s);

		s.nume = NULL;
	}

	// parsare lista dubla pentru validare inserari
	printf("\n\nTraversare lista dubla dupa creare:\n");
	NodD* temp = ld.prim;
	while (temp != NULL) {
		printf(" Student id: %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa); // \n dupa fiecare nr grupa deoarece fgets pune LF (0x0a) in ultimul token de pe fiecare linie

		temp = temp->next;
	}

	fclose(f);
}