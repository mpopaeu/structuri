#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char *nume;
	char nrGrupa[5];
};

struct NodABC {
	Student s;
	NodABC *st, *dr;
};


NodABC *inserare(NodABC *r, Student st, int &er)
{
	if (r == NULL) {
		NodABC *nou = new NodABC;
		nou->dr = NULL;
		nou->st = NULL;
		// nou->s = st;
		nou->s.id = st.id;
		nou->s.nume = st.nume;
		strcpy(nou->s.nrGrupa, st.nrGrupa);
		r = nou;
	}
	else if (r->s.id == st.id) er = 1;
	else if (r->s.id > st.id)
		r->st = inserare(r->st, st, er);
	else
		r->dr = inserare(r->dr, st, er);
	return r;
}

void Inordine(NodABC *r)
{
	if (r)
	{
		Inordine(r->st);
		printf(" %d ", r->s.id);
		Inordine(r->dr);
	}
}

int max(int x, int y)
{
	return x > y ? x : y;
}

int Inaltime(NodABC* r)
{
	if (r)
	{
		return 1 + max(Inaltime(r->st), Inaltime(r->dr));
	}
	return 0;
}

// TEMA
// stergere a unui nod in ABC
// determinare numar de noduri frunza in ABC

int main()
{
	Student stud;
	NodABC *root = NULL;

	FILE * f;
	f = fopen("Studenti.txt", "r");
	char studBuff[20];

	char * token, file_buf[LINESIZE], sep_list[] = ",\n";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(stud.nrGrupa, token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare student in ABC
		int err = 0;
		root = inserare(root, stud, err);
		if (err) {
			printf("\nStudentul cu id %d exista in arbore.\n", stud.id);
			free(stud.nume);
		}
		else
			printf("\nStudentul %s a fost inserat\n", stud.nume);
	}

	printf(" Arborele binar de cautare dupa creare: ");
	Inordine(root);
	printf("\n\n");

	printf("Inaltime arbore binar de cautare: %d niveluri\n\n", Inaltime(root));

	fclose(f);
}