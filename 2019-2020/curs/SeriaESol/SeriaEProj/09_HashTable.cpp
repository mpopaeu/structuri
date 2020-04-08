
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
	int pos = positionHashFunction(s.name, size);
	printf("Position: %d for %s\n", pos, s.name); // cheie de cautare: nume student; afisare de control cu privire la rezultatul functiei hash

	// search the first available starting with pos
	char inserted = 0; // flag for insertion 

					   // look for first available position in hash table
					   // starting with pos and till size
	for (int i = pos; i<size && !inserted; i++) {
		if (ht[i].name == NULL) {
			ht[i] = s;
			inserted = 1;
		}
	}

	return inserted;
}

// search a student using its name
int searchStudent(Student* ht, int size, char* studName)
{
	int pos = positionHashFunction(studName, size);
	char found = 0;
	for (int i = pos; i<size && !found; i++)
	{
		if (ht[i].name == 0)
			found = -1; // end of the cluster
		else if (strcmp(ht[i].name, studName) == 0)
		{
			found = 1;
			pos = i;
		}
	}

	if (found == 1)
		return pos; // student found within the hash table
	else
		return -1; // student not found
}

void main() {
	FILE* f;
	f = fopen("Students.txt", "r");

	char buffer[LINESIZE], seps[] = { "," }, *token;
	Student s;

	// define the hash table
	Student * HTable;
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

		printf("%d %s\n", s.id, s.name); // afisare de control cu privire la continut student incarcat din fisierul text

		// insert a student into my hash table
		char insert = insertStudent(HTable, size, s);
		int newSize = size;

		while (!insert) {
			// extindere tabela de dispersie
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
			printf("Position: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	// cautare student dupa nume
	char numeStudent[] = "Popa Marius";
	int pozTabela = searchStudent(HTable, size, numeStudent);
	if (pozTabela != -1)
		printf("Student identificat pe pozitia %d in tabela: %d %s\n\n", pozTabela, HTable[pozTabela].id, HTable[pozTabela].name);
	else
		printf("Studentul nu este in tabela de dispersie.\n\n");
}