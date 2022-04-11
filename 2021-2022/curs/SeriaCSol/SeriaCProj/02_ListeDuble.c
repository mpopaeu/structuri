#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128


struct Student {
	int id;
	char* nume;
	float medie; // data derivata
};

struct NodD {
	struct Student* st;
	struct NodD* next, * prev;
};

struct ListaDbl {
	struct NodD* p, * u;
};

struct ListaDbl inserareListaDubla(struct ListaDbl lstD, struct Student* pStd) {
	struct NodD* nou;
	nou = (struct NodD*)malloc(sizeof(struct NodD));
	nou->st = pStd;
	nou->next = 0;
	nou->prev = lstD.u;

	if (!lstD.p) // lista dubla empty
		lstD.p = lstD.u = nou;
	else { // exista cel putin 1 nod in LD
		lstD.u->next = nou; // sfarsit curent de LD va avea succesor pe nou
		lstD.u = nou; // actualizare sfarsit de lista
	}

	return lstD;

}

void main()
{
	struct ListaDbl lstStuds;
	lstStuds.p = lstStuds.u = 0; // NULL

	struct Student* pStud;

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";

	// fseek(f, 0, 0); // SEEK_SET

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		pStud = (struct Student*)malloc(sizeof(struct Student));
		pStud->id = atoi(token);

		token = strtok(NULL, sep_list);
		pStud->nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(pStud->nume, token);

		token = strtok(NULL, sep_list);
		pStud->medie = atof(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		lstStuds = inserareListaDubla(lstStuds, pStud);
	}

	pStud = NULL;

	fclose(f);
}