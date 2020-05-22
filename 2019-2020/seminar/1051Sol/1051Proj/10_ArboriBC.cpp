#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
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

void TraversareInordine(NodABC *r)
{
	if (r) {
		TraversareInordine(r->st);
		printf("%d %s\n", r->s.id, r->s.nume);
		TraversareInordine(r->dr);
	}
}

void TraversarePreordine(NodABC *r)
{
	if (r) {
		printf("%d %s\n", r->s.id, r->s.nume);
		TraversarePreordine(r->st);
		TraversarePreordine(r->dr);
	}
}

void noduriNivel(NodABC *r, int nivel)
{
	if (r) {
		if(nivel == 1)
			printf("%d %s\n", r->s.id, r->s.nume);

		nivel -= 1;
		noduriNivel(r->st, nivel);
		noduriNivel(r->dr, nivel);
	}
}

int max(int x, int y)
{
	if (x < y)
		return y;

	return x;
}

int inaltimeArbore(NodABC *r)
{
	if (r)
		return 1 + max(inaltimeArbore(r->st), inaltimeArbore(r->dr));
	return 0;
}


// TEMA
// determinare nr noduri frunza pe un nivel specificat
// copiere noduri de pe un nivel specificat (vector/lista simpla)
// stergerea unui nod in ABC
// traversare ABC pe niveluri
// determinare noduri plasate pe drumul de la radacina la nod specificat prin id

NodABC *stergere(NodABC *r, int idStud)
{
	if (r != NULL) {
		if (r->s.id > idStud)
			r->st = stergere(r->st, idStud);
		else
			if(r->s.id < idStud)
			r->dr = stergere(r->dr, idStud);
			else
			{
				//nodul de sters a fost identificat si este r
				if (r->st== NULL && r->dr == NULL)
				{
					// cazul 1: nod frunza
					free(r->s.nume); // dezalocare nume student
					free(r); // dezalocare nod
					r = NULL;
				}
				else
				{
					if (r->st == NULL || r->dr == NULL)
					{
						// cazul 2: nodul de sters are 1 desc
						NodABC * descendent = r->dr;
						if (descendent == NULL) descendent = r->st;


						free(r->s.nume); // dezalocare nume student
						free(r); // dezalocare nod
						r = descendent;
					}
					else {
						// cazul 3: nodul de sters are 2 desc
					}
				}
			}
	}
	

	return r;
}

void main() {

	Student stud;
	NodABC *root = NULL;

	FILE * f;
	f = fopen("Studenti.txt", "r");
	char studBuff[20];

	char * token, file_buf[LINESIZE], sep_list[] = ",";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(stud.nrGrupa, token);


		// inserare student in ABC
		int err = 0;
		root = inserare(root, stud, err);
		if (err) {
			printf("\nStudentul cu id %d exista in arbore.\n", stud.id);
			free(stud.nume);
		}
		else
			printf("\nStudentul %s a fost inserat\n", stud.nume);

		stud.nume = NULL;
	}


	printf("\nArborele dupa creare:\n\n");
	TraversareInordine(root);

	printf("\nTraversare preordine arbore:\n\n");
	TraversarePreordine(root);

	int nivel = 2;
	printf("\n\nNoduri de pe nivel specificat: %d\n", nivel);
	noduriNivel(root, nivel);

	printf("\n\nInaltime arbore: %d\n", inaltimeArbore(root));

	printf("\n\n");

	fclose(f);
}