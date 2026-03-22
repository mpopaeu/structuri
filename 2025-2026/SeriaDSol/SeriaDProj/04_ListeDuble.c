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

	if (!lstD.p)
		lstD.p = lstD.u = nou; // inserare prim nod in lista dubla; prim este ultim si nod unic in lista dubla
	else {
		lstD.u->next = nou; // ultimul nod curent are succesor pe noul nod; inserare la sfarsit
		lstD.u = nou; // actualizare sfarsit de lista dubla
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

void dezalocareLista(struct ListaDbl * lstD)
{
	while(lstD->p)
	{
		struct NodD* t = lstD->u;

		lstD->u = lstD->u->prev; // actualizare sfarsit de lista dubla

		if (lstD->u == NULL)
			lstD->p = NULL; // lista devine empty, deci ambele capete trebuie sa contina adrese nule

		// dezalocare heap pentru nodul izolat t
		free(t->st->nume); 
		free(t->st);
		free(t); // dezalocare nod lista dubla
	}
}


int main()
{
	struct ListaDbl lstStuds;
	lstStuds.p = lstStuds.u = NULL; // marcaje pentru lista duble empty

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

	dezalocareLista(&lstStuds);
	printf("\nLista dubla dupa dezalocare:\n");
	parseListDblInvers(lstStuds);

	return 0;
}