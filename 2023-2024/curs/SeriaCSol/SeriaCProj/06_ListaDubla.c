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

typedef struct Nod Nod;
typedef struct Student Student;
typedef struct ListaDbl ListaDbl;

struct ListaDbl inserareListaDubla(ListaDbl lstD, Student* pStd) {
	struct NodD* nou;
	nou = (struct NodD*)malloc(sizeof(struct NodD));
	nou->st = pStd;
	nou->next = 0; // NULL
	nou->prev = lstD.u;

	if (!lstD.p)
		lstD.p = lstD.u = nou;
	else {
		lstD.u->next = nou;
		lstD.u = nou;
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


struct ListaDbl stergereStudentDbl(struct ListaDbl lstD) {
	struct NodD* tmp = lstD.p;

	if (tmp) { // exista cel putin un nod in lista dubla
		lstD.p = lstD.p->next;
		if (lstD.p)
			lstD.p->prev = 0; // NULL
		else {
			// exista un singur nod in lista
			lstD.u = 0; // NULL
		}

		free(tmp->st->nume); // dezalore nume student
		free(tmp->st);		 // dezalocare structura Student
		free(tmp); // dezalocare nod propriu-zis
	}

	return lstD;
}


int main()
{
	FILE* f;
	f = fopen("Studenti.txt", "r");
	ListaDbl lstStuds;
	lstStuds.p = lstStuds.u = 0;


	char* token, file_buf[LINESIZE], sep_list[] = ",\n";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		struct Student stud; // buffer incarcare date din fisier
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = (float)atof(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		Student* pstudent = (Student*)malloc(sizeof(Student));
		*pstudent = stud;

		// inserare nod in lista dubla 
		lstStuds = inserareListaDubla(lstStuds, pstudent);
	}

	printf("Lista dubla dupa creare (parsare inversa ultim->prim):\n");
	parseListDblInvers(lstStuds);

	lstStuds = stergereStudentDbl(lstStuds);
	printf("Lista dubla dupa dezalocare nod in lista dubla (parsare inversa ultim->prim):\n");
	parseListDblInvers(lstStuds);

	//dezalocare lista dubla
	while (lstStuds.p != NULL)
	{
		lstStuds = stergereStudentDbl(lstStuds);
	}
	printf("Lista dubla dupa dezalocare structura lista dubla (parsare inversa ultim->prim):\n");
	parseListDblInvers(lstStuds);

	fclose(f);

	return 0;
}