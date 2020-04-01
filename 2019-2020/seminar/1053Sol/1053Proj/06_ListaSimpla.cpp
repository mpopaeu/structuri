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
void printList(Nod* lst) {
	Nod* temp = lst;
	while (temp) {
		printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

		temp = temp->next;
	}
}

// stergere/dezalocare nod din lista simpla (la inceputul listei)

// dezalocare lista simpla

// interschimb de noduri adiacente prin modificarea adreselor de legatura (prin modificare campuri next)
Nod* interschimbAdiacente(Nod* lst, int poz) { // poz - pozitia nodului 1 din interschimb 
	Nod *p, *q, *r, *s;
	// cazuri particulare
	// 1. lista contine 0 sau 1 nod -> interschimb ne-efectuat
	if (lst == NULL || lst->next == NULL)
		return lst;
	// 2. poz == 1 (interschimba nodul 1 cu nodul 2 in lista) -> un nou inceput de lista simpla
	if (poz == 1) {
		q = lst;
		r = lst->next;
		s = r->next;

		// modificare adrese de legatura
		q->next = s;
		r->next = q;
		lst = r; // actualizare adresa de inceput lista simpla
	}
	else {
		// 3. poz == n (n - nr de noduri in lista); nodul 1 din interschimb este ultimul din lista -> interschimb ne-efectuat
		// 4. poz > n (n - nr noduri in lista)
		// caz general; pozitionare pe poz -> interschimb nod de pe poz cu nod de pe poz+1
		p = lst;
	}

	return lst;
}

void main() {
	Nod * prim = NULL; 
	Student s;

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {

		// incarcare date student in variabila s
		token = strtok(file_buf, sep_list);
		s.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		s.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(s.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(s.nrGrupa, token);

		// inserare student in lista simpla (prim)
		prim = insertNodeEnd(prim, s);

		s.nume = NULL; // evitare partajare zona de memorie aferenta numelui de student
	}

	printf("Lista dupa creare:\n");
	printList(prim);

	fclose(f);
}