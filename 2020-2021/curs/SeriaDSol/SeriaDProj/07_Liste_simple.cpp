#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char *nume;
	float medie; // data derivata
};

struct Nod {
	Student st; // Student *st;
	Nod *next;
};

Nod* inserareLista(Nod *p, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(1 * sizeof(Nod));

	nou->st = s;
	nou->next = p;

	return nou;
}

int main()
{
	Nod *prim = NULL; // pointer adresa nod inceput lista -> gestionare
				   // structura de date lista simpla

	Student stud; // buffer incarcare date din fisier
				  // suprascris pentru fiecare student preluat din fisier

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = atof(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		prim = inserareLista(prim, stud);
	}
	
	fclose(f);

	return 0;
}