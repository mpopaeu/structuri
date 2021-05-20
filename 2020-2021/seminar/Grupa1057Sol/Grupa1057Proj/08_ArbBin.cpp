#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

// Definire structuri 

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodABC {
	Student s;
	NodABC* st, * dr;
};

/*
struct StudentNode {
	int id;
	char* nume;
	char nrGrupa[5];
	StudentNode* next, * prev;
};
*/


// Inserare nod in ABC 
NodABC* inserare(NodABC* r, Student student, int& er)
{
	if (r == NULL) {
		NodABC* nou = new NodABC;
		nou->dr = NULL;
		nou->st = NULL;

		nou->s.id = student.id;
		nou->s.nume = student.nume;
		strcpy(nou->s.nrGrupa, student.nrGrupa);

		r = nou;
	}
	else if (r->s.id == student.id) er = 1;
	else if (r->s.id > student.id)
		r->st = inserare(r->st, student, er);
	else
		r->dr = inserare(r->dr, student, er);

	return r;
}


// Traversare inordine ABC
void TraversareInordine(NodABC* r)
{
	if (r) {
		TraversareInordine(r->st); // prelucrare in inordine a nodurilor din subarborele stanga
		printf("%d %s\n", r->s.id, r->s.nume); // prelucrare nod curent
		TraversareInordine(r->dr); // prelucrare in inordine a nodurilor din subarborele dreapta
	}
}

int max(int x, int y)
{
	return x > y ? x : y;
}

int inaltime_arbore(NodABC* r)
{
	if (r)
	{
		return 1 + max(inaltime_arbore(r->st), inaltime_arbore(r->dr));
	}

	return 0;
}

// dezalocare structura ABC
NodABC* dezalocare_arbore(NodABC* r)
{
	if (r)
	{
		// exista nod curent r pentru care se dezaloca descendentii si dupa nodul curent
		r->st = dezalocare_arbore(r->st);
		r->dr = dezalocare_arbore(r->dr);

		// prelucrare/vizitare (dezalocare) nod curent
		free(r->s.nume);
		free(r);
		r = NULL;
	}

	return r; // NULL pentru fiecare apel
}

// determinare numar de noduri frunza din ABC
// extragere nod din ABC

// Creare ABC din Studenti.txt
void main() {

	Student stud;
	NodABC* root = NULL;

	FILE* f;
	f = fopen("Studenti.txt", "r");
	char studBuff[20];

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";

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

	// traversare in inordine (ordine crescatoare id-uri studenti)
	printf("\nTraversare arbore inordine:\n");
	TraversareInordine(root);

	int h = inaltime_arbore(root);
	printf("\nInaltime arbore: %d.", h);

	// dezalocare arbore binar de cautare
	root = dezalocare_arbore(root);
	root = NULL;
	printf("\nTraversare arbore inordine dupa dezalocare:\n");
	TraversareInordine(root);

	fclose(f);
}

