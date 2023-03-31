#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	float medie; // data derivata
};

struct Nod {
	struct Student st; // Student *st;
	struct Nod* next;
};

struct Nod* inserareLista(struct Nod* p, struct Student s) {
	struct Nod* nou;
	nou = (struct Nod*)malloc(1 * sizeof(struct Nod));

	nou->st = s;
	nou->next = p;

	return nou;
}

void parseList(struct Nod* p) {
	while (p) {
		printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie);

		p = p->next;
	}
}

struct Student stergereStudent(struct Nod* * p) {
	struct Nod* tmp = *p;
	struct Student s;
	if (tmp) {
		if (tmp->next) { //  cel putin doua noduri in lista
			while (tmp->next->next)
				tmp = tmp->next;
			s = tmp->next->st;  // salvare student in var locala s

			free(tmp->next);  // dezalocare ultimul nod din lista simpla
			tmp->next = 0; // actualizare adresa legatura 
		}
		else {  // caz particular; un singur nod in lista
			s = tmp->st;  // salvare student din cap lista

			free(tmp);  // dezalocare cap de lista
			*p = 0;
		}
	}

	return s;
}

int main() {

	struct Nod* prim = NULL; // pointer adresa nod inceput lista -> gestionare
				   // structura de date lista simpla

	struct Student stud; // buffer incarcare date din fisier
				  // suprascris pentru fiecare student preluat din fisier

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token); // conversie ASCII-to-int

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token); // nu are loc conversie

		token = strtok(NULL, sep_list);
		stud.medie = (float)atof(token); // conversie ASCII-to-float

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		prim = inserareLista(prim, stud);
	}

	printf("\nLista dupa creare:\n");
	parseList(prim);


	if (prim)   // stergere student (dezalocare ultim nod)
		stud = stergereStudent(&prim);

	printf("\nLista dupa stergere student din lista:\n");
	parseList(prim);
	printf("Student extras din lista: %d %s\n", stud.id, stud.nume);
	// dezalocare nume student
	free(stud.nume);

	// dezalocare structura lista simpla
	while (prim) {
		stud = stergereStudent(&prim);
		printf("Student extras la dezalocare lista: %d %s\n", stud.id, stud.nume);
		free(stud.nume);
	}

	printf("Lista dupa dezalocare:\n");
	parseList(prim);

	fclose(f);

	return 0;
}