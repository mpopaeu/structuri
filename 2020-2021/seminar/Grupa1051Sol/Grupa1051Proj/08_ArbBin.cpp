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


void TraversareInordine(NodABC* r)
{
	if (r) {
		TraversareInordine(r->st); // prelucrare noduri din subarbore stanga
		printf("%d %s\n", r->s.id, r->s.nume); // prelucrare nod curent r
		TraversareInordine(r->dr); // prelucrare noduri din subarbore dreapta
	}
}

int max(int x, int y)
{
	return x > y ? x : y;
}

// determinare inaltime (sub)arbore
int inaltime(NodABC* r)
{
	if (r)
	{
		return 1 + max(inaltime(r->st), inaltime(r->dr));
	}

	return 0;
}

NodABC* dezalocare_arbore(NodABC* r)
{
	if (r)
	{
		r->st = dezalocare_arbore(r->st); // se prelucreaza/dezaloca nodurile din subarborele stanga
		r->dr = dezalocare_arbore(r->dr); // se prelucreaza/dezaloca nodurile din subarborele dreapta

		// prelucrare/dezalocare nod curent r
		free(r->s.nume);
		free(r);
		r = NULL;
	}

	return r; 
}

int nr_noduri_nivel(NodABC* r, unsigned char nivel)
{
	if (r)
	{
		if (nivel == 1)
			return 1;
		else
		{
			if (nivel > 1)
			{
				// 0 pt ca nodul curent r nu se afla pe nivelul specificat
				return 0 + nr_noduri_nivel(r->st, nivel - 1) + nr_noduri_nivel(r->dr, nivel - 1);
			}
		}
	}

	return 0; // nu exista nod pe nivelul specificat
}

// extragere nod din ABC


// creare ABC cu studenti inscrisi in grupa specificata din ABC existent
// cele doua structuri NU partajeaza zone de heap
// [in] r - arbore existent
// [in] nr_grupa - numar grupa utilizat la filtrarea studentilor/nodurilor din r
// return - ABC nr. 2 (adresa radacina ABC cu studenti din aceeasi grupa specificata de nr_grupa)

NodABC* creare_abc_grupa_studenti(NodABC* r, char* nr_grupa, NodABC* newTree)
{
	if (r)
	{
		// prelucrare nod curent
		if (strcmp(r->s.nrGrupa, nr_grupa) == 0)
		{
			Student s;
			s.id = r->s.id;
			s.nume = (char*)malloc((strlen(r->s.nume) + 1) * sizeof(char));
			strcpy(s.nume, r->s.nume);
			strcpy(s.nrGrupa, r->s.nrGrupa);
			int err;
			newTree = inserare(newTree, s, err);
		}

		newTree = creare_abc_grupa_studenti(r->st, nr_grupa, newTree);
		newTree = creare_abc_grupa_studenti(r->dr, nr_grupa, newTree);
	}

	return newTree;
}

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

	int h = inaltime(root);
	printf("Inaltime arbore este %d.\n", h);

	int nr = nr_noduri_nivel(root, 1);
	for (int i = 1; i <= h; i++)
	{
		int nr = nr_noduri_nivel(root, i);
		printf("Nr noduri pe nivel specificat %d este %d.\n", i, nr);
	}

	NodABC* newTree = NULL;
	newTree = creare_abc_grupa_studenti(root, (char*)"1051", newTree);
	printf("\nTraversare arbore cu studenti filtrati pe grupa:\n");
	TraversareInordine(newTree);

	// dezalocare structura arbore binar de cautare
	root = dezalocare_arbore(root);
	printf("\nTraversare arbore dupa dezalocare:\n\n");
	TraversareInordine(root);

	fclose(f);
}



