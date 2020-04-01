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

// stergere/dezalocare nod din lista simpla (la inceputul listei)

// dezalocare lista simpla

// interschimb de noduri adiacente prin modificarea adreselor de legatura (prin modificare campuri next)

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

	fclose(f);
}