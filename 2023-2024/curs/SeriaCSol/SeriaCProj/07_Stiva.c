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

struct NodStiva {
	struct Nod* pNodListaSimpla;
	struct NodStiva* next;
};

struct NodStiva* push(struct NodStiva* stiva, struct Nod* pNod)
{
	struct NodStiva* nou = (struct NodStiva*)malloc(sizeof(struct NodStiva));
	nou->pNodListaSimpla = pNod;
	nou->next = stiva;

	return nou;
}

struct Nod* pop(struct NodStiva** stiva)
{
	if (*stiva)
	{
		struct Nod* temp = (*stiva)->pNodListaSimpla;
		struct NodStiva* tNodStiva = *stiva;
		*stiva = (*stiva)->next;

		free(tNodStiva);

		return temp;
	}
	return NULL;
}

struct Nod* inserareLista(struct Nod* p, struct Student s) {
	struct Nod* nou;
	nou = (struct Nod*)malloc(1 * sizeof(struct Nod));

	nou->st = s;
	nou->next = p;

	return nou;
}

void parseList(struct Nod* p) {
	while (p) {
		printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie);

		p = p->next;
	}
}


void parse_list_recursiv(struct Nod* p)
{
	if (p != NULL) // p este nod curent in traversare recursiva a listei simple
	{
		parse_list_recursiv(p->next);
		printf("%d %s %5.2f\n", p->st.id, p->st.nume, p->st.medie); // prelucrare nod curent p
	}
}

void parse_list_invers_iterativ(struct Nod* p)
{
	struct NodStiva* stiva = NULL;
	struct Nod* temp = p;
	while (temp)
	{
		stiva = push(stiva, temp); // adaugare pe stiva a adresei nodului curent p
		temp = temp->next;
	}

	// parsare inversa a listei simple p prin consumul datelor de pe stiva
	while (stiva)
	{
		temp = pop(&stiva);
		printf("%d %s %5.2f\n", temp->st.id, temp->st.nume, temp->st.medie);
	}
}


struct Student stergereStudent(struct Nod** p) {
	struct Nod* tmp = *p;
	struct Student s;
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
			*p = 0;
		}
	}

	return s;
}


int main() {

	struct Nod* prim = 0; // pointer adresa nod inceput lista -> gestionare
				   // structura de date lista simpla

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";
	while (fgets(file_buf, sizeof(file_buf), f)) {
		struct Student stud; // buffer incarcare date din fisier
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
		prim = inserareLista(prim, stud);
	}

	printf("\nLista dupa creare:\n");
	parseList(prim);

	printf("\nLista simpla traversata invers prin apel functie recursiva:\n");
	parse_list_recursiv(prim);

	printf("\nLista simpla traversata invers prin salvare temporare noduri in structura de date stiva:\n");
	parse_list_invers_iterativ(prim);

	// dezalocare lista simpla
	while (prim != NULL)
	{
		struct Student new_student = stergereStudent(&prim);
		free(new_student.nume);
	}

	printf("\nLista simpla dupa dezalocare:\n");
	parseList(prim);

	fclose(f);

	return 0;
}