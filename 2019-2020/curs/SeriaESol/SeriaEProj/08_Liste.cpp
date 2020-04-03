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

////// LISTA SIMPLA

struct Nod {
	Student st; // Student *st; // datele de prelucrat
	Nod *next; // info de legatura
};

Nod* inserareNodLista(Nod *p, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(1 * sizeof(Nod));

	nou->st = s; // copiere byte cu byte a structurii Student in nou->st
	nou->next = p;

	return nou;
}

void parseList(Nod *p) { // pointerul p este trimis prin valoare
	while (p) {
		printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie);

		p = p->next; // modificarea lui p este locala
	}
}

Student stergereNodStudent(Nod** p) {
	Nod * tmp = *p;
	Student s;
	if (tmp) {
		if (tmp->next) { //  cel putin doua noduri in lista
			while (tmp->next->next)
				tmp = tmp->next;
			s = tmp->next->st;  // salvare student in var locala s

			free(tmp->next);  // dezalocare nod lista simpla
			tmp->next = 0; // actualizare adresa legatura 
		}
		else {  // caz particular; un singur nod in lista
			s = tmp->st;  // salvare student din cap lista

			free(tmp);  // dezalocare cap de lista
			*p = 0; // actualizare inceput de lista
		}
	}

	return s;
}

////// LISTA DUBLA
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

	if (!lstD.p) // lista nu contine nici un nod
		lstD.p = lstD.u = nou;
	else {
		lstD.u->next = nou;
		lstD.u = nou;
	}

	return lstD;
}


void parseListDblInvers(ListaDbl lstD) {
	NodD *tmp = lstD.u;
	while (tmp) {
		printf("%d %s %5.2f\n", tmp->st->id, tmp->st->nume, tmp->st->medie);

		tmp = tmp->prev;
	}
}


ListaDbl stergereStudentDbl(ListaDbl lstD) {
	NodD * tmp = lstD.p;

	if (tmp) { // exista cel putin un nod in lista dubla
		lstD.p = lstD.p->next;
		if (lstD.p)
			lstD.p->prev = 0;
		else {
			// exista un singur nod in lista
			lstD.u = 0;
		}

		free(tmp->st->nume); // dezalocare nume student
		free(tmp->st);		// dezalocare student
		free(tmp);		// dezalocare nod lista dubla
	}

	return lstD;
}
void main() {

	////// LISTA SIMPLA

	Nod *prim = 0; // pointer adresa nod inceput lista -> gestionare
				   // structura de date lista simpla

	Student stud; // buffer incarcare date din fisier
				  // suprascris pentru fiecare student preluat din fisier

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token); // conversie a string-ului token la int-ul stud.id

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = atof(token); // conversie a string-ului token la float-ul stud.medie

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		prim = inserareNodLista(prim, stud);
		
		stud.nume = NULL; // eliminare partajare stud.nume cu prim->st.nume
	}
	
	printf("Lista dupa creare:\n");
	parseList(prim);


	stud = stergereNodStudent(&prim);
	printf("Lista dupa stergere nod:\n");
	parseList(prim);

	// dezalocare nume student intors de functia de stergere
	free(stud.nume);

	// dezalocare listei simple (in intregime)
	while (prim != NULL) {
		stud = stergereNodStudent(&prim);
		free(stud.nume);
	}

	printf("Lista dupa stergere lista simpla:\n");
	parseList(prim);

	////// LISTA DUBLA
	ListaDbl lstStuds;
	lstStuds.p = lstStuds.u = 0;

	Student* pStud;

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

	printf("\n\nLista dubla dupa creare:\n");
	parseListDblInvers(lstStuds);

	lstStuds = stergereStudentDbl(lstStuds);
	printf("\nLista dubla dupa stergere nod:\n");
	parseListDblInvers(lstStuds);

	//dezalocare lista dubla
	while (lstStuds.p != NULL) {
		lstStuds = stergereStudentDbl(lstStuds);
	}
	printf("\n\nLista dubla dupa dezalocare:\n");
	parseListDblInvers(lstStuds);

	fclose(f);
}