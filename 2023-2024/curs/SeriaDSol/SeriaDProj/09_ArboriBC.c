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

struct NodABC {
	struct Student s;
	struct NodABC* st, * dr;
};


struct NodABC* inserare(struct NodABC* r, struct Student st, int* er)
{
	if (r == NULL) {
		struct NodABC* nou = (struct NodABC*)malloc(sizeof(struct NodABC));
		nou->dr = NULL;
		nou->st = NULL;
		nou->s = st;
		r = nou;
	}
	else if (r->s.id == st.id) *er = 1;
	else if (r->s.id > st.id)
		r->st = inserare(r->st, st, er);
	else
		r->dr = inserare(r->dr, st, er);
	return r;
}

void TraversareInordine(struct NodABC* r)
{
	if (r) {
		TraversareInordine(r->st);		// vizitare noduri cu chei mai mici decat r->st.id
		printf("\n%d %s\n", r->s.id, r->s.nume); // prelucrare nod r (date din r->st)
		TraversareInordine(r->dr);		// vizitare noduri cu chei mai mari decat r->st.id
	}
}


struct NodABC* StergerePostordine(struct NodABC* r)
{
	if (r != NULL) {
		StergerePostordine(r->st);		// stergere noduri cu chei mai mici decat r->st.id
		StergerePostordine(r->dr);		// stergere noduri cu chei mai mari decat r->st.id
		// prelucrare nod curent r (dezalocare)
		free(r->s.nume); // dezalocare heap relativ la date Student
		free(r);		 // dezalocare heap pentru nodul curent r
		r = NULL;
	}

	return r;
}

void main() {

	struct Student stud;
	struct NodABC* root = NULL;

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = (float)atof(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare student in ABC
		int err = 0;
		// float test = 0; // test cu parametrul 3 ca referinta
		root = inserare(root, stud, &err);
		if (err) {
			printf("\nStudentul cu id %d exista in arbore.\n", stud.id);
			free(stud.nume);
		}
		else
			printf("\nStudentul %s a fost inserat\n", stud.nume);
	}

	fclose(f);

	// traversare in inordine (ordine crescatoare id-uri studenti)
	printf("\nTraversare arbore inordine:\n\n");
	TraversareInordine(root);

	// dezalore arbore binar de cautare
	root = StergerePostordine(root);
	printf("\nTraversare arbore dupa dezalocare:\n\n");
	TraversareInordine(root);
}

