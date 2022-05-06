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

char insertStudent(struct Student* ht, int size, struct Student s) {
	int pos = positionHashFunction(s.name, size);
	// printf("Position: %d for %s\n", pos, s.name);

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
		if (ht[i].name == NULL)
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
		return -1; // studentul nu a fost identificat in tabela de dispersie
}

char deleteStudent(struct Student* ht, int size, char* studName)
{
	int poz = searchStudent(ht, size, studName);
	if (poz == -1)
		return 0;

	free(ht[poz].name);
	ht[poz].name = NULL;
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

	struct Student* temp = (struct Student*)malloc(sizeof(struct Student) * (sup - inf));
	int  j = 0;
	for (int i = inf; i < poz; i++)
	{ // salvare studenti in vectorul temp (subcluster stanga)
		temp[j++] = ht[i];
		ht[i].name = NULL;
	}
	for (int i = poz + 1; i <= sup; i++)
	{ // salvare studenti in vectorul temp (subcluster dreapta)
		temp[j++] = ht[i];
		ht[i].name = NULL;
	}

	for (int i = 0; i < (sup - inf); i++)
		flag = insertStudent(ht, size, temp[i]);

	free(temp);

	return 1;
}

void main() {
	FILE* f;
	f = fopen("Students.txt", "r");

	char buffer[LINESIZE], seps[] = { ",\n" }, * token;
	struct Student s;

	struct Student* HTable;
	unsigned int size = ARRAY_SIZE;

	HTable = (struct Student*)malloc(size * sizeof(struct Student));
	for (unsigned int i = 0; i < size; i++) {
		HTable[i].name = NULL; // flag pentru disponibilitate pozitie i la inserare student
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

		char insert = insertStudent(HTable, size, s); // inserare student s in tabela de dispersie cu linear probing
		int newSize = size;

		while (!insert) {
			struct Student* newHTable;
			newSize += ARRAY_SIZE;
			newHTable = (struct Student*)malloc(newSize * sizeof(struct Student));

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL;
			}

			insert = 1;
			for (unsigned int i = 0; i < size && insert; i++) {
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

	// cautare student in tabela de dispersie
	int pos_student = searchStudent(HTable, size, "Pavel Ionescu");
	if (pos_student != -1)
	{
		// student identificat in tabela de dispersie
		printf("\nStudent identificat: %d %s", HTable[pos_student].id, HTable[pos_student].name);
	}
	else
		printf("\nStudentul cautat nu este in tabela de dispersie!");

	printf("\nTabela de dispersie inainte de stergere student:\n");
	for (unsigned int i = 0; i < size; i++)
	{
		if (HTable[i].name != NULL)
		{
			printf("\nPosition: %d %s", i, HTable[i].name);
		}
	}
	char sters = deleteStudent(HTable, size, "Popescu Gigel");
	if (sters)
	{
		printf("\n\nTabela de dispersie dupa stergere student:\n");
		for (unsigned int i = 0; i < size; i++)
		{
			if (HTable[i].name != NULL)
			{
				printf("\nPosition: %d %s", i, HTable[i].name);
			}
		}
	}
	else
		printf("\nStudentul nu a fost gasit in tabela de dispersie.\n");

	// dezalocare tabela de dispersie
	for (unsigned int i = 0; i < size; i++)
		if (HTable[i].name != NULL)
			free(HTable[i].name);
	free(HTable);

	fclose(f);
}
