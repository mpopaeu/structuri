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

Nod* inserare_nod_inceput(Nod* lst, Student s)
{
	Nod* nou;
	nou = (Nod*)malloc(1 * sizeof(Nod));

	nou->stud.id = s.id;
	nou->stud.nume = s.nume;
	strcpy(nou->stud.nrGrupa, s.nrGrupa);

	nou->next = lst;

	return nou;
}

Nod* stergere_nod_inceput(Nod* lst, Student &s)
{
	if (lst) // exista cel putin 1 nod
	{
		s.id = lst->stud.id;
		s.nume = lst->stud.nume;
		strcpy(s.nrGrupa, lst->stud.nrGrupa);

		Nod* t = lst;
		lst = lst->next;

		free(t);
	}
	else
	{
		// nu exista nod in lista; initializare diferita/convenabila pt s
		s.nume = NULL;
	}

	return lst;
}


// TEMA
// inserare/stergere de nod in/din interiorul listei
// interschimb noduri adiacente/oarecare in lista simpla
// concatenare de liste simple 
// de-concatenare ("spargere", "rupere") lista simpla in mai multe liste

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
		prim = inserare_nod_inceput(prim, s);

		s.nume = NULL; // eliminare partajare zona heap pt ultimul student inserat
	}

	printf("Lista simpla dupa creare:\n");
	Nod* t = prim;
	while (t)
	{
		printf(" %d %s\n", t->stud.id, t->stud.nume); // prelucrare nodului curent t

		t = t->next;
	}


	// dezalocare lista simpla
	printf("\n\nDezalocare lista simpla:\n");
	while (prim)
	{
		prim = stergere_nod_inceput(prim, s);

		printf(" %d %s\n", s.id, s.nume);
		free(s.nume);
	}

	return 0;
}