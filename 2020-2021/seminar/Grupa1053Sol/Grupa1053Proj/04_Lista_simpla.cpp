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
		// exista cel putin 1 nod in lista
		st.id = lst->stud.id;
		st.nume = lst->stud.nume;
		strcpy(st.nrGrupa, lst->stud.nrGrupa);

		Nod* t = lst->next; // salvare adresa nod 2/NULL in t
		free(lst); // dezalocare prim nod in lista

		lst = t;
	}
	else
	{
		// nu exista nici un nod in lista
		st.nume = NULL;
	}

	return lst;
}

// concatenare a doua liste
// input: lst1, lst2 - liste simple
// output: lst3 - lista simpla; nu partajeaza zone de mem heap cu nici una din listele lst1, lst2

Nod* concatenare_liste(Nod* lst1, Nod* lst2) // ----> lst3 = { lst1, lst2 }
{

}


//////////////////////////////////////////////////////////////////////////////////
// TEMA
// inserare/stergere interior in/din lista simpla (definire cerinte)
// interschimbare noduri adiacente/oarecare in lista simpla (definire cerinte)
// deconcatenare lista simpla (definire cerinte)
//////////////////////////////////////////////////////////////////////////////////

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
		printf(" %d %s\n", t->stud.id, t->stud.nume);

		t = t->next; // t (locatie in stack seg) se rescrie cu continutul campului next (preluat din mem heap)
	}

	printf("\n\nDezalocare lista simpla:\n");
	while (prim)
	{
		prim = stergere_nod(prim, s);
		printf(" %d %s\n", s.id, s.nume);
		free(s.nume);
	}


	return 0;
}