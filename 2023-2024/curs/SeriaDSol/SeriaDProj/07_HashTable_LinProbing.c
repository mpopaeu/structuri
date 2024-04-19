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
		sum += str[i];

	return sum % size; // impartire modulo pentru a obtine offset valid in tabela de dipersie (vector)
}

char insertStudent(struct Student* ht, int size, struct Student s) {
	// 1. calcul offset valid pentru vectorul (tabela de dispersie) ht
	int pos = positionHashFunction(s.name, size);
	printf("Position: %d for %s\n", pos, s.name);

	char inserted = 0;

	for (int i = pos; i < size && !inserted; i++) {
		if (ht[i].name == NULL) {
			ht[i] = s;
			inserted = 1;
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
		if (ht[i].name == 0)
			found = -1;
		else if (strcmp(ht[i].name, studName) == 0)
		{
			found = 1;
			pos = i;
		}
	}

	if (found == 1)
		return pos;
	else
		return -1;
}


char deleteStudent(struct Student* ht, int size, char* studName)
{
	int poz = searchStudent(ht, size, studName); // pozitie reala a studentului in tabela hash
	if (poz == -1)
		return 0;

	free(ht[poz].name); // dezalocare nume student
	ht[poz].name = 0;   // disponibilizare pozitie la inserare dupa efectuare stergere
	int inf, sup;

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
	for (int i = poz + 1; i < size && !flag; i++)
		if (ht[i].name == 0)
		{
			flag = 1;
			sup = i - 1;
		}
	if (!flag)
		sup = size - 1;

	if ((sup - inf) > 0)
	{
		struct Student* temp = (struct Student*)malloc(sizeof(struct Student) * (sup - inf)); // alocare vector temporar studenti din cele 2 subclustere formate
		int  j = 0;
		for (int i = inf; i < poz; i++) // subcluster stanga
		{
			temp[j++] = ht[i]; // salvare student in vector temporar
			ht[i].name = 0; // disponibilizare pozitie
		}
		for (int i = poz + 1; i <= sup; i++) // subcluster dreapta
		{
			temp[j++] = ht[i]; // salvare student in vector temporar
			ht[i].name = 0;    // disponibilizare pozitie
		}

		for (int i = 0; i < (sup - inf); i++)
			flag = insertStudent(ht, size, temp[i]); // reinserare studenti in tabela de dispersie
													 // pozitiile ocupate vor fi in [inf, sup]

		free(temp);
	}

	return 1;
}

void main() {
	FILE* f;
	f = fopen("Studenti.txt", "r");

	char buffer[LINESIZE], seps[] = { ",\n" }, * token;
	struct Student s;

	struct Student* HTable; // tabela de dispersie cu linear probing
	int size = ARRAY_SIZE;

	HTable = (struct Student*)malloc(size * sizeof(struct Student));
	for (int i = 0; i < size; i++) {
		HTable[i].name = NULL; // fiecare element din vectorul HTable (tabela de dispersie)
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
			struct Student* newHTable;
			newSize += ARRAY_SIZE;
			newHTable = (struct Student*)malloc(newSize * sizeof(struct Student)); // alocare tabela noua pt +ARRAY_SIZE elemente

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL;
			}

			insert = 1;
			for (int i = 0; i < size && insert; i++) { // tabela veche se parseaza secvential (element cu element)
				if (HTable[i].name) // la offset i in tabela veche se afla date student valid
					insert = insertStudent(newHTable, newSize, HTable[i]); // mutare element i din tabela veche pe cea noua
			}

			if (!insert) {
				free(newHTable); // dezalocare tabela noua pentru ca mutarea elementelor de pe tabela veche a esuat
			}
			else { // mutare cu succes a elemetelor de pe tabela veche pe tabela noua
				free(HTable); // dezalocare vector suport pentru tabela veche

				HTable = newHTable; // comutare pointer tabela veche pe pointer tabela noua
				size = newSize;		// comutare size pe noua dimensiune a tabelei noi

				insert = insertStudent(HTable, size, s); // tentativa de inserare a studentului in tabela
			}
		}
	}

	printf("\n Continut tabela de dispersie (dimensiune %d):\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	// cautare student in tabela de dispersie
	int poz_student = searchStudent(HTable, size, "Mihai Vasilescu");
	if (poz_student != -1)
	{
		printf("\n\nStudent identificat: %d %s\n\n", HTable[poz_student].id, HTable[poz_student].name);
	}
	else
	{
		printf("Studentul nu exista in tabela de dispersie!\n");
	}

	char studName[] = { "Popescu Gigel" };
	char deleted = deleteStudent(HTable, size, studName);

	printf("\n Tabela de dispesie dupa stergere: %d elemente\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %d %s\n", i, HTable[i].id, HTable[i].name);
		}
	}

	// dezalocare tabela hash
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			free(HTable[i].name); // dezalocare string pentru nume student stocat pe offset i in tabela
		}
	}
	free(HTable);
	HTable = NULL;

	fclose(f);
}