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
// in - lst - pachet cu 2 adrese (p, u) pt cele doua capete ale listei duble  
// in - pos - pozitia de pe care se face stergerea nodului/studentului
// out - return - lista dubla posibil actualizata pentru p si/sau u
// out - s - date student extrase din nodul care se elimina din lista dubla

ListaDbl stergere_student_pozitie_data(ListaDbl lst, unsigned int pos, Student &s)
{
	if (pos > 0)
	{
		NodD * t = lst.p; // adresa primului nod in lista dubla
		unsigned int counter = 1;

		while (t && counter < pos)
		{
			t = t->next;
			counter += 1;
		}

		if (t)
		{
			NodD* t_pred, * t_succ;
			t_pred = t->prev;
			t_succ = t->next;

			// exista pos in lista dubla (adresa nodului este in t)
			if (counter == 1)
			{
				// se sterge primul nod
				if (t_succ != NULL)
				{
					// lista contine cel putin 2 noduri
					t_succ->prev = t_pred; // t_pred este NULL; nodul 2 devine inceput de lista dubla
					lst.p = t_succ; // actualizare inceput de lista
				}
				else
				{
					// exista un singur nod in lista dubla
					lst.p = lst.u = NULL; // actualizare ambele capete ale listei
				}
			}
			else
			{
				if (t_succ == NULL)
				{
					// se dezaloca/sterge ultimul nod in lista dubla
					t_pred->next = t_succ; // t_succ este NULL
					lst.u = t_pred; // actualizare sfarsit de lista
				}
				else
				{
					// cazul general
					// se sterge nodul t (lista este dubla, deci putem accesa t->prev)
					t_pred->next = t_succ;
					t_succ->prev = t_pred;
				}
			}

			// salvare date din nodul t in s
			s.id = t->st->id;
			s.nume = t->st->nume;
			strcpy(s.nrGrupa, t->st->nrGrupa);
			
			// dezalocare nod t
			free(t->st); // dezalocare locatie Student
			free(t); // dezalocare nod lista dubla
		}
		else
		{
			// t a ajuns pe NULL (a fost parsata intreaga lista dubla)
			// nu exista pozitia pos
			s.nume = NULL; // flag pentru esec operatie de identificare nod pe pozitia pos
		}
	}

	return lst;
}

// operatiile similare de la liste simple

// stergere studenti(noduri) din lista dubla pentru o grupa specificata
ListaDbl stergere_studenti_grupa(ListaDbl lst, char* nr_grupa)
{
	NodD* tmp = lst.p;

	while (tmp)
	{
		if (strcmp(tmp->st->nrGrupa, nr_grupa) == 0)
		{
			// este identificat nodul de sters, respectiv tmp
			NodD* tmp_pred, * tmp_succ;
			tmp_pred = tmp->prev;
			tmp_succ = tmp->next;

			if (tmp_pred != NULL && tmp_succ != NULL)
			{
				// cazul general; tmp nu este nod 1 sau nod n (ultimul nod)
				tmp_pred->next = tmp_succ;
				tmp_succ->prev = tmp_pred;
			}
			else
			{
				if (tmp_pred == NULL)
				{
					if (tmp_succ == NULL)
					{
						// tmp este unicul nod in lista dubla
						lst.p = lst.u = NULL; // lista devine empty (0 noduri)
					}
					else
					{
						// tmp este primul nod in lista dubla (nodul 1)
						tmp_succ->prev = tmp_pred; // tmp_pred este NULL
						lst.p = tmp_succ;
					}
				}
				else
				{
					// tmp este ultimul nod din lista dubla (nodul n)
					tmp_pred->next = tmp_succ; // tmp_succ este NULL
					lst.u = tmp_pred;
				}
			}

			// dezalocare nod tmp
			free(tmp->st->nume); // nume student
			free(tmp->st); // locatie student
			free(tmp); // nod lista dubla

			// actualizare adresa continuta de tmp
			tmp = tmp_succ;
		}
		else
		{
			tmp = tmp->next;
		}
	}

	return lst;
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

	// stergere student/nod in functie de pozitie
	Student stud;
	lstStuds = stergere_student_pozitie_data(lstStuds, 5, stud);
	printf("\n\nLista dubla dupa stergere in functie pozitie:\n");
	parseListDblInvers(lstStuds);

	if (stud.nume != NULL)
	{
		// nodul a fost sters de pe pozitie data in lista dubla
		printf("\n\n Student identificat si extras: %d %s\n", stud.id, stud.nume);
		free(stud.nume);
	}
	else
	{
		// operatia de stergere de pe pozitie data a esuat
		printf("\n\n Studentul nu a fost identificat si extras de pe pozitia specificata.\n");
	}

	// stergere studenti/noduri in functie de nr grupa
	lstStuds = stergere_studenti_grupa(lstStuds, (char*)"1053");
	printf("\n\nLista dubla dupa stergere in functie de nr grupa:\n");
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