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
	int poz = searchStudent(ht, size, studName);
	if (poz == -1)
		return 0;

	free(ht[poz].name); // dezalocare nume student sters
	ht[poz].name = 0; // disponibilizare pozitie student sters
	int inf, sup;

	char flag = 0;
	for (int i = poz - 1; i >= 0 && !flag; i--)
	{
		if (ht[i].name == 0)
		{
			flag = 1;
			inf = i + 1; // inf este limita inferioara subcluster stanga
		}
	}
	if (!flag)
		inf = 0;

	flag = 0;
	for (int i = poz + 1; i < size && !flag; i++)
		if (ht[i].name == 0)
		{
			flag = 1;
			sup = i - 1; // limita superioara subcluster dreapta
		}
	if (!flag)
		sup = size - 1;

	// subclusterele sunt: stanga (inf, poz - 1), dreapta (poz + 1, sup)

	struct Student* temp = (struct Student*)malloc(sizeof(struct Student) * (sup - inf));
	int  j = 0;
	// acces la elementele/studentii dn subcluster stanga
	for (int i = inf; i < poz; i++)
	{
		temp[j++] = ht[i]; // copiere student i in vector temp
		ht[i].name = 0; // disponibilizare pozitie i pentru inserare
	}
	// acces la elementele/studentii din subcluster dreapta
	for (int i = poz + 1; i <= sup; i++)
	{
		temp[j++] = ht[i]; // copiere student i in vector temp
		ht[i].name = 0; // disponibilizare pozitie i pentru inserare
	}

	// re-inserare elemente scoase din cele doua subclustere
	for (int i = 0; i < (sup - inf); i++)
		flag = insertStudent(ht, size, temp[i]);

	free(temp);

	return 1;
}

void main() {
	FILE* f;
	f = fopen("Studenti.txt", "r");

	char buffer[LINESIZE], seps[] = { ",\n" }, * token;
	struct Student s;

	struct Student* HTable; // variabila gestionare tabela de dispersie
	int size = ARRAY_SIZE; // dimensiune initiala tabela de dispersie

	HTable = (struct Student*)malloc(size * sizeof(struct Student));
	for (int i = 0; i < size; i++) {
		HTable[i].name = NULL; // nume folosit ca flag pentru semnalarea disponibilitatii la inserare
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

		// inserare student s in tabela de dispesie HTable
		char insert = insertStudent(HTable, size, s);
		int newSize = size;

		while (!insert) {
			struct Student* newHTable; // noua tabela de dispersie la realocare
			newSize += ARRAY_SIZE; // noua dimensiune a tabelei de dispersie la realocare
			newHTable = (struct Student*)malloc(newSize * sizeof(struct Student));

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL; // marcaj pozitie i disponibila la inserare
			}

			// mutarea elementelor (studenti) din vechea tabela pe noua tabela
			// obligatoriu, mutarea se efectueaza prin re-inserare elemente pe noua tabela
			insert = 1;
			for (int i = 0; i < size && insert; i++) {
				if (HTable[i].name)
					insert = insertStudent(newHTable, newSize, HTable[i]);
			}

			if (!insert) {
				free(newHTable); // esec inserare element HTable[i-1] in noua tabela newHTable
			}
			else {
				// elemente mutate cu succes pe noua tabela
				free(HTable); // dezalocare tabela veche/initiala

				HTable = newHTable; // comutare HTable pe noul vector/tabela
				size = newSize; // update dimensiune tabela

				insert = insertStudent(HTable, size, s);
			}
		}
	}

	printf("\n Continut tabela de dispersie (dimensiune %d):\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	char studName[] = { "Popescu Gigel" };

	int pozitie = searchStudent(HTable, size, studName);
	if (pozitie >= 0)
		printf("Student cautat: %d %s \n", HTable[pozitie].id, HTable[pozitie].name);
	else
		printf("Stundetul %s nu a fost gasit in tabela\n", studName);

	char deleted = deleteStudent(HTable, size, studName);

	printf("\n Tabela de dispesie dupa stergere %d elemente:\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %d %s\n", i, HTable[i].id, HTable[i].name);
		}
	}

	fclose(f);
}