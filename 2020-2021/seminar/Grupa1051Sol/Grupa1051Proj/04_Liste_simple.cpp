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
	Student stud;
	Nod* next;
};

Nod* inserare_inceput_lista(Nod* lst, Student s)
{
	Nod* nou;
	nou = (Nod*)malloc(1 * sizeof(Nod));

	nou->stud.id = s.id;
	nou->stud.nume = s.nume;
	strcpy(nou->stud.nrGrupa, s.nrGrupa);
	// nou->stud.nrGrupa = s.nrGrupa;	
	// nou->stud = s; // ??? 

	nou->next = lst;

	return nou; // se intoarce noul inceput de lista
}

Nod* stergere_inceput_lista(Nod* lst, Student &s)
{
	if (lst)
	{
		s.id = lst->stud.id;
		s.nume = lst->stud.nume;
		strcpy(s.nrGrupa, lst->stud.nrGrupa);

		Nod* t = lst; // vechiul inceput de lista

		lst = lst->next; // noul inceput de lista

		free(t); // dezalocare inceput vechi de lista
	}
	else
	{
		s.nume = NULL;
	}

	return lst;
}

Nod* inserare_interior_lista(Nod* lst, Student s, unsigned int pozitie)
{
	unsigned int n = 0; // n nr de noduri din lista simpla
	Nod* t = lst;
	while (t)
	{
		n += 1;
		t = t->next;
	}

	if (pozitie > 0 || pozitie <= n + 1)
	{
		if (pozitie == 1)
			lst = inserare_inceput_lista(lst, s);
		else
		{
			Nod* nou;
			nou = (Nod*)malloc(1 * sizeof(Nod));

			nou->stud.id = s.id;
			nou->stud.nume = s.nume;
			strcpy(nou->stud.nrGrupa, s.nrGrupa);
			// nou->stud.nrGrupa = s.nrGrupa;	
			// nou->stud = s; // ??? 

			// pozitionare pe nodul pozitie - 1
			unsigned int i = 1;
			t = lst;
			while (i != pozitie - 1)
			{
				t = t->next;
				i += 1;
			}
			// t este nodul de pe pozitie - 1
			nou->next = t->next;
			t->next = nou;
		}

	}
	 
	return lst;	
}


// TEMA
// stergere la interior
// interschimbare noduri adiacente
// interschimbare noduri oarecare
// concatenare de liste simple
// "spargerea" unei liste simple

int main() {
	Nod* prim = NULL; // lista simpla empty
	Student s;
	FILE* f;
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
		prim = inserare_inceput_lista(prim, s);		
	}

	s.nume = NULL; // eliminare partajare zona heap pt ultimul student inserat

	// traversare lista simpla
	printf("Continut lista simpla dupa creare:\n");
	Nod* t = prim; // t - locatie de memorie care stocheaza adresa de Nod
	while (t)
	{
		printf(" %d %s\n", t->stud.id, t->stud.nume); // "prelucrare" nod

		t = t->next; // var locala t in seg stack se rescrie cu adresa nodului succesor
	}

	// inserare la interior in lista simpla
	prim = stergere_inceput_lista(prim, s);
	prim = inserare_interior_lista(prim, s, 2);
	printf("Continut lista simpla dupa inserare la interior:\n");
	t = prim; // t - locatie de memorie care stocheaza adresa de Nod
	while (t)
	{
		printf(" %d %s\n", t->stud.id, t->stud.nume); // "prelucrare" nod

		t = t->next; // var locala t in seg stack se rescrie cu adresa nodului succesor
	}

	// afisare rezultat inserare la interior

	// dezalocare structura lista
	printf("\n\nStergerea listei simple:\n");
	while (prim)
	{
		prim = stergere_inceput_lista(prim, s); // dezalocare nod 1 din lista; salvare date student in s
		printf(" %d %s\n", s.id, s.nume);
		free(s.nume);
	}
	printf("\n\nLista simpla dupa dezalocare:\n");
	t = prim; 
	while (t)
	{
		printf(" %d %s\n", t->stud.id, t->stud.nume); // "prelucrare" nod

		t = t->next; // var locala t in seg stack se rescrie cu adresa nodului succesor
	}

	return 0;
}