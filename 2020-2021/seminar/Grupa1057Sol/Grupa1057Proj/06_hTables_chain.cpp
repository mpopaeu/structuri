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

void inserareHTable(Nod** hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = calculPozitie(s, sizeHT);

	hTab[k] = inserareLista(hTab[k], s);
}

void parseHTable(Nod** hTab, int size) {
	for (int i = 0; i < size; i++)
		if (hTab[i]) {  // lista i contine cel putin un student
			Nod* tmp = hTab[i];
			printf("Lista no. %d:\n", i);
			while (tmp) {
				printf("%d %s %s\n", tmp->st.id, tmp->st.nume, tmp->st.nrGrupa);
				tmp = tmp->next;
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

Student cauta_student(Nod** hTab, int size, char* nume_student)
{
	int k = calculPozitie_String(nume_student, size);

	Nod* tmp = hTab[k]; // adresa de inceput a listei simple k din vectorul hTab
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
//////
// identificarea studentilor intr-o grupa specificata
Nod* studenti_grupa(Nod** hTab, int size, const char* nr_grupa)
{
	Nod* lst = NULL;

	for (int i = 0; i < size; i++)
	{
		if (hTab[i])
		{
			// exista cel putin 1 nod in lista hTab[i]
			Nod* tmp = hTab[i];
			while (tmp)
			{
				if (strcmp(tmp->st.nrGrupa, nr_grupa) == 0)
				{
					lst = inserareLista(lst, tmp->st); // malloc dedicat pentru nume student la inserare in nod lista simpla 
													   // (FARA partajare intre lista si tabela hash)
				}

				tmp = tmp->next;
			}
		}
	}

	return lst;
}


// modificarea cheii de cautare a unui student specificat prin cheie de cautare

// creare tabela de dispersie (cheie de cautare: numar grupa) pentru studentii care au acelasi nume specificat (cheie: nume student)
// tabela de dispersie nr 2 - aceeasi dimensiune DIM ca tabela nr. 1
// [in] hTab - tabela de dispersie (cheie: nume student); sursa de date pentru tabela nr. 2
// [in] size - dimensiune tabele de dispersie nr. 1 (cheie: nume student), nr. 2 (cheie: nr grupa)
// [in] nume_student - nume student care se copiaza din tabela nr. 1 in tabela nr. 2
// [out] return [Nod**] - tabela de dispersie nr. 2 (cheie: nr grupa)

void inserareHTable_grupa(Nod** hTab, int sizeHT, Student s) {
	int k; // pozitie de inserare pentru s
	k = calculPozitie_String(s.nrGrupa, sizeHT);

	hTab[k] = inserareLista(hTab[k], s);
}

Nod** tabela_hash_grupa(Nod** hTab, int size, char* nume_student)
{
	Nod** hTab_grupa = (Nod**)malloc(size * sizeof(Nod*)); // tabela de dispersie nr. 2 (cheie: nr grupa)
	for (int i = 0; i < size; i++)
		hTab_grupa[i] = NULL;


	int k = calculPozitie_String(nume_student, size);

	Nod* tmp = hTab[k]; // adresa de inceput a listei simple k din vectorul hTab
	while (tmp)
	{
		if (strcmp(nume_student, tmp->st.nume) == 0)
		{
			inserareHTable_grupa(hTab_grupa, DIM, tmp->st);
		}
		tmp = tmp->next;
	}

	return hTab_grupa;
}


int main() {

	Nod* *HTable; // vector suport pentru tabela de dispersie; alocare in mem heap la runtime
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

	printf("\n Tabela de dispersie dupa creare:\n");
	parseHTable(HTable, DIM);

	// cautare student pe baza cheii de cautare
	char nume_student[] = {"Popescu Marian"};
	stud = cauta_student(HTable, DIM, nume_student);
	if (stud.nume)
	{
		printf("\n\n Studentul a fost identificat: %d %s\n", stud.id, stud.nrGrupa);
	}
	else
	{
		printf("\n\n Studentul %s nu a fost identificat in tabela de dispersie.\n", nume_student);
	}

	// creare lista simpla cu studentii in grupa specificata
	Nod* lst_studs = studenti_grupa(HTable, DIM, "1057");
	printf("\n Studenti in lista cu grupa specificata:\n");
	Nod* tmp = lst_studs;
	while (tmp)
	{
		printf("%d %s\n", tmp->st.id, tmp->st.nume);
		tmp = tmp->next;
	}

	// creare tabela de dispersie nr. 2 (cheie: nr grupa) pentru un student cu nume specificat
	Nod** HTable_grupa = tabela_hash_grupa(HTable, DIM, (char*)"Ionescu Cristian");

	printf("\n\n Tabela de dispersie nr. 2 (cheie: nr grupa):\n");
	parseHTable(HTable_grupa, DIM);

	// dezalocare tabela de dispersie nr. 1
	// 1. dezalocare liste simple (max DIM liste simple)
	for (int i = 0; i < DIM; i++)
		if (HTable[i]) {  // lista i contine cel putin un student
			Nod* tmp = HTable[i];
			while (tmp) {
				HTable[i] = tmp->next; // nodul 2 din lista (daca exista)

				free(tmp->st.nume);
				free(tmp);
				
				tmp = HTable[i];
			}
		}
	// 2. dezalocare vector de adrese de inceput de liste (au devenit toate de tip NULL)
	free(HTable);

	// dezalocare lista simpla lst_studs

	// dezalocare tabela de dispersie nr. 2 (HTable_grupa)

	fclose(f);

	return 0;
}