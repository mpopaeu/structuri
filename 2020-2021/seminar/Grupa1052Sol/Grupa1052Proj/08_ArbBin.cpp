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
NodABC* inserare(NodABC* r, Student st, int& er)
{
	if (r == NULL) {
		NodABC* nou = new NodABC;
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
		// exista nod curent si se poate calcula inaltime de subarbore cu radacina r
		return 1 + max(inaltime(r->st), inaltime(r->dr));
	}
	else
	{
		return 0; // pozitie de NULL in arbore; nu are inaltime
	}
}

// dezalocare arbore binar de cautare
NodABC* dezalocare_arbore(NodABC* r)
{
	if (r) {
		r->st = dezalocare_arbore(r->st);
		r->dr = dezalocare_arbore(r->dr);
		
		printf("Student %d dezalocat din arbore:\n", r->s.id);
		free(r->s.nume);
		free(r);
		r = NULL;
	}

	return r;
}

// numar de noduri pe nivel specificat
int nr_noduri_nivel(NodABC* r, unsigned char nivel)
{
	if (r)
	{
		if (nivel == 1) // 1 deoarece indexarea nivelurilor este de tipul 1, 2, 3, ... (nr salturi in arbore = nivel - 1)
			return 1; // r este pe nivel specificat
		else
		{
			if (nivel > 1)
			{
				return 0 + nr_noduri_nivel(r->st, nivel - 1) + nr_noduri_nivel(r->dr, nivel - 1); // 0 deoarece r nu indeplineste conditia de a fi pe nivel specificat
			}
		}
	}

	return 0; // 0 pentru pozitiile de NULL identificate deasupra nivelului specificat
}

// stergere nod din arbore binar de cautare

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
			printf("\nStudentul cu id %d exista in arbore.", stud.id);
			free(stud.nume);
		}
		else
			printf("\nStudentul %s a fost inserat\n", stud.nume);
	}

	// traversare in inordine (ordine crescatoare id-uri studenti)
	printf("\nTraversare arbore inordine:\n");
	TraversareInordine(root);

	int h = inaltime(root);
	printf("Inaltime arbore binar de cautare: %d\n\n", h);

	int nr = nr_noduri_nivel(root, 50);
	printf("Nr noduri pe nivel specificat: %d\n\n", nr);

	// dezalocare arbore binar de cautare
	root = dezalocare_arbore(root);
	printf("\nTraversare arbore inordine dupa dezalocare:\n");
	TraversareInordine(root);

	fclose(f);
}



