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
	int pos = positionHashFunction(s.name, size); // cheie de cautare alfanumerica (nume student)
	printf("Position: %d for %s\n", pos, s.name);

	char inserted = 0; // initial, status ESEC

	for (int i = pos; i < size && !inserted; i++) {
		if (ht[i].name == NULL) {
			// s-a gasit pozitie disponibila pentru inserarea lui s
			ht[i] = s; 
			inserted = 1; // comutare flag pe status SUCCES
		}
	}

	return inserted;
}


int searchStudent(struct Student* ht, int size, char* studName)
{
	int pos = positionHashFunction(studName, size); // cheie de cautare alfanumerica (nume student)
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

	free(ht[poz].name); // dezalocare nume student sters de pe pozitia reala poz
	ht[poz].name = 0; // disponibilizare pozitie poz pentru inserare viitoare
	int inf, sup; // se formeaza 2 sub-clustere: [inf, poz - 1], [poz + 1, sup]

	// determinare inf pentru sub-cluster stanga
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

	// determinare sup pentru sub-cluster dreapta
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
	// mutare elemente sub-cluster stanga [inf, poz - 1]
	int  j = 0;
	for (int i = inf; i < poz; i++)
	{
		temp[j++] = ht[i];
		ht[i].name = 0; // disponibilizare pozitie din sub-cluster stanga
	}
	// mutare elemente sub-cluster dreapta [poz + 1, sup]
	for (int i = poz + 1; i <= sup; i++)
	{
		temp[j++] = ht[i];
		ht[i].name = 0; // disponibilizare pozitie din sub-cluster dreapta
	}

	// re-inserare elemente in tabela de dispersie
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

	struct Student* HTable; // gestionare tabela hash - vector alocat la runtime
	int size = ARRAY_SIZE; // numar de elemente din tabela de dispersie

	HTable = (struct Student*)malloc(size * sizeof(struct Student));
	for (int i = 0; i < size; i++) {
		HTable[i].name = NULL; // flag pentru semnalare pozitie disponibila la inserare
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

		// inserare student in tabela de dispersie cu linear probing (pasul +1, pana la final de tabela)
		char insert = insertStudent(HTable, size, s);
		int newSize = size;

		while (!insert) {
			struct Student* newHTable; // noua tabela de dispersie
			newSize += ARRAY_SIZE;	// dimensiune noua tabela de dispersie
			newHTable = (struct Student*)malloc(newSize * sizeof(struct Student));

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL; // flag pozitii disponibile la inserare
			}

			insert = 1;
			for (int i = 0; i < size && insert; i++) { // traversare secvential a tabelei curente
				if (HTable[i].name)
					insert = insertStudent(newHTable, newSize, HTable[i]);
			}

			if (!insert) {
				free(newHTable); // dezalocare tabela noua in vederea re-alocarii pe o dim si mai mare
			}
			else {
				// elemente din tabela curenta mutate cu succes pe noua tabela

				// dezalocare tabela curenta
				free(HTable);

				// comutare HTable pe noua tabela
				HTable = newHTable;
				// comutare size pe noua dimensiune (mai mare)
				size = newSize;

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


	// cautare student in tabela de dispersie cu linear probing
	char studName[] = { "Popescu Gigel" };
	int pozitie = searchStudent(HTable, size, studName);
	if (pozitie != -1)
		printf("Student %s identificat: %d %.2f\n", studName, HTable[pozitie].id, HTable[pozitie].avg);
	else
		printf("Studentul %s nu exista in tabela de dispersie.\n", studName);


	// stergere student din tabela de dispersie
	char deleted = deleteStudent(HTable, size, studName);

	printf("\n Tabela de dispersie dupa stergere %d elemente:\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %d %s\n", i, HTable[i].id, HTable[i].name);
		}
	}

	fclose(f);
}