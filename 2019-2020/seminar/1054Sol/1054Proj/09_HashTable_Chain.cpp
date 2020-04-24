#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128
#define DIM 100

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct Nod {
	Student stud; // date propriu-zise
	Nod* next; // date de legatura (relatie de ordine pe elemente de tip Nod)
};

// inserare nod cu Student la sfarsitul unei liste simple
Nod* inserareSfarsitLista(Nod* p, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod)); // alocare nod nou
									 // nou->stud = s; // copiere inclusiv nrGrupa !!!
	nou->stud.id = s.id;
	nou->stud.nume = s.nume; // asumare s.nume va fi copiat peste nou->nume
	strcpy(nou->stud.nrGrupa, s.nrGrupa);
	nou->next = NULL;

	if (p == NULL) // lista nu contine nici un nod/element
		return nou;
	else {
		// parsare lista pana pe ultimul element
		Nod* temp = p;
		while (temp->next != NULL)
			temp = temp->next;
		// conectare ultimul nod din lista la nodul nou
		temp->next = nou;
	}

	return p;
}

// stergere nod din lista (la inceput, fara extragere de date-Student)
Nod* stergereNodInceput(Nod* lst) {
	Nod * temp = lst;

	if (lst) {
		lst = lst->next; // actualizare nod de inceput lista

		free(temp->stud.nume); // dezalocare mem heap pt nume student
		free(temp);			// dezalocare mem heap pt nod din lista
	}

	return lst;
}

// stergere nod din lista (pe baza nume student)
// se vor sterge toti studentii cu acelasi nume
Nod* stergereNodNumeStudent(Nod* lst, char *numeStud) {
	Nod * temp = lst;

	if (lst != NULL) {
		// actualizare stergere la inceput cu parsarea lista in intregime
		// pt situatia in care exista mai multi studenti cu acelasi nume in lista
		if (strcmp(lst->stud.nume, numeStud) == 0) {
			// studentul este identificat in primul nod din lista
			lst = lst->next; // actualizare inceput de lista
			free(temp->stud.nume); // dezalocare nume student
			free(temp); // dezalocare nod din lista
		}
		// else {
			// cautare nod de sters prin testarea sa din predecesor (temp)
			while (temp->next) {
				Nod* q = temp->next;
				if (strcmp(q->stud.nume, numeStud) == 0) {
					// q este nodul de sters, temp este predecesor lui q
					temp->next = q->next; // izolare q fata de lista 
					free(q->stud.nume);
					free(q);
				}
				else
					temp = temp->next;
			}
		// }
	}

	return lst;
}

// implementare functi hash (nume student: cheie de cautare)
int functieHash(char* str, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i < strlen(str); i++)
		temp += str[i];

	poz = temp % size;

	printf("%d %d   ", temp, poz);

	return poz;
}

// inserare student in tabela de dispesie (chaining)
void inserareHTable(Nod** hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = functieHash(s.nume, sizeHT);

	hTab[k] = inserareSfarsitLista(hTab[k], s);
}

// parsare tabela de dispersie (in intregime, secvential)
void parseHTable(Nod** hTab, int size) {
	for (int i = 0; i<size; i++)
		if (hTab[i]) {  // lista i contine cel putin un student
			Nod* tmp = hTab[i];
			printf("Lista no. %d:\n", i);
			while (tmp) {
				printf("%d %s\n", tmp->stud.id, tmp->stud.nume);
				tmp = tmp->next;
			}
		}
}

// cautare student in tabela hash dupa cheia de cautare (nume student)
// functia intoarce student (gasit->nume nu este NULL; neidentificat in tabela hash->nume este NULL)
Student cautaHTable(Nod** hTab, int size, char* numeStud) {
	int k; // pozitie probabila pentru string-ul nume
	k = functieHash(numeStud, size);

	Nod* tmp = hTab[k];
	while (tmp) {
		if (!strcmp(tmp->stud.nume, numeStud))
			return tmp->stud;

		tmp = tmp->next;
	}

	Student retStud;
	retStud.nume = NULL;
	return retStud;
}

// stergere unui student din tabela hash
// functia intoarce 1 (studentul exista in tabela) pentru succes, 0 pentru esec (studentul nu a fost identificat)
char stergereHTable(Nod** hTab, int size, char* numeStud) {

}

void main() {

	Nod* *HTable;
	Student stud;

	// alocare spatiu tabela de dispersie
	HTable = (Nod**)malloc(sizeof(Nod*) * DIM);

	// initializare elemente tabela de dispersie
	for (int i = 0; i < DIM; i++)
		HTable[i] = NULL;  // HTable[i] => elementul i in tabela hash


	FILE * f;
	f = fopen("Studenti.txt", "r");
	char studBuff[20];

	char * token, file_buf[LINESIZE], sep_list[] = ",";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(stud.nrGrupa, token);

		//token = strtok(NULL, sep_list);
		//if (token)
		//	printf("\nEroare preluare token!");

		// inserare Student in Tabela Hash 
		inserareHTable(HTable, stud, DIM);
		printf("Student %s inserat \n", stud.nume);

		stud.nume = NULL; // evitare partajare zona heap pentru nume student
	}

	// afisare in consola continut tabela dispersie
	printf("\n Tabela de dispersie:\n");
	parseHTable(HTable, DIM);

	// cautare student dupa cheie de cautare (nume student)
	stud = cautaHTable(HTable, DIM, (char*)"Popescu Marian");
	if (stud.nume != NULL)
		// studentul a fost identificat
		printf("\n\n Student identificat: %d %s %s\n", stud.id, stud.nume, stud.nrGrupa);
	else
		printf("\n\nStudentul nu exista in tabela hash.\n");

	fclose(f);
}