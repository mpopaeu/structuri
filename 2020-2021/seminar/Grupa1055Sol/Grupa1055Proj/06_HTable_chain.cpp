#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 100
#define LINESIZE 128

struct Student {
	int id;
	char *nume;
	char nrGrupa[5];
};

struct Nod {
	Student st;
	Nod *next;
};

Nod* inserareLista(Nod *p, Student s) {
	Nod* nou;
	nou = (Nod*)malloc(1 * sizeof(Nod));

	nou->st.id = s.id;
	nou->st.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->st.nume, s.nume);
	strcpy(nou->st.nrGrupa, s.nrGrupa);

	nou->next = p;

	return nou;
}

int calculPozitie(Student s, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i<strlen(s.nume); i++)
		temp += s.nume[i];

	poz = temp % size;

	printf("%d %d   ", temp, poz);

	return poz;
}

int calculPozitie_string(char* nume, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i<strlen(nume); i++)
		temp += nume[i];

	poz = temp % size;

	return poz;
}

void inserareHTable(Nod** hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = calculPozitie(s, sizeHT); // implementare functie hash in calculPozitie

	hTab[k] = inserareLista(hTab[k], s);
}

void parseHTable(Nod** hTab, int size) {
	for (int i = 0; i<size; i++)
		if (hTab[i]) {  // lista i contine cel putin un student
			Nod* tmp = hTab[i];
			printf("Lista no. %d:\n", i);
			while (tmp) {
				printf("%d %s %s\n", tmp->st.id, tmp->st.nume, tmp->st.nrGrupa);
				tmp = tmp->next;
			}
		}
}

Student cauta_student_nume(Nod* *hTab, int size_hTab, char* nume_student)
{
	int k;
	k = calculPozitie_string(nume_student, size_hTab);

	Student s;
	s.nume = NULL; // ipoteza: studentul nu exista in tabela hash
	Nod* tmp = hTab[k]; // tmp - adresa primul nod din lista k
	while (tmp)
	{
		if (strcmp(nume_student, tmp->st.nume) == 0)
		{
			// studentul este identificat in tabela de dispersie
			s.id = tmp->st.id;
			s.nume = tmp->st.nume;
			strcpy(s.nrGrupa, tmp->st.nrGrupa);

			// return s;
		}
		tmp = tmp->next;
	}

	return s;
}

// stergerea studentilor care fac parte din aceeasi grupa
void stergere_studenti_grupa(Nod* *hTab, int size_hTab, char* nr_grupa)
{
	for (int i = 0; i < size_hTab; i++) // traversare secventiala vector (tabela de dispersie)
	{
		if (hTab[i] != NULL)
		{
			// exista lista simpla i cu cel putin 1 nod (student)
			// traversare secventiala lista i

			// stergerea nodurilor aflate pe pozitiile consecutive 1, 2, ... j ale listei simple i
			while (hTab[i] && strcmp(hTab[i]->st.nrGrupa, nr_grupa) == 0)
			{
				Nod* tmp = hTab[i]; // tmp este nodul care tb dezalocat
				hTab[i] = hTab[i]->next; // noul inceput de lista simpla i este nodul 2

				free(tmp->st.nume);
				free(tmp);
			}

			if (hTab[i] != NULL)
			{
				// stergerea nodurilor de pe pozitii interioare ale listei simple i
				Nod* tmp = hTab[i];

				while (tmp->next)
				{
					if (strcmp(tmp->next->st.nrGrupa, nr_grupa) == 0)
					{
						Nod* de_sters = tmp->next;
						tmp->next = de_sters->next; // actualizare succesor pentru tmp

						// dezalocare nod
						free(de_sters->st.nume);
						free(de_sters);
					}
					else
						tmp = tmp->next;
				}
			}
		}
	}
}

// dezalocarea tabelei de dispersie


// Extragerea studentilor din tabela de dispersie (cu dezalocare noduri) pe baza numelui specificat.
// Studentii se salveaza intr-un vector
// in - hTab - tabela de dispersie
// in - size_hTab - dimensiunea vector (tabela de dispersie)
// in - nume_student - nume student folosit la identificarea nodurilor
// out - return - adresa de inceput a vectorului unde se salveaza studentii extrasi
// out - size_vStudenti - dimensiunea vectorului returnat cu studentii extrasi
Student* extrage_studenti_nume(Nod* *hTab, int size_hTab, char* nume_student, int &size_vStudenti)
{
}

void main() {

	Nod* *HTable; // vector de elemente de tip Nod* (adrese de inceput de lista simpla)
	Student stud;

	// alocare spatiu tabela de dispersie
	HTable = (Nod**)malloc(sizeof(Nod*) * DIM);

	// initializare elemente tabela de dispersie
	for (int i = 0; i<DIM; i++)
		HTable[i] = NULL;  // HTable[i] => elementul i in tabela hash


	FILE * f;
	f = fopen("Studenti.txt", "r");
	char studBuff[20];

	char * token, file_buf[LINESIZE], sep_list[] = ",\n";

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
	}

	parseHTable(HTable, DIM);

	stud = cauta_student_nume(HTable, DIM, (char*)"Vasilescu George");
	if (stud.nume != NULL)
	{
		printf("\nStudent identificat: %d %s\n", stud.id, stud.nrGrupa);
	}
	else
	{
		printf("\nStudent nu este in tabela hash.\n");
	}

	stergere_studenti_grupa(HTable, DIM, (char*)"1055");
	printf("\n Tabela de dispersie dupa stergere studentilor din grupa specificata.\n\n");
	parseHTable(HTable, DIM);
	
	fclose(f);
}