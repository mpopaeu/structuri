#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct Nod {
	Student stud; // date propriu-zise care urmeaza a fi prelucrate
	Nod* next; // date de legatura (se asigura inlantuirea nodurilor)
};

Nod* inserare_nod(Nod* lst, Student st)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->stud.id = st.id;
	nou->stud.nume = st.nume;
	strcpy(nou->stud.nrGrupa, st.nrGrupa);

	nou->next = lst;

	return nou;
}

Nod* stergere_nod(Nod* lst, Student &st)
{
	if (lst)
	{
		// lista contine cel putin 1 nod

		// salvare date student in parametrul st
		st.id = lst->stud.id;
		st.nume = lst->stud.nume;
		strcpy(st.nrGrupa, lst->stud.nrGrupa);

		Nod *t = lst;

		lst = lst->next; // actualizare inceput de lista (adresa nod 2, daca exista)
		free(t);		// dezalocare nod 
	}
	else
	{
		// lista contine 0 noduri
		st.nume = NULL;
	}

	return lst;
}

// functie care creeaza un vector cu studenti (din lista simpla) care fac parte din aceeasi grupa
// input: lista simpla, nr grupa selectie studenti
// output: vector de studenti (id, nume student) in aceeasi grupa, dimensiune vector; 
// studentii din vector nu partajeaza zone de heap cu nodurile din lista simpla


int main() {
	Nod* prim = NULL; // lista simpla empty
	Student s;
	FILE* f; // pointer la structura FILE
	f = fopen("Studenti.txt", "r");

	char * token, sep_list[] = ",\n";
	char file_buf[LINESIZE];
	while (fgets(file_buf, sizeof(file_buf), f)) {
		// preluare continut fisier studenti; se initializeaza temporarul s
		token = strtok(file_buf, sep_list);
		s.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		s.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(s.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(s.nrGrupa, token);

		// operatie pe lista simpla (inserare in lista simpla)
		prim = inserare_nod(prim, s);

		s.nume = NULL; // eliminare partajare zona heap pt ultimul student inserat
	}

	printf("Lista simpla dupa creare:\n");
	Nod* t = prim;
	while (t)
	{
		printf(" %d %s\n", t->stud.id, t->stud.nume); // prelucrarea unui nod din lista simpla

		t = t->next;
	}


	// dezalocare lista simpla
	printf("\n\nDezalocare lista simpla:\n");
	while (prim)
	{
		prim = stergere_nod(prim, s);
		printf(" %d %s\n", s.id, s.nume);

		free(s.nume);
	}

	return 0;
}