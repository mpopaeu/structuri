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
	nou->next = 0; // NULL
	nou->prev = lstD.u;

	if (!lstD.p) // lista este empty
		lstD.p = lstD.u = nou;
	else { // lista contine cel putin 1 nod
		lstD.u->next = nou;
		lstD.u = nou;
	}

	return lstD;

}

void parseListDblInvers(ListaDbl lstD) {
	NodD *tmp = lstD.u; // tmp var locala in frame de stack seg aferent functiei parseListDblInvers
	while (tmp) {
		printf("%d %s %5.2f\n", tmp->st->id, tmp->st->nume, tmp->st->medie);

		tmp = tmp->prev;
	}
}

ListaDbl stergereStudentDbl(ListaDbl lstD) {
	NodD * tmp = lstD.p; // stergere nod la inceputul listei duble (fara extragere date Student)

	if (tmp) { // exista cel putin un nod in lista dubla
		lstD.p = lstD.p->next; // p "mutat" pe nodul 2
		if (lstD.p) // lista are cel putin 2 noduri inainte de stergere
			lstD.p->prev = 0;
		else {
			// exista un singur nod in lista dubla inainte de stergere
			lstD.u = 0; // NULL - lista devine empty dupa stergerea unicului nod
		}

		free(tmp->st->nume); // dezalocare extensie nume student
		free(tmp->st);		// dezalocare structura Student
		free(tmp);			// dezalocare nod lista dubla
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

	while (fgets(file_buf, sizeof(file_buf), f)) {
		//token = strtok(file_buf, sep_list);
		pStud = (Student*)malloc(sizeof(Student));
		//pStud->id = atoi(token);

		//token = strtok(NULL, sep_list);
		//pStud->nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		// strcpy(pStud->nume, token);

		//token = strtok(NULL, sep_list);
		//pStud->medie = atof(token);

		//token = strtok(NULL, sep_list);
		//if (token)
		//	printf("\nEroare preluare token!");
		char nume[30];
		sscanf(file_buf, "%d,%[^,],%f\n", &pStud->id, nume, &pStud->medie);

		// inserare nod la inceputul listei
		lstStuds = inserareListaDubla(lstStuds, pStud);
	}

	printf("Lista dubla dupa creare:\n");
	parseListDblInvers(lstStuds);

	// dezalocare lista dubla
	while (lstStuds.p)
	{
		lstStuds = stergereStudentDbl(lstStuds);
	}
	printf("Lista dubla dupa dezalocare:\n");
	parseListDblInvers(lstStuds);

	return 0;
}