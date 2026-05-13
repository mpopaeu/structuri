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
		// nodul inserat in arbore va fi frunza intotdeuna
		nou->dr = NULL;
		nou->st = NULL;
		nou->s = st;
		r = nou;
	}
	else if (r->s.id == st.id) *er = 1; // cheia de inserat exista deja in arbrore; se abandoneaza operatia de inserare
	else if (r->s.id > st.id)
		r->st = inserare(r->st, st, er); // continua cautarea in sub-arbore stanga
	else
		r->dr = inserare(r->dr, st, er); // continua cautarea in sub-arbore dreapta
	return r;
}

void TraversareInordine(struct NodABC* r)
{
	if (r) {
		TraversareInordine(r->st); // prelucrare noduri din sub-arbore stanga

		printf("\n%d %s\n", r->s.id, r->s.nume); // prelucrare nod curent

		TraversareInordine(r->dr); // prelucrare noduri din sub-arbore dreapta
	}
}

struct NodABC* dezalocareArbore(struct NodABC* r)
{
	if (r != NULL)
	{
		r->st = dezalocareArbore(r->st);
		r->dr = dezalocareArbore(r->dr);

		// nodul curent r devine nod frunza, deci poate fi dezalocat
		free(r->s.nume); // dezalocare extensie student pentru stocare string nume
		free(r);  // dezalocare nod curent 

		r = NULL;
	}

	return r;
}

struct Student* cautareStudent(struct NodABC* r, int cheie)
{
	if (r != NULL)
	{
		if (r->s.id == cheie) return &r->s ; // studentul este identificat in ABC si se intoarce adresa sa din nodul in care este stocat
		else if (r->s.id > cheie)
			return cautareStudent(r->st, cheie); // continua cautarea in sub-arbore stanga
		else
			return cautareStudent(r->dr, cheie); // continua cautarea in sub-arbore dreapta
	}

	return NULL;
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
	printf("\nTraversare arbore inordine:\n");
	TraversareInordine(root);

	struct Student* pStud = cautareStudent(root, 121);
	printf("\n////// CAUTARE STUDENT DUPA CHEIE ///////\n");
	if (pStud == NULL)
	{
		printf("Studentul cautat dupa cheie nu a fost identificat in ABC\n");
	}
	else
	{
		printf("Student identificat: %d %s\n", pStud->id, pStud->nume);
	}


	root = dezalocareArbore(root);
	printf("\nTraversare arbore inordine dupa dezalocare:\n");
	TraversareInordine(root);
}

