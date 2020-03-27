#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

/////////////// LISTA SIMPLA
struct Student {
	int id;
	char *nume;
	float medie; // data derivata
};

struct Nod {
	Student st; // Student *st;
	Nod *next;  // info de legatura
};

Nod* inserareNodLista(Nod *p, Student s) { // inserare la inceput
	Nod* nou;
	nou = (Nod*)malloc(1 * sizeof(Nod));

	nou->st = s; // copiere structura Student byte-cu-byte in nou->st; asumare partajare mem heap nou->st.nume cu s.nume
	nou->next = p;

	return nou;
}

void parseList(Nod * p) { // traversarea/parsarea listei simple
	Nod* temp = p;
	while (temp) {
		printf("%d %s %5.2f\n", temp->st.id, temp->st.nume, temp->st.medie);

		temp = temp->next;
	}
}

void parseListRecursiv(Nod* p) {
	if (p) {
		printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie);
		parseListRecursiv(p->next);
	}
}

Student stergereNodStudent(Nod** p) {
	Nod * tmp = *p;
	Student s;
	if (tmp) {
		if (tmp->next) { //  cel putin doua noduri in lista
			while (tmp->next->next) // parsare lista pana pe penultimul nod
				tmp = tmp->next;
			s = tmp->next->st;  // salvare student in var locala s

			free(tmp->next);  // dezalocare nod lista simpla
			tmp->next = 0; // actualizare adresa legatura 
		}
		else {  // caz particular; un singur nod in lista
			s = tmp->st;  // salvare student din cap lista

			free(tmp);  // dezalocare cap de lista
			*p = 0;
		}
	}

	return s;
}

/////////////// LISTA DUBLA
struct NodD {
	Student *st;
	NodD *next, *prev;
};

struct ListaDbl {
	NodD *p, *u;
};

ListaDbl inserareNodListaDubla(ListaDbl lstD, Student * pStd) { // inserare la sfarsit in lista dubla
	NodD * nou;
	nou = (NodD*)malloc(sizeof(NodD));
	nou->st = pStd;
	nou->next = 0;
	nou->prev = lstD.u;

	if (!lstD.p) // lista dubla nu are nici un nod
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

void main() {

	/////////////// LISTA SIMPLA
	Nod *prim = 0; // pointer adresa nod inceput lista -> gestionare
				   // structura de date lista simpla

	Student stud; // buffer incarcare date din fisier
				  // suprascris pentru fiecare student preluat din fisier

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = atof(token); // conversie ASCII->Binar(float)

		token = strtok(NULL, sep_list); // verificare existenta token dupa medie in linia curenta file_buf
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		prim = inserareNodLista(prim, stud);

		stud.nume = NULL; // evitare partajare zona de memorie aferenta numelui de student
	}

	printf("Lista dupa creare:\n");
	// parseList(prim);
	parseListRecursiv(prim);

	stud = stergereNodStudent(&prim);
	printf("Studentul extras: %d, %s\n", stud.id, stud.nume);

	printf("Lista dupa stergere nod:\n");
	parseListRecursiv(prim);

	/////////////// LISTA DUBLA
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
		lstStuds = inserareNodListaDubla(lstStuds, pStud);
	}

	printf("Lista dubla dupa creare:\n");
	parseListDblInvers(lstStuds);
	
	fclose(f);
}

