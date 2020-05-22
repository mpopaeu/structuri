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

void TraversareInordine(NodABC *r)
{
	if (r) {
		TraversareInordine(r->st);
		printf("%d %s\n", r->s.id, r->s.nume);
		TraversareInordine(r->dr);
	}
}

void nrFrunze(NodABC *r, int &nr) 
{
	if (r) {
		nrFrunze(r->st, nr);

		// prelucrare/vizitare nod curent
		if (r->st == NULL && r->dr == NULL)
			nr += 1;

		nrFrunze(r->dr, nr);
	}
}

//void salvareIDFrunze(NodABC *r, int * vFrunze, int offset)
//{
//
//}


// TEMA
// determinare nr noduri ABC
// determinare inaltime ABC
// determinare nr noduri de pe un nivel specificat in ABC
// salvare noduri (cheie id student) intr-un vector de pe un nivel specificat in ABC
// traversare preordine ABC
// traversare postordine ABC
// traversare pe niveluri ABC
// stergere nod din ABC

NodABC *stergereNod(NodABC *r, int idStud)
{
	if (r != NULL) {
		if (r->s.id == idStud)
		{
			// aplicare operatie stergere
			// nodul a fost identificat
			// 1. nod frunza
			// 2. nod cu 1 descendent
			// 3. nod cu 2 descendenti
			if ((r->st == NULL) && (r->dr == NULL))
			{
				// cazul 1
				free(r->s.nume); // dezalocare extensie/extensii student in heap
				free(r); // dezalocare nod
				r = NULL;
			}
			else
			{
				if ((r->st == NULL) || (r->dr == NULL))
				{
					// cazul 2
					NodABC* descendent = r->dr;
					if (descendent == NULL) descendent = r->st;
					free(r->s.nume);
					free(r);

					r = descendent;
				}
				else
				{
					// cazul 3 
					NodABC* cmsNod = r->dr; // radacina subarbore dreapta
					NodABC* parinteCMSNod = r->dr;

					// caz particular: radacina subarbore dreapta nu are nici un desc stanga adica este CMS
					// caut cel mai din stanga nod cu salvarea parintelui
					while (cmsNod->st != NULL) {
						// traversez pe stanga subarborelui

						parinteCMSNod = cmsNod;
						cmsNod = cmsNod->st;
					}
				}
			}
		}
		else
		{
			// cautare nod bazata pe relatiile de ordine ale ABC
			if (r->s.id > idStud)
				r->st = stergereNod(r->st, idStud);
			else
				r->dr = stergereNod(r->dr, idStud);
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
		// float test = 0; // test cu parametrul 3 ca referinta
		root = inserare(root, stud, err);
		if (err) {
			printf("\nStudentul cu id %d exista in arbore.\n", stud.id);
			free(stud.nume);
		}
		else
			printf("\nStudentul %s a fost inserat\n", stud.nume);

		stud.nume = NULL;
	}

	// validare structura arbore binar de cautare
	printf("Arbore binar de cautare dupa creare:\n");
	TraversareInordine(root);

	int nrFrunzeABC = 0;
	nrFrunze(root, nrFrunzeABC);
	printf("\nArborele are nr de frunze = %d\n\n", nrFrunzeABC);

	//int* vIDFrunze = new int[nrFrunzeABC];
	//int i = 0; // offset element 1 in vector
	//salvareIDFrunze(root, vIDFrunze, i);



	fclose(f);
}