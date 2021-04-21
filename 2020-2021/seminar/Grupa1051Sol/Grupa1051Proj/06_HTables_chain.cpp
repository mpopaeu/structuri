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

int calculPozitie(Student s, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i < strlen(s.nume); i++)
		temp += s.nume[i];

	poz = temp % size;

	printf("%d %d   ", temp, poz);

	return poz;
}

int calculPozitie_String(char* str, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i < strlen(str); i++)
		temp += str[i];

	poz = temp % size;

	printf("%d %d   ", temp, poz);

	return poz;
}

void inserareHTable(Nod** hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = calculPozitie(s, sizeHT);

	hTab[k] = inserareLista(hTab[k], s); // inserare student s in lista simpla hTab[k]
}


void parseHTable(Nod** hTab, int size) {
	for (int i = 0; i < size; i++)
		if (hTab[i]) {  // lista i contine cel putin un student
			Nod* tmp = hTab[i];
			printf("Lista no. %d:\n", i);
			while (tmp) {
				printf("%d %s\n", tmp->st.id, tmp->st.nume);
				tmp = tmp->next;
			}
		}
}

Student cauta_student(Nod** hTab, int size, char* nume_student)
{
	int k; 
	k = calculPozitie_String(nume_student, size);

	Nod* tmp = hTab[k];
	while (tmp)
	{
		if (strcmp(nume_student, tmp->st.nume) == 0)
		{
			return tmp->st;
		}

		tmp = tmp->next;
	}

	Student s;
	s.nume = NULL;
	return s;
}

// TEMA
///////
// stergere student(ilor) identificat pe baza cheii de cautare (nume student)

// cautare studenti pentru un nr de grupa specificat (fara printf in functie)
Nod* cauta_studenti_grupa(Nod** hTab, int size, const char* nr_grupa)
{
	Nod* lst_studs = NULL;

	for (int i = 0; i < size; i++)
	{
		if (hTab[i]) // exista cel putin1 nod in lista i din tabela de dispersie
		{
			Nod* tmp = hTab[i];
			while (tmp)
			{
				if (strcmp(tmp->st.nrGrupa, nr_grupa) == 0)
				{
					lst_studs = inserareLista(lst_studs, tmp->st);
				}
				tmp = tmp->next;
			}
		}
	}

	return lst_studs;
}

// modificare nume student; studentul se identifica si pe baza criteriul 2 -> id student
// [in] hTab - tabela de dispersie cu chaining cu studenti
// [in] size - dimensiune tabela de dispersie
// [in] nume_student - numele studentului care se modifica
// [in] id_student - id student care se modifica (pt identificare exacta a studentului cu nume nou)
// [in] nume_nou_student - numele care inlocuieste nume_student in tabela hTab

void modificare_nume_student(Nod** hTab, int size, char* nume_student, int id_student, char* nume_nou_student)
{

}

int main() {

	Nod* *HTable; // vector de Nod*
	Student stud;

	// alocare spatiu tabela de dispersie (vector)
	HTable = (Nod**)malloc(sizeof(Nod*) * DIM);

	// initializare elemente tabela de dispersie
	for (int i = 0; i < DIM; i++)
		HTable[i] = NULL;  // HTable[i] => elementul i in tabela hash


	FILE* f;
	f = fopen("Studenti.txt", "r");
	char studBuff[20];

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
		free(stud.nume);
	}

	printf("\n\n Tabela de dispersie dupa creare:\n");
	parseHTable(HTable, DIM);

	char nume_student[] = {"Pop Gigelescu"};
	stud = cauta_student(HTable, DIM, nume_student);
	if (stud.nume != NULL)
	{
		printf("\n\n Student identificat: %d %s\n", stud.id, stud.nrGrupa);
	}
	else
	{
		printf("\n\n Studentul %s nu a fost identificat in tabela hash.\n", nume_student);
	}

	Nod* lista_studenti_grupa = cauta_studenti_grupa(HTable, DIM, "1051");
	printf("\n\n Studenti din grupa cautata (1051):\n");
	Nod* tmp = lista_studenti_grupa;
	while (tmp)
	{
		printf("\nStudent %d %s in grupa 1051:", tmp->st.id, tmp->st.nume);
		tmp = tmp->next;
	}

	// dezalocare tabela de dispersie
	for (int i = 0; i < DIM; i++) // dealocare liste cu adrese de inceput stocate in vector
		if (HTable[i]) {  // lista i contine cel putin un student
			Nod* tmp = HTable[i];			
			while (tmp) {
				HTable[i] = tmp->next;
				
				// dezalocare mem heap 
				free(tmp->st.nume);
				free(tmp);

				tmp = HTable[i];
			}
		}

	free(HTable); // dezalocare vector de pointeri la liste simple
	HTable = NULL;

	// dezalocare lista simpla lista_studenti_grupa

	fclose(f);

	return 0;
}
