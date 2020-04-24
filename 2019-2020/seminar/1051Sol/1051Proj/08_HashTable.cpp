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
	Student stud;
	Nod* next;
};

Nod* inserareNodSfarsit(Nod* lista, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(sizeof(Nod));

	// nou->stud = s; // copiere byte cu byte a lui s peste nou->st; partajare temporara nume student ca si locatie de heap
	nou->stud.id = s.id;
	nou->stud.nume = s.nume; // partajare temporara nume student ca si locatie de heap
	strcpy(nou->stud.nrGrupa, s.nrGrupa);

	nou->next = NULL; // nou devine ultimul nod in lista simpla

	if (lista == NULL) // nu exista nici un nod in lista
		return nou;
	else {
		// lista are cel putin 1 nod
		Nod* temp = lista;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = nou; // actualizare legatura sfarsit de lista catre nodul care se insereaza
	}

	return lista;
}

int functieHash(char* str, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i<strlen(str); i++)
		temp += str[i];

	poz = temp % size;

	printf("Pozitie calculata: %d ", poz);

	return poz;
}

void inserareHTable(Nod* *hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = functieHash(s.nume, sizeHT);

	hTab[k] = inserareNodSfarsit(hTab[k], s);
}


Student cautaHTable(Nod** hTab, int size, char* numeStudent) {
	int k; // pozitie probabila pentru string-ul nume
	k = functieHash(numeStudent, size); // k - nr de lista simpla unde are trebui sa fie studentul cautat

	Nod* tmp = hTab[k];
	while (tmp) { // cautare secventiala in lista hTab[k]

		if (!strcmp(tmp->stud.nume, numeStudent))
			return tmp->stud;

		tmp = tmp->next;
	}

	Student student;
	student.nume = NULL;
	return student;
}

void parseHTable(Nod** hTab, int size) {
	for (int i = 0; i < size; i++)
		if (hTab[i]) {  // lista i contine cel putin un student
			Nod* tmp = hTab[i];
			printf("Lista no. %d:\n", i);
			while (tmp) {
				printf("%d %s\n", tmp->stud.id, tmp->stud.nume);
				tmp = tmp->next;
			}
		}
}

void stergereHTable(Nod** hTab, int size, char* numeStudent) {
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

		stud.nume = NULL;
	}

	printf("\nTabela de dispersie dupa creare:\n");
	parseHTable(HTable, DIM);

	stud = cautaHTable(HTable, DIM, (char*)"Alexandru Georgescu");
	if (stud.nume != NULL)
		// studentul exista in tabela de dispersie
		printf("\n Student identificat in tabela hash: %d %s\n", stud.id, stud.nume);
	else
		printf("\n Studentul cautat nu exista in tabela hash.\n");

	fclose(f);
}