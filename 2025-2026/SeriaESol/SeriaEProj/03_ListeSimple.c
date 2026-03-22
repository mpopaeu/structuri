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

struct Nod* inserareLista(struct Nod* p, struct Student s) {
	struct Nod* nou;
	nou = (struct Nod*)malloc(1 * sizeof(struct Nod)); // aloca 16 bytes pentru un singur nod in heap seg

	nou->st = s; // datele studentului din parametrul s sunt copiata byte cu byte in zona st a nodului
	nou->next = p; // p este inceput curent al listei simple, deci nou va fi plasat in fata acestuia (inserare la inceput)

	return nou;
}


void parseList(struct Nod* p) {
	while (p) {
		printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie);

		p = p->next; // modificarea lui p este locala functiei si nu afecteaza argumentul in apelator
	}
}

void dezalocareLista(struct Nod* *p)
{
	while (*p != NULL)
	{
		struct Nod* t = *p;
		*p = (*p)->next;

		free(t->st.nume);
		free(t);
	}
}

int main() {

	struct Nod* prim = NULL; // pointer adresa nod inceput lista -> gestionare
				   // structura de date lista simpla

	struct Student stud; // buffer incarcare date din fisier
				  // suprascris pentru fiecare student preluat din fisier

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";
	while (fgets(file_buf, sizeof(file_buf), f)) { // preluare continut din fisierul text la nivel de linie (separator: 0x0d 0x0a ENTER)
		token = strtok(file_buf, sep_list); // identificare prim substring in file_buf pe baza listei de separatori sep_list
		// token stocheaza adresa de inceput (din file_buf) a primului substring
		stud.id = atoi(token); // conversie ASCII-to-binary (integer)

		token = strtok(NULL, sep_list); // primul argument este NULL, indicand continuarea identificarii de substring-uri pe baza de separatori
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char)); // alocare spatiu de mem heap pentru stocare string aferent numelui de student
		strcpy(stud.nume, token); // copiere nume student in mem heap alocata mai sus

		token = strtok(NULL, sep_list);
		stud.medie = (float)atof(token); // conversie ASCII-to-binary (float)

		token = strtok(NULL, sep_list); // incercare de identificare a urmatorului token de pe linia curenta salvata in file_buf
		if (token)
			printf("\nEroare preluare token!"); // nu se asteapta alte date in afara celor definite in structura Student

		// inserare nod la inceputul listei
		prim = inserareLista(prim, stud); // stud contine datele preluate din fisier si pregatite conform tipurilor utilizate la definirea structurii Student
	}
	fclose(f);

	printf("Lista simpla dupa creare:\n");
	parseList(prim); // prim se transmite prin valoare


	dezalocareLista(&prim); // prim se transmite prin adresa pentru a fi actualizat cu NULL (lista empty)
	printf("Lista simpla dupa dezalocare:\n");
	parseList(prim);

	return 0;
}