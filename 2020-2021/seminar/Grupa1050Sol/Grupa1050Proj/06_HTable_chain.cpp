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

int calculPozitie_string(char* nume_student, int size) {  // functie hash
	int temp = 0, poz; // suma valorilor ASCII pentru cheie alfanumerica
	for (int i = 0; i<strlen(nume_student); i++)
		temp += nume_student[i];

	poz = temp % size;
	return poz;
}

void inserareHTable(Nod** hTab, Student s, int sizeHT) {
	int k; // pozitie de inserare pentru s
	k = calculPozitie(s, sizeHT); // functia hash

	hTab[k] = inserareLista(hTab[k], s);
}

void parseHTable(Nod** hTab, int size) {
	for (int i = 0; i<size; i++)
		if (hTab[i]) {  // lista i contine cel putin un student
			Nod* tmp = hTab[i];
			printf("Lista no. %d:\n", i);
			while (tmp) {
				printf("%d %s\n", tmp->st.id, tmp->st.nume);
				tmp = tmp->next;
			}
		}
}

Student cautare_tabela_hash(Nod** hTab, char * nume_student, int size)
{
	int k;
	k = calculPozitie_string(nume_student, size);

	Student s;
	s.nume = NULL;
	Nod* tmp = hTab[k];
	while (tmp)
	{
		if (strcmp(nume_student, tmp->st.nume) == 0)
		{
			s.id = tmp->st.id;
			s.nume = (char*)malloc((strlen(tmp->st.nume) + 1) * sizeof(char));
			strcpy(s.nume, tmp->st.nume);
			strcpy(s.nrGrupa, tmp->st.nrGrupa);
		}
		tmp = tmp->next;
	}
	
	return s;
}

// stergerea studentilor dintr-o grupa specificata 

// lista cu cele mai multe coliziuni in tabela de dispersie (cea mai lunga lista simpla)
// in - tabela de dispersie
// in - dimensiune tabela de dispersie
// out - nr de ordine in vector
// out - nr de noduri din lista (nr de studenti)

// TEMA - generalizare implementare pentru cazul in care exista mai multe liste cu acelasi nr maxim de noduri/studenti
void calcul_max_coliziuni(Nod** hTab, int size, int &idx_list, int &max_elem)
{
	idx_list = -1; // index invalid pentru accesarea unei liste din tabela de dispersie hTab
	max_elem = 0; // lista cu maxim 0 noduri corespunde unei tabele hash empty

	for (int i = 0; i < size; i++)
	{
		if (hTab[i]) // exista lista i in tabela hTab
		{
			int nr_stud = 0;
			Nod* tmp = hTab[i];
			while (tmp)
			{
				nr_stud += 1;
				tmp = tmp->next;
			}

			if (nr_stud > max_elem)
			{
				max_elem = nr_stud;
				idx_list = i;
			}
		}
	}
}

// extragere studenti din tabela de dispesie pe baza numelui specificat (cheie de cautare). 
// Extragerea are loc intr-o structura lista simpla.
// in - hTab tabela de dispersie
// in - nume_student numele studentului cautat (poate fi valid pt mai multe noduri)
// in - size dimensiunea tabela de dispersie
// out - return lista simpla cu studentii extrasi din tabela de dispersie

// TEMA - testare implementare
Nod* extragere_studenti_nume(Nod** hTab, char* nume_student, int size)
{
	int k;
	k = calculPozitie_string(nume_student, size);

	Nod* lst_studs = NULL;

	Nod* tmp = hTab[k];
	while (tmp && tmp->next) // traversare lista i de pe nodul 2,.... n
	{
		if (strcmp(nume_student, tmp->next->st.nume) == 0)
		{
			Nod* tmp_mutat = tmp->next;
			tmp->next = tmp_mutat->next; // am izolat tmp_mutat din lista i
			// adaugarea nodului izolat din tabela de dispersie in lista simpla rezultat
			tmp_mutat->next = lst_studs;
			lst_studs = tmp_mutat;
		}

		tmp = tmp->next;
	}

	// verificare nod 1
	if (strcmp(nume_student, hTab[k]->st.nume) == 0)
	{
		Nod* tmp_mutat = hTab[k];
		hTab[k] = hTab[k]->next;

		// adaugare nodul 1 la lista rezultat
		tmp_mutat->next = lst_studs;
		lst_studs = tmp_mutat;
	}

	return lst_studs;
}

int main() {

	Nod* *HTable; // vector cu elemente de tip adresa (inceput de lista simpla cu studenti care colizioneaza pe cheia de cautare utilizata)
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

	stud = cautare_tabela_hash(HTable, (char*)"Ionescu Cristian", DIM);

	if (stud.nume != NULL)
	{
		printf("Student identificat: %d %s\n\n", stud.id, stud.nrGrupa);
		free(stud.nume);
	}
	else
	{
		printf("Studentul nu a fost identificat in tabela de dispersie.\n\n");
	}

	// determinare lista simpla cu maximul de coliziuni in tabela de dispersie
	int idx_lista, max_stud;
	calcul_max_coliziuni(HTable, DIM, idx_lista, max_stud);
	if (max_stud == 0)
	{
		printf("\n Tabela de dispersie empty.\n");
	}
	else
	{
		printf("\n\n Maximul de coliziuni este in lista %d cu nr de studenti %d.\n", idx_lista, max_stud);
	}

	// dezalocarea tabelei de dispersie
	for (int i = 0; i < DIM; i++) // dezalocare liste
		if (HTable[i] != NULL) {  // lista i contine cel putin un student
			Nod* tmp = HTable[i];
			while (tmp) {
				HTable[i] = HTable[i]->next; // mutare inceput de liste pe nodul 2

				free(tmp->st.nume); // dezalocare nume student din nodul 1
				free(tmp); // dezalocare nod 1

				tmp = HTable[i]; // noul inceput de lista care se va dezaloca pe iteratia urmatoare
			}
		}
	free(HTable); // dezalocare vector suport pentru tabela de dispersie
	HTable = NULL;

	fclose(f);

	return 0;
}