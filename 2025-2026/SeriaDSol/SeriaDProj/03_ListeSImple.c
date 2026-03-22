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

struct Nod {
	struct Student st; // Student *st;
	struct Nod* next;
};

struct Nod* inserareNodLista(struct Nod* p, struct Student s) {
	struct Nod* nou;
	nou = (struct Nod*)malloc(1 * sizeof(struct Nod));

	nou->st = s;
	nou->next = p; // nou nod este legat de lista prin scrierea adresei de inceput a acesteia in campul next; deci inserarea noului nod are loc pe prima pozitie

	return nou; // functia actualizeaza inceputul listei simple dupa fiecare apel
}


void parseList(struct Nod* p) {
	while (p) {
		printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie);

		p = p->next;
	}
}

void dezalocareLista(struct Nod * *p)
{
	if (*p)
	{
		// exista cel putin 1 nod in lista simpla
		struct Nod* t;
		while (*p)
		{
			t = *p;
			// inceputul de lista mutat pe nodul #2
			*p = (*p)->next;

			// dezalocare nod t
			free(t->st.nume); // dezalore heap seg pentru nume student
			free(t); // dezalocare nod t
		}
	}
	
}

int main() {

	struct Nod* prim = NULL; // pointer adresa nod inceput lista -> gestionare
				   // structura de date lista simpla

	struct Student stud; // buffer incarcare date din fisier
				  // suprascris pentru fiecare student preluat din fisier

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char *token, file_buf[LINESIZE], sep_list[] = ",\n"; // "\n" pentru LF; LF nu va fi in continutul ultimul token identificat in file_buf
	while (fgets(file_buf, sizeof(file_buf), f)) { // scrie in file_buf continutul unei linii din fisier Studenti.txt, inclusiv byte 0x0a (LF in tabela ASCII)
		token = strtok(file_buf, sep_list); // incepe traversare file_buf si identifica primul token (in ASCII)
		stud.id = atoi(token); // conversie token (ASCII) la intreg

		token = strtok(NULL, sep_list); // argument NULL pentru a continua identificarea noului token incepand cu pozitia ultimului separator identificat in file_buf
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char)); // +1 pentru byte 0x00 (terminator de string)
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = (float)atof(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare nod la inceputul listei
		prim = inserareNodLista(prim, stud); // date pregatite in variabila locala stud, conform tipurilor de date definite in structura Student
	}

	printf("Continut lista simpla dupa creare:\n");
	parseList(prim);

	dezalocareLista(&prim);
	printf("Continut lista simpla dupa dezalocare noduri:\n");
	parseList(prim);

	fclose(f);
	return 0;
}