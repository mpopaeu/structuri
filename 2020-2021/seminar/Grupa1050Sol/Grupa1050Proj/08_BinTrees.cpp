#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

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

NodABC* inserare(NodABC* r, Student st, int& er)
{
	if (r == NULL) { // locul de inserare a nodului cu datele st a fost identificat
		NodABC* nou = new NodABC;
		nou->dr = NULL;
		nou->st = NULL;
		nou->s.id = st.id;
		nou->s.nume = st.nume;
		strcpy(nou->s.nrGrupa, st.nrGrupa);
		r = nou;
	}
	else if (r->s.id == st.id) er = 1; // in arbore exista nod cu aceeasi cheie din st
	else if (r->s.id > st.id)
		r->st = inserare(r->st, st, er); // continuare cautare pozitie de inserat pe subarborele din stanga nodului curent r
	else
		r->dr = inserare(r->dr, st, er); // continuare cautare pozitie de inserat pe subarborele din dreapta nodului curent r
	return r;
}

void Inordine(NodABC* r)
{
	if (r)
	{
		Inordine(r->st); // prelucrarea tuturor nodurilor din subarborele stanga conform aceleasi reguli
		printf(" %d ", r->s.id); // prelucrare nod curent r
		Inordine(r->dr); // prelucrarea tuturor nodurilor din subarborele dreapta conform aceleasi reguli
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
// salvare noduri frunza din ABC in vector (cu stergerea nodurilor frunza)
// cu alocare prealabila a vectorului
NodABC* salveaza_frunze(NodABC* r, Student* vFrunze, unsigned char& i)
{
	if (r)
	{
		if (!r->st && !r->dr) // nodul curent r este nod frunza
		{
			vFrunze[i].id = r->s.id;
			vFrunze[i].nume = r->s.nume;
			strcpy(vFrunze[i].nrGrupa, r->s.nrGrupa);
			i += 1;

			free(r); // se dezaloca doar nodul; numele studentului este copiat in vector
			r = NULL; // pointer NULL care va rescrie in parinte->st sau parinte->dr
		}
		else {
			r->st = salveaza_frunze(r->st, vFrunze, i);
			r->dr = salveaza_frunze(r->dr, vFrunze, i);
		}
	}
	return r;
}
// cu realocarea vectorului (creare dinamica a vectorului fara determinare prealabila numar frunze)

// stergere nod in ABC

// creare vector de studenti copiati din nodurile plasate pe un nivel specificat
// [in] r - (sub)arbore binar de cautare
// [in] nivel - nivelul de pe care se copiaza studentii
// [out] n - numarul de studenti copiati (dim vector de studenti)
// return - vector de studenti copiati de pe nivelul nivel din arbore binar de cautare
Student* vector_studenti_nivel(NodABC* r, unsigned char nivel, int &n)
{

}

int main()
{
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

	printf(" Arborele dupa creare: ");
	Inordine(root);
	printf("\n\n");

	printf("Inaltime arbore: %d niveluri\n\n", Inaltime(root));

	fclose(f);

	return 0;
}