#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 100
#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct Nod {
	Student st;
	Nod* next;
};

int calculPozitie(Student s, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i < strlen(s.nume); i++)
		temp += s.nume[i];

	poz = temp % size;

	printf("%d %d   ", temp, poz);

	return poz;
}

Nod* inserareLista(Nod* p, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(1 * sizeof(Nod));

	nou->st.id = s.id;
	nou->st.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->st.nume, s.nume);
	strcpy(nou->st.nrGrupa, s.nrGrupa);

	nou->next = p;

	return nou;
}

void inserareHTable(Nod** hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = calculPozitie(s, sizeHT);

	hTab[k] = inserareLista(hTab[k], s);
}

void parseHTable(Nod** hTab, int size) {
	for (int i = 0; i < size; i++) // se parseaza intregul vector in mod secvential
		if (hTab[i]) {  // lista i contine cel putin un student
			Nod* tmp = hTab[i];
			printf("Lista no. %d:\n", i);
			while (tmp) {
				printf("%d %s\n", tmp->st.id, tmp->st.nume);
				tmp = tmp->next;
			}
		}
}

int calculPozString(char* str, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i < strlen(str); i++)
		temp += str[i];

	poz = temp % size;
	return poz;
}

Student cautaHTable(Nod** hTab, int size, char * nume_student) {
	int k; // pozitie probabila pentru string-ul nume
	k = calculPozString(nume_student, size);

	Nod* tmp = hTab[k];
	while (tmp) {

		if (!strcmp(tmp->st.nume, nume_student))
			return tmp->st;

		tmp = tmp->next;
	}

	Student s;
	s.nume = NULL; // pt cazul in care studentul nu este identificat in tabela hash
	return s;
}

// TEMA
/////
// cautare student pt o grupa specificata ---> secvential pe intreaga tabela de dispersie
// dezalocare tabelei de dispersie

int main() {

	Nod* * HTable;
	Student stud;

	// alocare spatiu tabela de dispersie
	HTable = (Nod**)malloc(sizeof(Nod*) * DIM);

	// initializare elemente tabela de dispersie
	for (int i = 0; i < DIM; i++)
		HTable[i] = NULL;  // HTable[i] => elementul i in tabela hash este adresa de inceput lista simpla


	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(stud.nrGrupa, token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare Student in Tabela Hash 
		inserareHTable(HTable, stud, DIM);
		printf("Student %s inserat \n", stud.nume);
		// dezalocare nume student
		free(stud.nume);
	}

	printf("\n\n Tabela de dispersie dupa creare (parsare secventiala):\n");
	parseHTable(HTable, DIM);

	// identificare (fara dezalocare student/nod) prim student dupa nume
	char nume_student[] = {"Vasil Marianescu"}; 
	stud = cautaHTable(HTable, DIM, nume_student);
	if(stud.nume != NULL)
		printf("\n\nStudent identificat:%d %s\n", stud.id, stud.nume);
	else
		printf("\n\nStudentul nu este prezent in tabela hash\n");

	fclose(f);

	return 0;
}