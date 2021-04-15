#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128
#define ARRAY_SIZE 100

struct Student {
	int id;
	char *name;
	float avg;
};

int positionHashFunction(char *str, int size) {
	int sum = 0;
	for (int i = 0; i<strlen(str); i++)
		sum += str[i];

	return sum % size; // rezultatul este intodeauna pozitie valida in tabela de dispersie
}

// in - tabela de dispersie (vector de studenti)
// in - dimensiune tabela de dispersie
// in - studentul de inserat
// out - 1 inserare cu succes, 0 inserare ne-efectuata
char insertStudent(Student* ht, int size, Student s) {
	int pos = positionHashFunction(s.name, size); // implementare functie hash
	printf("Position: %d for %s\n", pos, s.name);

	char inserted = 0;

	for (int i = pos; i<size && !inserted; i++) {
		if (ht[i].name == NULL) {
			ht[i] = s; // studentul s se aseaza pe pozitia i in tabela de dispersie
			inserted = 1;
		}
	}

	return inserted;
}


int searchStudent(Student* ht, int size, char* studName)
{
	int pos = positionHashFunction(studName, size);
	char found = 0;
	for (int i = pos; i<size && !found; i++)
	{
		if (ht[i].name == 0)
			found = -1; // se termina de traversat cluster-ul in care studNume ar tb sa fie identificat
		else if (strcmp(ht[i].name, studName) == 0)
		{
			found = 1; // student identifict in cluster
			pos = i; // pozitia reala a studentului in tabela de dispersie
		}
	}

	if (found == 1)
		return pos;
	else
		return -1;
}


char deleteStudent(Student* ht, int size, char* studName)
{
	int poz = searchStudent(ht, size, studName); // poz - pozitia reala in cluster a studentului cautat 
	if (poz == -1)
		return 0;

	free(ht[poz].name); // dezalocare nume student
	ht[poz].name = NULL; // "stergere" logica student in tabela de dispersie
						// disponibilizare pozitie la inserare
	int inf, sup; // limitele inferioara, superioara cluster in care studentul a fost identificat

	char flag = 0;
	for (int i = poz - 1; i >= 0 && !flag; i--)
	{
		if (ht[i].name == 0)
		{
			flag = 1;
			inf = i + 1;
		}
	}
	if (!flag)
		inf = 0;

	flag = 0;
	for (int i = poz + 1; i<size && !flag; i++)
		if (ht[i].name == 0)
		{
			flag = 1;
			sup = i - 1;
		}
	if (!flag)
		sup = size - 1;

	Student* temp = (Student*)malloc(sizeof(Student)*(sup - inf)); // temp - vector temporar care stocheaza studentii din cluster-ele delimitate de poz
	int  j = 0;
	// copiere elemente din cluster 1 in temp
	for (int i = inf; i<poz; i++)
	{
		temp[j++] = ht[i];
		ht[i].name = 0; // disponibilizare pozitie in cluster 1
	}
	// copiere elemente din cluster 2 in temp
	for (int i = poz + 1; i <= sup; i++)
	{
		temp[j++] = ht[i];
		ht[i].name = 0; // disponibilizare pozitie in cluster 2
	}

	for (int i = 0; i < (sup - inf); i++)
		flag = insertStudent(ht, size, temp[i]);

	free(temp);

	return 1;
}

void main() {
	FILE* f;
	f = fopen("Students.txt", "r");

	char buffer[LINESIZE], seps[] = { ",\n" }, *token;
	Student s;

	Student * HTable;	// pointer cu care se gestioneaza tabela de dispersie (vector)
	int size = ARRAY_SIZE;

	HTable = (Student*)malloc(size * sizeof(Student)); // alocare initiala a tabelei de dispersie
	for (unsigned int i = 0; i<size; i++) {
		HTable[i].name = NULL; // marcaj de disponilitate a pozitiei i la inserare
	}


	while (fgets(buffer, LINESIZE, f)) {
		token = strtok(buffer, seps);
		s.id = atoi(token);

		token = strtok(NULL, seps);
		s.name = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(s.name, token);

		token = strtok(NULL, seps);
		s.avg = atof(token);

		printf("%d %s\n", s.id, s.name);

		char insert = insertStudent(HTable, size, s);
		int newSize = size;

		while (!insert) {
			Student *newHTable; // noua tabela de dispersie dupa realocare
			newSize += ARRAY_SIZE; // noua dimensiune a tabelei de dispersie
			newHTable = (Student*)malloc(newSize * sizeof(Student));

			for (int i = 0; i<newSize; i++) {
				newHTable[i].name = NULL; // disponibilizare la inserare a tuturor pozitiilor din noul vector suport
			}

			// "copiere"/reinserare elemente din tabela initiala in noua tabela de dispersie
			insert = 1;
			for (int i = 0; i<size && insert; i++) {
				if (HTable[i].name)
					insert = insertStudent(newHTable, newSize, HTable[i]);
			}

			if (!insert) {
				free(newHTable);
			}
			else {
				free(HTable);

				HTable = newHTable;
				size = newSize;

				insert = insertStudent(HTable, size, s);
			}
		}
	}

	printf("\n Continut tabela de dispersie (dimensiune %d):\n", size);
	for (unsigned int i = 0; i<size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	char studName[] = { "Popescu Gigel" };
	char deleted = deleteStudent(HTable, size, studName);

	printf("\n Tabela de dispesie dupa stergere:\n", size);
	for (unsigned int i = 0; i<size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %d %s\n", i, HTable[i].id, HTable[i].name);
		}
	}

	int poz = searchStudent(HTable, size, studName);
	if (poz != -1)
	{
		// studentul a fost identificat
		printf("\n\n Studentul a fost identificat: %d %5.2f\n\n", HTable[poz].id, HTable[poz].avg);
	}
	else
	{
		printf("\n\n Studentul %s nu exista in tabela de dispersie.\n\n", studName);
	}

	// dezalocare tabela de dispersie
	for (unsigned int i = 0; i < size; i++)
	{
		if (HTable[i].name != NULL)
		{
			free(HTable[i].name); // dezalocare nume student
		}
	}

	free(HTable); // dezalocare vector suport tabela de dispersie

	fclose(f);
}