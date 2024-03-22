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

struct Student stergereStudent(struct Nod** p) {
	struct Nod* tmp = *p;
	struct Student s;
	if (tmp) {
		if (tmp->next) { //  cel putin doua noduri in lista
			while (tmp->next->next)
				tmp = tmp->next; // parsare lista simpla pana la penultimul nod
			s = tmp->next->st;  // salvare student in var locala s

			free(tmp->next);  // dezalocare nod lista simpla
			tmp->next = 0; // actualizare adresa legatura (penultimul nod in lista devine nou sfarsit de lista)
		}
		else {  // caz particular; un singur nod in lista
			s = tmp->st;  // salvare student din cap lista

			free(tmp);  // dezalocare cap de lista
			*p = 0; // *p = NULL;
		}
	}

	return s;
}

void parseList(struct Nod* p) {
	while (p) {
		printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie);

		p = p->next;
	}
}


int main() {

	struct Nod* prim = NULL; // pointer adresa nod inceput lista -> gestionare structura

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		struct Student stud;		// buffer incarcare date din fisier
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = (float)atof(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare acces la token (sub-string)!");

		// inserare nod la inceputul listei
		prim = inserareLista(prim, stud);
	}

	struct Student student_salvat = stergereStudent(&prim);
	printf("Student extras din lista simpla: %d %s\n", student_salvat.id, student_salvat.nume);
	free(student_salvat.nume);

	// dezalocare lista simpla
	while (prim)
	{
		student_salvat = stergereStudent(&prim);
		free(student_salvat.nume);
	}

	printf("Lista simpla dupa dezalocare:\n");
	parseList(prim);

	fclose(f);
	return 0;
}