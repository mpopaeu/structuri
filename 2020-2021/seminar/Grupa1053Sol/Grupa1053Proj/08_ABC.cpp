#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

// Definire structuri 
#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodABC {
	Student s;
	NodABC* st, * dr;
};


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
		TraversareInordine(r->st);
		printf("\n%d %s\n", r->s.id, r->s.nume);
		TraversareInordine(r->dr);
	}
}

int max(int x, int y)
{
	return x > y ? x : y;
}

int inaltime(NodABC* r)
{
	if (r)
	{
		// exista nod pentru care se poate calcula inaltime
		// r - radacina de subarbore din ABC
		return 1 + max(inaltime(r->st), inaltime(r->dr));
	}

	return 0; // r este pe pozitie de NULL in ABC (nu exista nod)
}

int numara_frunze(NodABC* r)
{
	if (r)
	{
		if (r->st == NULL && r->dr == NULL)
		{
			// r este frunza
			return 1;
		}

		return numara_frunze(r->st) + numara_frunze(r->dr);
	}

	return 0;
}

void salveaza_in_vector(NodABC* r, int* v, int &idx)
{
	if (r)
	{
		if (r->st == NULL && r->dr == NULL)
		{
			// r este frunza
			v[idx] = r->s.id;
			idx += 1;
		}

		salveaza_in_vector(r->st, v, idx);
		salveaza_in_vector(r->dr, v, idx);
	}
}

int* creare_vector_id(NodABC* r, int &n) // n - nr de frunze/studenti in noduri frunza
{
	n = numara_frunze(r);
	
	int* v = (int*)malloc(n * sizeof(int));

	int idx = 0;
	salveaza_in_vector(r, v, idx);

	return v;
}

// TEMA
// vector cu id studenti de pe drumul invers de la un nod/student identificat pe baza de id specificat
// stergere nod in ABC
// dezalocare ABC

// Creare ABC din Studenti.txt
int main() {

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
		// float test = 0; // test cu parametrul 3 ca referinta
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

	int h = inaltime(root);
	printf("\nInaltime ABC este: %d\n\n", h);

	int n;
	int* vFrunze = creare_vector_id(root, n);
	printf("\n Vector id studenti in noduri frunza: ");
	for (int i = 0; i < n; i++)
		printf(" %d ", vFrunze[i]);
	printf("\n\n");

	fclose(f);

	return 0;
}


