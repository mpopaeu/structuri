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
// 1. lista contine 0 sau 1 nod -> nu exista interschimb
// 2. primul nod al interschimbului este ultimul nod / nu exista in lista -> interschimbul nu se realizeaza
// 3. primul nod al interschimbului este primul nod din lista -> modificare adresei de inceput al listei

Nod* interschimbNoduriAdiacente(Nod* lst, int idStud)
{
	// caz part 1
	if (lst == NULL || lst->next == NULL)  return lst;

	Nod *p = NULL, *q = NULL, *r = NULL, *s = NULL;
	// caz part 3
	if (lst->stud.id == idStud) {
		q = lst;
		r = q->next;
		s = r->next;

		q->next = s;
		r->next = q;

		return r;
	}

	// caz part 2
	// caz general
}

void main() {
	Nod* prim = NULL;
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
		
		// apel functie de inserare nod in lista simpla
		prim = inserareNodSfarsit(prim, s);

		s.nume = NULL; // eliminare partajare zona hep pt ultimul student inserat
	}

	printf("Traversare lista simpla dupa creare:\n");
	Nod* temp = prim;
	while (temp != NULL) {
		printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

		temp = temp->next;
	}


	fclose(f);
}