#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodD {
	Student *st; // adresa locatie de tip Student
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

	if (!lstD.p) // nu exista nici un nod in lista dubla (empty)
		lstD.p = lstD.u = nou; // lista dubla empty
	else { // exista cel putin un nod in lista dubla
		lstD.u->next = nou;
		lstD.u = nou;
	}

	return lstD;
}

void parseListDblInvers(ListaDbl lstD) {
	NodD *tmp = lstD.u;
	while (tmp) {
		printf("%d %s %s\n", tmp->st->id, tmp->st->nume, tmp->st->nrGrupa);

		tmp = tmp->prev; // se rescrie locatia de stack seg a var locale tmp
	}
}

void parseListDbl(ListaDbl lstD) {
	NodD *tmp = lstD.p;
	while (tmp) {
		printf("%d %s %s\n", tmp->st->id, tmp->st->nume, tmp->st->nrGrupa);

		tmp = tmp->next; // se rescrie locatia de stack seg a var locale tmp
	}
}

ListaDbl stergereStudentDbl(ListaDbl lstD) { // stergere primul nod din lista dubla (fara salvare/extragere student)
	NodD * tmp = lstD.p;

	if (tmp) { // exista cel putin un nod in lista dubla
		lstD.p = lstD.p->next;
		if (lstD.p)
			lstD.p->prev = 0;
		else {
			// exista un singur nod in lista
			lstD.u = 0;
		}

		free(tmp->st->nume); // dezalocare nume student (nivel 3 de indirectare)
		free(tmp->st);		// dezalocare locatie de tip Student (nivel 2 de indirectare)
		free(tmp);			// dealocare nod lista dubla (nivel 1 de indirectare)
	}

	return lstD;
}

// interschimbarea primului nod cu ultimul nod
// cu modificarea ordinii de acces la noduri (modificare adrese de legatura)
// in - lista dubla in care se efectueaza interschimb
// out - lista dubla cu ordinea de acces la noduri modificata (p devine u, u devine p)
// ?? - cazuri paticulare (nr noduri < 2)
ListaDbl interschimbare_1N(ListaDbl lst)
{

}

// concatenare/deconcatenare
// interschimb noduri adiacente/oarecare ---> algo de sortare
// QuickSort --> stiva/stive

int main()
{
	ListaDbl lstStuds; // variabila locala
	lstStuds.p = lstStuds.u = 0; // lista dubla empty

	Student* pStud;

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",\n";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		pStud = (Student*)malloc(sizeof(Student));
		pStud->id = atoi(token);

		token = strtok(NULL, sep_list);
		pStud->nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(pStud->nume, token);

		token = strtok(NULL, sep_list);
		strcpy(pStud->nrGrupa, token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");


		// inserare nod la inceputul listei
		lstStuds = inserareListaDubla(lstStuds, pStud);
	}

	printf("\nLista dubla dupa creare (invers):\n");
	parseListDblInvers(lstStuds);
	printf("\nLista dubla dupa creare (normal):\n");
	parseListDbl(lstStuds);

	// interschimbare primul cu ultimul nod in lista dubla
	lstStuds = interschimbare_1N(lstStuds);

	printf("\nLista dubla dupa interschimbare (invers):\n");
	parseListDblInvers(lstStuds);
	printf("\nLista dubla dupa interschimbare (normal):\n");
	parseListDbl(lstStuds);

	// dezalocare lista dubla prin stergere repetata a primului nod
	while (lstStuds.p)
	{
		lstStuds = stergereStudentDbl(lstStuds);
	}

	printf("\nLista dubla dupa dezalocare:\n\n");
	parseListDblInvers(lstStuds);

	fclose(f);

	return 0;
}