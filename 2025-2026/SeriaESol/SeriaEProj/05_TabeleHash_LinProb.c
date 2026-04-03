#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128
#define ARRAY_SIZE 100

struct Student {
	int id;
	char* name;
	float avg;
};

int positionHashFunction(char* str, int size) {
	int sum = 0;
	for (unsigned int i = 0; i < strlen(str); i++)
		sum += str[i]; // suma coduri ASCII string str

	return sum % size; // translatare la offset valid pe tabela hash
}

char insertStudent(struct Student* ht, int size, struct Student s) {
	int pos = positionHashFunction(s.name, size); // calcul functie hash
	printf("Position: %d for %s\n", pos, s.name); // logging pentru identificare situatii de coliziune a datelor

	char inserted = 0;

	for (int i = pos; i < size && !inserted; i++) {
		if (ht[i].name == NULL) { // verificare pozitie disponibila (name == NULL inseamna disponibil pentru scriere
			ht[i] = s;
			inserted = 1; // flag pentru iesire din DO-FOR; studentul s se scrie o singura data in tabela
		}
	}

	return inserted;
}


int searchStudent(struct Student* ht, int size, char* studName)
{
	int pos = positionHashFunction(studName, size);
	char found = 0;
	for (int i = pos; i < size && !found; i++)
	{
		if (ht[i].name == NULL)
			found = -1; // studentul cautat nu exista in tabela de dispersie
		else if (strcmp(ht[i].name, studName) == 0)
		{
			found = 1; // flag care arata ca exista student
			pos = i; // salvare pozitie real a studentului cu studNume in tabela hash
		}
	}

	if (found == 1)
		return pos; // se returneaza offset real din vector unde se afla studentul;
					// se returneaza DOAR primul student cu cheie cautata
	else
		return -1; // studentul nu exista in tabela hash
}

char deleteStudent(struct Student* ht, int size, char* studName)
{
	int poz = searchStudent(ht, size, studName);
	if (poz == -1)
		return 0; // studentul nu exista in tabela

	free(ht[poz].name); // dezalocare extensii student in heap mem
	ht[poz].name = NULL; // disponibilizare pozitie pentru scriere ulterioara
	int inf, sup; // limite inf si sup cluster in care se afla studentul sters

	char flag = 0;
	for (int i = poz - 1; i >= 0 && !flag; i--) // determinare limita inf (offset in vector) cluster
	{
		if (ht[i].name == NULL)
		{
			flag = 1;
			inf = i + 1;
		}
	}
	if (!flag)
		inf = 0;

	flag = 0;
	for (int i = poz + 1; i < size && !flag; i++) // determinare limita superioara (offset in vector) cluster
		if (ht[i].name == NULL)
		{
			flag = 1;
			sup = i - 1;
		}
	if (!flag)
		sup = size - 1;

	struct Student* temp = (struct Student*)malloc(sizeof(struct Student) * (sup - inf)); // alocare vector temporar pentru stocare studenti din subcluster stanga + subcluster dreapta
	int  j = 0;
	for (int i = inf; i < poz; i++) // mutare date din subcluster stanga
	{
		temp[j++] = ht[i];
		ht[i].name = NULL; // disponibilizare pozitie pentru scriere ulterioara
	}
	for (int i = poz + 1; i <= sup; i++) // mutare date din subcluster dreapta
	{
		temp[j++] = ht[i];
		ht[i].name = NULL; // disponibilizare pozitie pentru scriere ulterioara
	}

	for (int i = 0; i < (sup - inf); i++) // reinserare elemente student din structura temporara inapoi pe tabela hash
										  // studentii reinserati pot avea pozitii reale diferite dupa reinserare
		flag = insertStudent(ht, size, temp[i]); 

	free(temp); // dezalocare vector temporar

	return 1;
}

int main() {
	FILE* f;
	f = fopen("Studenti.txt", "r");

	char buffer[LINESIZE], seps[] = { ",\n" }, * token;
	struct Student s;

	struct Student* HTable; // tabela de dispersie
	int size = ARRAY_SIZE;

	HTable = (struct Student*)malloc(size * sizeof(struct Student)); // alocare tabela hash pe size initial
	for (int i = 0; i < size; i++) {
		HTable[i].name = NULL; // marcare pozitii disponibile pentru scriere
	}


	while (fgets(buffer, LINESIZE, f)) {
		token = strtok(buffer, seps);
		s.id = atoi(token);

		token = strtok(NULL, seps);
		s.name = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(s.name, token);

		token = strtok(NULL, seps);
		s.avg = (float)atof(token);

		printf("%d %s\n", s.id, s.name);

		char insert = insertStudent(HTable, size, s);
		int newSize = size;

		while (!insert) { // proces realocare tabele de dispersie
			struct Student* newHTable; // noua tabela hash
			newSize += ARRAY_SIZE; // noul size de tabela 
			newHTable = (struct Student*)malloc(newSize * sizeof(struct Student)); // alocare noua tabela 

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL; // disponibilizare elemente pentru scriere pe noua tabela
			}

			insert = 1;
			for (int i = 0; i < size && insert; i++) { // mutare elemente din vechea tabela pe noua tabela
				if (HTable[i].name)
					insert = insertStudent(newHTable, newSize, HTable[i]); // mutare prin reinserare deoarece functia hash poate furniza la rezultate diferite, newSize fiind diferit fata de size
			}

			if (!insert) {
				free(newHTable); // daca mutarea elemente a esuat, se dezaloca tabela noua si se incearca o noua tabela cu un newSize si mai mare pe iteratia urmatoare
			}
			else {
				// mutarea elemente a fost efectuata cu succes
				free(HTable); // dezalocare tabela veche

				HTable = newHTable; // comutare pointer gestionare tabela hash pe noua tabela hash
				size = newSize; // actualizare pentru noua tabela 

				insert = insertStudent(HTable, size, s); // o noua incercare de a insera datele noi pe noua tabela
			}
		} // while proces de realocare tabela hash
	} // while parsare fisier cu date de intrare

	fclose(f);

	printf("\n Continut tabela de dispersie (dimensiune %d):\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	int pos = searchStudent(HTable, size, "Gigel opescuP");
	printf("\nCautare student (prima aparitie) in tabela de dispersie:\n");
	if (pos == -1)
	{
		printf("\nStudentul cautat nu exista in tabela.\n");
	}
	else
	{
		printf("\n %d %s\n", HTable[pos].id, HTable[pos].name);
	}

	char sters = deleteStudent(HTable, size, "Georgescu Alexandru");
	printf("\nStergere student din tabela hash:\n");
	if (sters == 0)
	{
		printf("\nStudentul nu exista in tabela.\n");
	}
	else
	{
		printf("\n Continut tabela de dispersie dupa stergere (dimensiune %d):\n", size);
		for (int i = 0; i < size; i++) {
			if (HTable[i].name) {
				printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
			}
		}
	}
		
	// dezalocare tabela de dispersie

	return 0;
}