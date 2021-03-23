#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char *nume;
	float medie; // data derivata
};

struct NodD {
	Student *st;
	NodD *next, *prev;
};

struct ListaDbl {
	NodD *p, *u;
};

ListaDbl inserareListaDubla(ListaDbl lstD, Student * pStd) {
	NodD * nou;
	nou = (NodD*)malloc(sizeof(NodD));
	nou->st = pStd;
	nou->next = 0;
	nou->prev = lstD.u;

	if (!lstD.p)
		lstD.p = lstD.u = nou;
	else {
		lstD.u->next = nou;
		lstD.u = nou;
	}

	return lstD;

}

int main()
{
	ListaDbl lstStuds;
	lstStuds.p = lstStuds.u = 0;

	Student* pStud;
	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";

	fseek(f, 0, 0); // SEEK_SET

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		pStud = (Student*)malloc(sizeof(Student));
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

	return 0;
}