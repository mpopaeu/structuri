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

// stergere nod de pe pozitie specificata
// I/ --- lista dubla, pozitia (1, 2, ...., n)
// /O --- lista dubla actualizata (p, u pot fi actualizati) pe tipul de return, Student (stergere cu extragere) -- se da in lista de param de I/

//ListaDbl stergere_student_pozitie_data(ListaDbl lst, unsigned int pos, Student &s)
//{
//	if (pos > 0)
//	{
//		NodD * t = lst.p; // adresa primului nod in lista dubla
//		unsigned int counter = 1;
//
//		while (t && counter < pos)
//		{
//			t = t->next;
//			counter += 1;
//		}
//
//		if (t)
//		{
//			// exista pos in lista dubla
//			if (counter == pos)
//			{
//				// se dezaloca/sterge ultimul nod in lista dubla
//			}
//			else
//			{
//				if (counter == 1)
//				{
//					// se sterge primul nod
//					// ? daca exista un singur nod ?
//				}
//				else
//				{
//					// cazul general
//					// se sterge nodul t (lista este dubla, deci putem accesa t->prev)
//				}
//			}
//		}
//		else
//		{
//			// t a ajuns pe NULL (a fost parsata intreaga lista dubla)
//			// nu exista pozitia pos
//			;
//		}
//	}
//
//	return lst;
//}

// operatiile similare de la liste simple

// stergere studenti(noduri) din lista dubla pentru o grupa specificata
ListaDbl stergere_studenti_grupa(ListaDbl lst, char* nr_grupa)
{

}



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

	printf("Lista dubla dupa creare:\n");
	parseListDblInvers(lstStuds);

	// dezalocare lista dubla prin stergere repetata a primului nod
	while (lstStuds.p)
	{
		lstStuds = stergereStudentDbl(lstStuds);
	}

	printf("Lista dubla dupa dezalocare:\n");
	parseListDblInvers(lstStuds);

	fclose(f);

	return 0;
}