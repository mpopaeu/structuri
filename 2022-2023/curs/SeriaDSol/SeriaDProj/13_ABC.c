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
		TraversareInordine(r->st);
		printf("\n%d %s\n", r->s.id, r->s.nume);
		TraversareInordine(r->dr);
	}
}

int main() {

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

	// stergere nod in arbore binar de cautare
	// dezalocare structura arbore binar de cautare

	return 0;
}

