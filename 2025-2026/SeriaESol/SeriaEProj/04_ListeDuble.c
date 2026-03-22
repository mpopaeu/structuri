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
	struct Student* st; // adresa de heap seg unde se afla datele studentului
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
	while (tmp) {
		printf("%d %s %5.2f\n", tmp->st->id, tmp->st->nume, tmp->st->medie);

		tmp = tmp->prev;
	}
}

struct ListaDbl dezalocareListaDubla(struct ListaDbl lstD)
{
	while (lstD.p != NULL)
	{
		struct NodD* t = lstD.p;
		lstD.p = lstD.p->next;

		free(t->st->nume); // dezalocare string nume student
		free(t->st); // dezalocare structura Student
		free(t); // dezalocare structur NodD (nod lista dubla)
	}
	lstD.u = NULL; // deoarece lstD.p a devenit NULL

	return lstD;
}

int main()
{
	struct ListaDbl lstStuds;
	lstStuds.p = lstStuds.u = NULL; // lista dubla este empty

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
		pStud->medie = (float)atof(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		lstStuds = inserareListaDubla(lstStuds, pStud);
	}
	fclose(f);

	printf("\nLista dubla dupa creare:\n");
	parseListDblInvers(lstStuds);

	lstStuds = dezalocareListaDubla(lstStuds);
	printf("\nLista dubla dupa creare:\n");
	parseListDblInvers(lstStuds);

	return 0;
}