#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char *nume;
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

// extragerea studentilor (dezalocare noduri din lista dubla) dintr-o grupa specificata intr-un vector
// in - lista dubla cu studenti
// in - nr de grupa (medie student) pentru care se face filtrare studenti in lista dubla 
// out - lista dubla dupa extrageri
// out - vector de studenti extrasi din lista dubla
// out - dimensiune vector studenti extrasi din lista dubla
ListaDbl extragere_studenti_grupa(ListaDbl lst, char* nr_grupa, Student* &vStudenti, unsigned char &nr_studenti)
{
	// determinare nr studenti care indeplinesc criteriul (nr grupa specificata)
	nr_studenti = 0;
	NodD* tmp = lst.p;
	while (tmp)
	{
		if (strcmp(tmp->st->nrGrupa, nr_grupa) == 0) // student care indeplineste criteriul de filtrare
			nr_studenti += 1;

		tmp = tmp->next;
	}

	// alocare spatiu necesar pentru salvarea studentilor in vector
	vStudenti = (Student*)malloc(nr_studenti * sizeof(Student));

	// extragerea studentilor (cu dezalocare nodului aferent in lista dubla)
	unsigned char i = 0;
	tmp = lst.p;
	while (tmp)
	{
		if (strcmp(tmp->st->nrGrupa, nr_grupa) == 0)
		{
			// student identificat in tmp
			// copiere date student in vector
			vStudenti[i].id = tmp->st->id;
			vStudenti[i].nume = tmp->st->nume;
			strcpy(vStudenti[i].nrGrupa, tmp->st->nrGrupa);
			i += 1;

			// refacerea legaturilor
			NodD* tmp_pred, * tmp_succ;
			tmp_pred = tmp->prev;
			tmp_succ = tmp->next;

			if (tmp_pred && tmp_succ)
			{
				// tmp este nod interior lista dubla
				tmp_pred->next = tmp_succ;
				tmp_succ->prev = tmp_pred;
			}
			else
			{
				if (tmp_pred == NULL)
				{
					// tmp este nodul 1
					if (tmp_succ == NULL)
					{
						// tmp este si ultimul nod (unicul nod din lista dubla)
						lst.p = lst.u = NULL;
					}
					else
					{
						// lista contine cel putin 2 noduri
						tmp_succ->prev = NULL;
						lst.p = tmp_succ;
					}
				}
				else
				{
					// tmp este ultimul nod
					tmp_pred->next = NULL;
					lst.u = tmp_pred;
				}
			}

			// dezalocare nod lista dubla
			free(tmp->st); // se "rupe" partajarea de memorie heap pt nume student cu vectorul 
			free(tmp);

			tmp = tmp_succ;
		}
		else
			tmp = tmp->next;
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

	printf("Lista dubla dupa creare (invers):\n");
	parseListDblInvers(lstStuds);
	printf("\nLista dubla dupa creare (normal):\n");
	parseListDbl(lstStuds);

	Student* vStuds;
	unsigned char nrStuds;
	char nr_grupa[] = { "1051" };
	lstStuds = extragere_studenti_grupa(lstStuds, nr_grupa, vStuds, nrStuds);

	printf("\n Lista dubla dupa extragere (normal):\n");
	parseListDbl(lstStuds);
	printf("\n Lista dubla dupa extragere (invers):\n");
	parseListDblInvers(lstStuds);
	printf("\n Vector cu studenti extrasi din lista dubla:\n");
	for(unsigned char i = 0; i<nrStuds; i++)
		printf("%d %s %s\n", vStuds[i].id, vStuds[i].nume, vStuds[i].nrGrupa);

	// dezalocare lista dubla prin stergere repetata a primului nod
	while (lstStuds.p)
	{
		lstStuds = stergereStudentDbl(lstStuds);
	}

	// dezalocare vector studenti extrasi in functie de nr grupa
	for (unsigned char i = 0; i < nrStuds; i++)
		free(vStuds[i].nume);
	free(vStuds);


	printf("\nLista dubla dupa dezalocare:\n\n");
	parseListDblInvers(lstStuds);

	fclose(f);

	return 0;
}