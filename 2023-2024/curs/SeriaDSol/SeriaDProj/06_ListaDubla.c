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
	nou->next = 0; // nou->next = NULL;
	nou->prev = lstD.u;

	if (!lstD.p)
		lstD.p = lstD.u = nou;
	else {
		lstD.u->next = nou;
		lstD.u = nou;
	}

	return lstD;

}

void parseListDblInvers(struct ListaDbl lstD) {
	struct NodD* tmp = lstD.u;
	while (tmp != NULL) {
		printf("%d %s %5.2f\n", tmp->st->id, tmp->st->nume, tmp->st->medie);

		tmp = tmp->prev;
	}
}

struct ListaDbl stergereStudentDbl(struct ListaDbl lstD) {
	struct NodD* tmp = lstD.p;

	if (tmp) { // exista cel putin un nod in lista dubla
		lstD.p = lstD.p->next;
		// tmp = lstD.p->prev; // doar daca exista lstD.p != NULL
		if (lstD.p)
			lstD.p->prev = 0;
		else {
			// exista un singur nod in lista
			lstD.u = 0;
		}

		free(tmp->st->nume);
		free(tmp->st);
		free(tmp);
	}

	return lstD;
}


int main()
{
	struct ListaDbl lstStuds;
	lstStuds.p = lstStuds.u = 0;

	struct Student* pStud;

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";

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

	printf("\nLista dubla dupa creare:\n");
	parseListDblInvers(lstStuds);

	lstStuds = stergereStudentDbl(lstStuds);
	printf("\nLista dubla dupa stergere nod:\n");
	parseListDblInvers(lstStuds);

	while (lstStuds.p)
	{
		lstStuds = stergereStudentDbl(lstStuds);
	}
	printf("\nLista dubla dupa dezalocare noduri:\n");
	parseListDblInvers(lstStuds);

	fclose(f);

	return 0;
}
