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

	nou->next = p; // inserare la inceputul listei simple p

	return nou; // noul inceput de lista simpla p
}

void inserareHTable(Nod** hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = calculPozitie(s, sizeHT);

	hTab[k] = inserareLista(hTab[k], s);
}

void parseHTable(Nod** hTab, int size) {
	if (hTab != NULL)
	{
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
}

int calculPozitie_String(char* str, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i < strlen(str); i++)
		temp += str[i];

	poz = temp % size;

	printf("%d %d   ", temp, poz);

	return poz;
}

// TEMA
// generalizare implementare pentru un nr oarecare de studenti
Student cauta_student_cheie(Nod** hTab, int size, char* nume_student) // nume student este cheie de cautare
{
	int k = calculPozitie_String(nume_student, size);

	Nod* tmp = hTab[k]; // acces direct la lista k (hTab[k])
	while (tmp)
	{
		if (strcmp(tmp->st.nume, nume_student) == 0)
		{
			// am identificat student cu nume_student
			return tmp->st; // se returneaza primul student care are numele identic cu parametrul de intrare nume_student
		}
		tmp = tmp->next; // acces secvential la nodul urmator din lista k (hTab[k])
	}

	Student s;
	s.nume = NULL;
	return s;
}

// stergere student(i) pentru care se precizeaza cheia de cautare (nume student)

int main() {

	Nod* * HTable; // vector alocat la runtime cu elemente de tip Nod*
	Student stud;

	// alocare spatiu tabela de dispersie
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

	stud = cauta_student_cheie(HTable, DIM, (char*)"Vasilescu Alex");
	if (stud.nume)
	{
		printf("\n\n Student identificat in tabela de dispersie: %d %s\n", stud.id, stud.nrGrupa);
	}
	else
	{
		printf("\n\n Studentul nu a fost identificat in tabela de dispersie.");
	}

	// dezalocare tabela de dispersie
	for (int i = 0; i < DIM; i++) // dezalocare liste (maxim DIM liste in vectorul HTable)
		if (HTable[i]) {  // lista i contine cel putin un student
			Nod* tmp = HTable[i];
			while (tmp) {
				HTable[i] = HTable[i]->next; // actualizare inceput de lista pe nodul 2
				
				// dezalocare nod tmp (nodul 1)
				free(tmp->st.nume);
				free(tmp);

				// actualizare continut variabila tmp
				tmp = HTable[i];
			}
		}
	free(HTable); // dezalocare vector cu adrese de inceput de liste simple
	HTable = NULL;

	printf("\n\n Tabela de dispersie dupa dezalocare:\n");
	parseHTable(HTable, DIM);
	
	fclose(f);

	return 0;
}