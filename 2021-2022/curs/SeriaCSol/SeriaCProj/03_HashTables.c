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

	fclose(f);
}
