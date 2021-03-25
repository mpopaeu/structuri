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
		// lista cu cel putin 1 nod
		st.id = lst->stud.id;
		st.nume = lst->stud.nume;
		strcpy(st.nrGrupa, lst->stud.nrGrupa);

		Nod* t = lst->next; // t este adresa nodului 2

		free(lst);

		lst = t;
	}
	else
	{
		// lista are 0 noduri
		st.nume = NULL;
	}

	return lst;
}


// functie
// creare lista simpla (a 2-a lista din app) care contine studentii cu id in interval specificat
// input: lista simpla, interval de valori
// output: o lista diferita cu studenti filtrati dupa id; noua lista nu partajeaza zone de mem heap cu cealalta


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
	Nod* t = prim; // t variabila locala, pointer (stocheaza adresa de memorie unde se afla un nod in heap)
	while (t)
	{
		printf(" %d %s\n", t->stud.id, t->stud.nume);

		t = t->next; // continut camp next din mem heap este copiat in t locatie de mem stack (var locala)
	}

	Nod* prim2 = NULL; // adresa de inceput a listei nr 2


	printf("\n\nDezalocare lista simpla:\n");
	while (prim)
	{
		prim = stergere_nod(prim, s); // dezaloca primul nod; NU se dezaloca nume student

		printf(" %d %s\n", s.id, s.nume);

		free(s.nume);  // dezalocare nume stundent extras din primul nod al listei
	}

	return 0;
}