#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LINESIZE 128
#define DIM_VECTOR 100

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

int max(int x, int y) {
	if (x < y)
		return y;
	return x;
}

// determinare numar de niveluri ABC (inaltime ABC)
int inaltimeABC(NodABC * r) 
{
	if (r)
		return 1 + max(inaltimeABC(r->st), inaltimeABC(r->dr));
	return 0;
}

// determinare nr de noduri de pe un nivel specificat
void nrNoduriNivel(NodABC * r, int nivel, int &nr)
{
	if (r) {
		nrNoduriNivel(r->st, nivel - 1, nr);
		
		// validare pozitie pe nivel curent si incrementare nr

		nrNoduriNivel(r->dr, nivel - 1, nr);
	}
}

// TEMA
// determinare numar frunze ABC
// copiere noduri de pe nivel specificat in structura suport (vector/lista)
// copiere noduri frunza in structura suport (vector/lista)
// determinare niveluri pe care se afla noduri frunza
// determinare numar de noduri cu 2 descendenti
// noduri plasate pe drumul de la radacina la un nod specificat prin id student. Copiere noduri in structura suport (vector/lista)

// stergere nod din ABC
NodABC *stergere(NodABC *r, int idStud)
{
	if (r != NULL) {		
		if (r->s.id > idStud)
			r->st = stergere(r->st, idStud);
		else
			if (r->s.id < idStud)
				r->dr = stergere(r->dr, idStud);
			else
			{
				// am identificat nodul de sters
				if ((r->st == NULL) && (r->dr == NULL))
				{
					// cazul 1 : nod frunza
					free(r->s.nume); // dezalocare nume student din nod
					free(r); // dezalocare nod ABC
					r = NULL;
				}
				else
				{
					if ((r->st == NULL) || (r->dr == NULL))
					{
						// cazul 2 : 1 descendent
						NodABC* descendent = r->st;
						if (descendent != NULL)
							descendent = r->dr;

						free(r->s.nume);
						free(r);

						r = descendent;
					}
					else
					{
						// cazul 3: 2 descendenti
						NodABC * cms, *parinteCMS = NULL;
						cms = r->dr;
						while (cms->st != NULL)
						{
							parinteCMS = cms;
							cms = cms->st;
						}

						// interschimbul nod curent r cu cms

						if (parinteCMS == NULL)
						{
							// cms nod este radacina de subarbore dreapta
						}
						else
						{
							// am identificat cms nod si pe parintele sau
							parinteCMS->st = NULL;
						}
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

	printf("\nArborele binar de cautare dupa creare:\n");
	TraversareInordine(root);

	int h = inaltimeABC(root);
	printf("\nInaltime arbore binare de cautare: %d", h);
	
		
	printf("\n\n");


	fclose(f);
}