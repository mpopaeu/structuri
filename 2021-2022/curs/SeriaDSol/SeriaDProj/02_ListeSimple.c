#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	float medie; // data derivata
};

struct Nod {
	struct Student st; // Student *st;
	struct Nod* next;
};

struct Nod* inserareLista(struct Nod* p, struct Student s) {
	struct Nod* nou;
	nou = (struct Nod*)malloc(1 * sizeof(struct Nod));

	nou->st = s;
	nou->next = p;

	return nou;
}

void main() {

	struct Nod* prim = 0; // pointer adresa nod inceput lista -> gestionare
				   // structura de date lista simpla

	struct Student stud; // buffer incarcare date din fisier
				  // suprascris pentru fiecare student preluat din fisier

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token); // conversie ascii-to-binary(integer)

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = atof(token); // conversie ascii-to-binary(float)

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		prim = inserareLista(prim, stud);
	}

	stud.nume = NULL;
		
	
	fclose(f);
}