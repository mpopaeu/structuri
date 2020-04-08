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
	// convert string representation into numerical
	for (int i = 0; i<strlen(str); i++)
		sum += str[i];

	// valid position in my array (hash table)
	return sum % size;
}

// returns insertion success / failure
char insertStudent(Student* ht, int size, Student s) {
	// calculate the position to be used by storing the student
	int pos = positionHashFunction(s.name, size); // functie hash aplicata pe cheia de cautare (nume student)
	printf("Position: %d for %s\n", pos, s.name);

	// search the first available starting with pos
	char inserted = 0; // flag for insertion 

					   // look for first available position in hash table
					   // starting with pos and till size
	for (int i = pos; i<size && !inserted; i++) {
		if (ht[i].name == NULL) { // ht[i] inseamna un Student; verific daca name este NULL (i disponibil la inserare)
			ht[i] = s;
			inserted = 1;
		}
	}

	return inserted;
}


void main() {
	FILE* f;
	f = fopen("Students.txt", "r");

	char buffer[LINESIZE], seps[] = { "," }, *token;
	Student s;

	// define the hash table
	Student * HTable; // vector alocat la run-time
	int size = ARRAY_SIZE;

	// allocation of the hash table
	HTable = (Student*)malloc(size * sizeof(Student));
	for (unsigned int i = 0; i < size; i++) {
		HTable[i].name = NULL; // initially, the all positions are marked as "available"
	}


	while (fgets(buffer, LINESIZE, f)) {
		token = strtok(buffer, seps);
		s.id = atoi(token);

		token = strtok(NULL, seps); // save the next token (name)
		s.name = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(s.name, token);

		token = strtok(NULL, seps);
		s.avg = atof(token);

		printf("%d %s\n", s.id, s.name);

		// insert a student into my hash table
		char insert = insertStudent(HTable, size, s);
		int newSize = size;

		while (!insert) {
			// extindere tabela de dispersie (creare vector nou mai mare)
			// realocare vector nou pe dimensiune mai mare
			Student *newHTable;
			newSize += ARRAY_SIZE;
			newHTable = (Student*)malloc(newSize * sizeof(Student));

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL;
			}

			// mutare elemente in noua tabela
			// inserare studenti in noua tabela pe noua dimensiune
			insert = 1;
			for (int i = 0; i < size && insert; i++) {
				if (HTable[i].name)
					insert = insertStudent(newHTable, newSize, HTable[i]);
			}

			if (!insert) {
				// inserare student esuata la mutarea datelor
				// din vechea tabela in noua tabela
				free(newHTable);
			}
			else {

				// sterge vechea tabela
				free(HTable);

				// actualizez noua tabela ca fiind cea curenta
				// (actualizez pointer la vector, actualizez size)
				HTable = newHTable;
				size = newSize;

				// inserare stud in noua tabela
				insert = insertStudent(HTable, size, s);
			}
		}
	}

	// parsing entire hash table for content validation
	printf("\n Hash table content (size %d):\n", size);
	for (unsigned int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Position: %d, Student: %s\n", i, HTable[i].name); // vizualizare clustere de studenti
		}
	}
}