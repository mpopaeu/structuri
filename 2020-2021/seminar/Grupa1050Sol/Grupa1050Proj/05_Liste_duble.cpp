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
	nou->next = 0; // NULL
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

ListaDbl stergereStudentDbl(ListaDbl lstD) { // stergere primul nod din lista dubla (fara salvare/extragere student)
	NodD * tmp = lstD.p;

	if (tmp) { // exista cel putin un nod in lista dubla
		lstD.p = lstD.p->next;
		if (lstD.p)
			lstD.p->prev = 0; // predecesor primul nod este NULL
		else {
			// exista un singur nod in lista
			lstD.u = 0; // NULL
		}

		free(tmp->st->nume); // dezalocare nume student (nivel 3 de indirectare)
		free(tmp->st);		// dezalocare locatie de tip Student (nivel 2 de indirectare)
		free(tmp);			// dealocare nod lista dubla (nivel 1 de indirectare)
	}

	return lstD;
}


// inserare Student/nod/element in lista dubla pe pozitie specificata
// I/ --> lista dubla, adresa de Student, pizitie de inserat
// /O --> lista dubla cu nod adaugat
// !!! cazuri particulare
ListaDbl inserareListaDubla_pozitie(ListaDbl lstD, Student * pStd, int pozitie)
{

}

int main()
{
	ListaDbl lstStuds; // variabila locala
	lstStuds.p = lstStuds.u = 0; // NULL; lista dubla empty

	Student* pStud;

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";

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

		//pStud = (Student*)malloc(sizeof(Student));
		//char nume_temp[100];
		//sscanf(file_buf, "%d,%[^,],%s\n", &pStud->id, nume_temp, &pStud->nrGrupa);
		//pStud->nume = (char*)malloc((strlen(nume_temp) + 1) * sizeof(char));
		//strcpy(pStud->nume, nume_temp);

		// inserare nod la inceputul listei
		lstStuds = inserareListaDubla(lstStuds, pStud);
	}

	printf("Lista dubla dupa creare:\n");
	parseListDblInvers(lstStuds);

	// dezalocare lista dubla prin stergere repetata a primului nod
	while (lstStuds.p)
	{
		lstStuds = stergereStudentDbl(lstStuds); // fara extragere date Student
	}

	printf("Lista dubla dupa dezalocare:\n");
	parseListDblInvers(lstStuds);

	fclose(f);

	return 0;
}