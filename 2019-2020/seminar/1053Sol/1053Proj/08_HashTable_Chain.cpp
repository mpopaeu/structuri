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
	Student stud; // date de procesat
	Nod* next;	  // date/info de legatura/implementare relatie de ordine intre noduri
};

int functieHash(char* str, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i<strlen(str); i++)
		temp += str[i];

	poz = temp % size;

	printf("\n Suma coduri ASCII %d,  Pozitie in tabela %d ", temp, poz);

	return poz;
}

Nod* insertNodeEnd(Nod* lst, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));

	nou->stud = s; // asumata partajarea lui nume
	nou->next = NULL;
	if (lst == NULL) // lista este goala/empty
		return nou;
	else {
		// exista cel putin 1 nod in lista
		Nod* temp = lst;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = nou; // legare nodul nou la sfarsitul listei lst
	}

	return lst;
}

// parsare lista simpla
void printList(Nod* lst) {
	Nod* temp = lst;
	while (temp) {
		printf("Student %d, %s, %s\n", temp->stud.id, temp->stud.nume, temp->stud.nrGrupa);

		temp = temp->next;
	}
}

void inserareHTable(Nod* *hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = functieHash(s.nume, sizeHT);

	hTab[k] = insertNodeEnd(hTab[k], s);
}

void parseHTable(Nod* *hTab, int size) {
	for (int i = 0; i < size; i++) {
		if (hTab[i]) {
			printf("\nLista nr. %d: \n", i);
			printList(hTab[i]);
		}
	}
}

Student cautaHTable(Nod** hTab, int size, char* numeStudent) {
	int k; // pozitie probabila pentru string-ul nume
	k = functieHash(numeStudent, size);

	Nod* tmp = hTab[k];
	while (tmp) {
		if (!strcmp(tmp->stud.nume, numeStudent))
			return tmp->stud;

		tmp = tmp->next;
	}

	Student stud;
	stud.nume = NULL; // flag pentru semnalarea absentei studentului in tabela hash
	return stud;
}

// stergerea unui student din tabela hash pe baza cheii de cautare (nume student)
// ??? daca exista mai multi studenti cu acelasi nume, cum se procedeaza ???

// consolidarea mai multor tabele de dispersie cu chaining -> se creeaza tabela nr 3 care va contine studenti
// din tabelele 1 si 2; tabelele 1 si 2 se vor dezaloca dupa consolidare

void main() {

	Nod* *HTable;
	Student stud;

	// alocare spatiu tabela de dispersie
	HTable = (Nod**)malloc(sizeof(Nod*) * DIM);

	// initializare elemente tabela de dispersie
	for (int i = 0; i<DIM; i++)
		HTable[i] = 0;  // HTable[i] => elementul i in tabela hash


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
		printf(" Student %s inserat", stud.nume);

		stud.nume = NULL;
	}

	printf("\nTabela de dispersie dupa creare:\n");
	parseHTable(HTable, DIM);

	stud = cautaHTable(HTable, DIM, (char*)"Mircea Popescu");
	if (stud.nume != NULL)
		// student identificat in tabela hash
		printf("\n\n Student identificat: %d %s \n", stud.id, stud.nume);
	else
		printf("\n\n Studentul nu a fost gasit in tabela de dispersie.\n");

	fclose(f);
}