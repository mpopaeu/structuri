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

	return sum % size;
}

// inserare student cu cheie string (nume student)
char insertStudent(struct Student* ht, int size, struct Student s) {
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

// cautare student dupa cheie
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

// stergere student
char deleteStudent(struct Student* ht, int size, char* studName)
{
	int poz = searchStudent(ht, size, studName);
	if (poz == -1)
		return 0;

	// exista student de sters pe pozitia poz
	free(ht[poz].name); // dezalocare nume student care se sterge in tabela
	ht[poz].name = NULL;
	int inf, sup;

	char flag = 0;
	for (int i = poz - 1; i >= 0 && !flag; i--)
	{
		if (ht[i].name == 0)
		{
			flag = 1;
			inf = i + 1; // inf este limita inferioara cluster din care se sterge studentul
		}
	}
	if (!flag)
		inf = 0;

	flag = 0;
	for (int i = poz + 1; i < size && !flag; i++)
		if (ht[i].name == 0)
		{
			flag = 1;
			sup = i - 1; // sup este limita superioara cluster din care se sterge studentul
		}
	if (!flag)
		sup = size - 1;

	struct Student* temp = (struct Student*)malloc(sizeof(struct Student) * (sup - inf)); // alocare vector temporar stocare studenti cuprinsi in [inf, sup]
																						  // mai putin studentul care s-a sters
	int  j = 0;
	for (int i = inf; i < poz; i++)
	{
		temp[j++] = ht[i]; // salvare student din sub-cluster stanga in structura temporara
		ht[i].name = NULL; // disponibilare pozitie pentru re-inserare
	}
	for (int i = poz + 1; i <= sup; i++)
	{
		temp[j++] = ht[i]; // salvare student din sub-cluster dreapta in vector temporar
		ht[i].name = NULL; // disponibilzare pozitie pentru re-inserare
	}

	for (int i = 0; i < (sup - inf); i++) // toti studentii dun sub-cluster stanga si sub-cluster dreapta sunt reinserati in tabela
		flag = insertStudent(ht, size, temp[i]); // re-inserare student din vector temporar inapoi in tabela hash

	free(temp); // dezalocare vector temporar

	return 1;
}

int main() {
	FILE* f;
	f = fopen("Studenti.txt", "r");

	char buffer[LINESIZE], seps[] = { ",\n" }, * token;
	struct Student s;

	struct Student* HTable;
	int size = ARRAY_SIZE;

	HTable = (struct Student*)malloc(size * sizeof(struct Student));
	for (int i = 0; i < size; i++) {
		HTable[i].name = NULL;
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

		char insert = insertStudent(HTable, size, s); // inserare date noi in tabela de dispersie
		int newSize = size;

		while (!insert) { // proces realocare, mutare si inserare date intr-o noua tabela
			struct Student* newHTable;
			newSize += ARRAY_SIZE; // dimensiune noua tabela hash
			newHTable = (struct Student*)malloc(newSize * sizeof(struct Student)); // alocare noua tabela hash

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL; // marcare elemente de pe noua tabela hash ca fiind disponibile la inserare
			}

			insert = 1;
			for (int i = 0; i < size && insert; i++) { // mutare elemente din vechea tabela pe noua tabela
				if (HTable[i].name)
					insert = insertStudent(newHTable, newSize, HTable[i]); // mutare prin reinserare (posibil pozitii diferite in noua tabela)
			}

			if (!insert) {
				free(newHTable); // esec mutare elemente pe noua tabela; noua tabela se dezaloca
			}
			else {
				free(HTable); // dezalocare tabela hash veche

				HTable = newHTable; // comutare variabila acces la tabela pe noul vector
				size = newSize; // update dimensiune tabela pe noua dimensiun

				insert = insertStudent(HTable, size, s); // inserare date noi in tabela noua
			}
		}
	}
	fclose(f);

	printf("\n Continut tabela de dispersie (dimensiune %d):\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	int pos_found = searchStudent(HTable, size, "Popescu Gigel");

	printf("\nCautare date dupa cheie de cautare:\n");
	if (pos_found == -1)
		printf("\nStudent nu exista in tabela\n");
	else
	{
		printf("\nStudent identificat: %d %s\n", HTable[pos_found].id, HTable[pos_found].name);
	}

	char sters = deleteStudent(HTable, size, "Ionescu Pavel");
	if (sters == 0)
		printf("\nStudentul nu a fost identificat in tabela hash.\n");
	else
	{
		printf("\nStudent sters. Continut tabela hash:\n");
		for (int i = 0; i < size; i++) {
			if (HTable[i].name) {
				printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
			}
		}
	}

	return 0;
}