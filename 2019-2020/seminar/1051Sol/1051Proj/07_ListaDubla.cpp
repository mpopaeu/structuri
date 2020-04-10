
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
	Student stud;
	NodD *next, *prev;
};

struct ListDubla {
	NodD *prim, *ultim;
};

ListDubla inserareNodSfarsitLD(ListDubla lista, Student s) {
	NodD* nou;
	nou = (NodD*)malloc(sizeof(NodD));

	nou->stud.id = s.id;
	nou->stud.nume = s.nume; // partajare temporara nume student ca si locatie de heap
	strcpy(nou->stud.nrGrupa, s.nrGrupa);

	nou->next = NULL; // nou devine ultimul nod in lista simpla
	nou->prev = lista.ultim;

	if (lista.prim == NULL) // nu exista nici un nod in lista
		lista.prim = lista.ultim = nou;
	else {
		// lista are cel putin 1 nod		
		lista.ultim->next = nou;
		lista.ultim = nou;		
	}

	return lista;
}

// interschimb noduri adiacente (lista dubla) cu modificarea adreselor de legatura
// 1. lista contine 0 sau 1 nod -> nu exista interschimb
// 2. primul nod al interschimbului este ultimul nod / nu exista in lista -> interschimbul nu se realizeaza
// 3. primul nod al interschimbului este primul nod din lista 
	// 3.1 lista are cel putin 3 noduri -> modificare adresa de inceput
	// 3.2 lista are DOAR 2 noduri -> modificare ambele capete de lista (inceput si sfarsit de lista dubla)
// 4. primul nod al interschimbului este penultimul in lista dubla -> modificare capat de sfarsit (sfarsit de lista dubla)
ListDubla interschimbNoduriAdiacenteLD(ListDubla lst, int idStud)
{
	// caz part 1
	if (lst.prim == NULL || lst.prim->next == NULL)  return lst;

	NodD *p = NULL, *q = NULL, *r = NULL, *s = NULL;
	// caz part 3
	if (lst.prim->stud.id == idStud) {
		q = lst.prim;
		r = q->next;
		s = r->next;

		q->next = s;
		r->next = q;

		q->prev = r;
		r->prev = NULL; // r devine primul nod in lista dubla
		lst.prim = r;

		if (s != NULL) {
			// lista dubla contine cel putin 3 noduri (caz 3.1)
			s->prev = q;
		}
		else {
			// lista dubla contine DOAR 2 noduri (caz 3.2)
			lst.ultim = q;
		}

		return lst;
	}

	// caz part 2 + 4
	// caz general
	p = lst.prim;

	// traversare lista simpla cu vericare id student
	// p este nodul predecesor lui q, deci se testeaza id student din p->next
	while (p->next)
	{
		q = p->next;
		if (q->stud.id == idStud) {
			// studentul a fost identificat in lista
			if (q->next != NULL) { // q->next == NULL inseamna q ultimul nod; se termina de traversat lista si se inchide while
				// cazul general
				// caz part 4
				r = q->next;
				s = r->next;

				p->next = r;
				q->next = s;
				r->next = q;
				q->prev = r;
				r->prev = p;

				if (s != NULL) {
					// cazul general; interschimb in interiorul listei duble -> nu se actualizeaza nici un capat al listei
					s->prev = q;
				}
				else {
					// cazul part 4, se interschimba ultimele doua noduri -> se modifica sfarsitul de lista
					lst.ultim = q;
				}

				return lst;
			}
		}

		p = p->next;
	}

	return lst; // caz part 2: q este ultimul nod sau q nu exista in lista simpla
}

// interschimb noduri oarecare in lista dubla
// sortare pe lista dubla
// dezalocare lista dubla

// implementare QuickSort (vector, lista simpla/dubla)

void main() {
	ListDubla lst;
	lst.prim = lst.ultim = NULL; // initial, lista  dubla nu contine nici un nod

	Student s;
	FILE* f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		// preluare continut fisier studenti; se initializeaza temporarul s
		token = strtok(file_buf, sep_list);
		s.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		s.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(s.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(s.nrGrupa, token);

		// apel functie de inserare nod in lista dubla
		lst = inserareNodSfarsitLD(lst, s);

		s.nume = NULL; // eliminare partajare zona hep pt ultimul student inserat
	}

	printf("Traversare lista dubla dupa creare:\n");
	NodD* temp = lst.prim;
	while (temp != NULL) {
		printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

		temp = temp->next;
	}

	fclose(f);
}