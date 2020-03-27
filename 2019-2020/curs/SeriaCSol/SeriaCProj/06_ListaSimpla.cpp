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

// structura nod LISTA SIMPLA
struct Nod {
	Student st; // Student *st;
	Nod *next;  // date de legatura cu nodul succesor
};

// structuri LISTA DUBLA
// nod lista dubla
struct NodD {
	Student *st;
	NodD *next, *prev;
};

// pachet pointeri capete de lista dubla
struct ListaDbl {
	NodD *p, *u;
};

// inserare nod la inceput in lista
Nod* inserareNodLista(Nod *p, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(1 * sizeof(Nod));

	nou->st = s;
	nou->next = p;

	return nou;
}

void parseList(Nod *p) {
	while (p) {
		printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie);

		p = p->next;
	}
}


Student stergereNodLista(Nod** p) {
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
			*p = 0;		// modificarea adresei de inceput de lista
		}
	}

	return s;
}

// functii LISTE DUBLE
ListaDbl inserareNodListaDubla(ListaDbl lstD, Student * pStd) {
	NodD * nou;
	nou = (NodD*)malloc(sizeof(NodD));
	nou->st = pStd;
	nou->next = 0; // inserare nod lista dubla la sfarsit (u)
	nou->prev = lstD.u;

	if (!lstD.p) // nu exista nici un nod in lista dubla (lstD.p == lstD.u == NULL)
		lstD.p = lstD.u = nou;
	else { // caz general - inserare nod la sfarsitul listei duble
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

		free(tmp->st->nume);
		free(tmp->st);
		free(tmp);
	}

	return lstD;
}

void main() {

	// IMPLEMENTARE LISTA SIMPLA

	Nod *prim = 0; // pointer adresa nod inceput lista -> gestionare
				   // structura de date lista simpla
				   // prim NULL inseamna ca lista este empty (nu contine nici un nod)

	Student stud; // buffer incarcare date din fisier
				  // suprascris pentru fiecare student preluat din fisier

	FILE * f;
	f = fopen("Studenti.txt", "r");

	char * token, file_buf[LINESIZE], sep_list[] = ",";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = atof(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		prim = inserareNodLista(prim, stud);

		stud.nume = NULL; // eliminare partajare adresa nume student din stud cu nume student din nod
	}	

	printf("Parsare lista dupa inserari noduri:\n");
	parseList(prim);

	// stergere nod din lista (ultimul)
	stud = stergereNodLista(&prim);
	printf("\nStudent extras: %d, %s, %f\n", stud.id, stud.nume, stud.medie);
	//dezalocare nume student
	free(stud.nume);

	printf("\nParsare lista dupa stergere nod:\n");
	parseList(prim);


	// dezalocare lista simpla (prin stergeri succesive atat timp cat exista cel putin 1 nod in lista)
	while (prim) {
		stud = stergereNodLista(&prim);
		free(stud.nume);
	}

	printf("\nParsare lista dupa dezalocare structura:\n");
	parseList(prim);

	// IMPLEMENTARE LISTA DUBLA

	ListaDbl lstStuds;
	lstStuds.p = lstStuds.u = 0; // NULL - indica lista fara noduri

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

	printf("\nLista Dubla dupa creare:\n");
	parseListDblInvers(lstStuds);

	stergereStudentDbl(lstStuds);
	printf("\nLista Dubla dupa stergere nod la inceput:\n");
	parseListDblInvers(lstStuds);

	fclose(f);
}