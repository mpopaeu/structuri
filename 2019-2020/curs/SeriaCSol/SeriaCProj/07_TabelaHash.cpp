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
	printf("Position: %d for %s\n", pos, s.name);

	// search the first available starting with pos
	char inserted = 0; // flag for insertion 

					   // look for first available position in hash table
					   // starting with pos and till size
	for (int i = pos; i<size && !inserted; i++) {
		if (ht[i].name == NULL) { // pozitia i disponibila pentru inserare student s
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

// delete a student in hash table using linear probing
char deleteStudent(Student* ht, int size, char* studName)
{
	// cauta pozitia finala a studentului in tabela hash
	int poz = searchStudent(ht, size, studName);
	if (poz == -1)
		return 0; // nu exista studentul cautat in tabela de dispersie
				  // stergerea nu are loc

				  // "stergere" student
	free(ht[poz].name);
	ht[poz].name = NULL; // pozitia se disponibilizeaza la inserare
	int inf, sup; // capete ale cluster-ului in care se sterge

				  // determinare limita inferioara cluster
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

	// determinare limita superioara cluster
	flag = 0;
	for (int i = poz + 1; i<size && !flag; i++)
		if (ht[i].name == 0)
		{
			flag = 1;
			sup = i - 1;
		}
	if (!flag)
		sup = size - 1;

	// alocare vector temporar salvare studenti din cele 2 subclustere
	// formate de stergere student
	Student* temp = (Student*)malloc(sizeof(Student)*(sup - inf));
	int  j = 0;
	for (int i = inf; i<poz; i++)
	{
		temp[j++] = ht[i]; // mutare element din cluster in vector temporar
		ht[i].name = 0; // disponibilizare pozitie in tabela hash
	}
	for (int i = poz + 1; i <= sup; i++)
	{
		temp[j++] = ht[i]; // mutare element din cluster in vector temporar
		ht[i].name = 0; // disponibilizare pozitie in tabela hash
	}

	// reinserare studenti in tabela de dispersie
	// foarte posibil ordine diferita in functie de punctele de coliziune
	for (int i = 0; i < (sup - inf); i++)
		flag = insertStudent(ht, size, temp[i]);
	// dezalocarevector temporar
	free(temp);

	return 1; // stergere efectuata
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
	for (unsigned int i = 0; i<size; i++) {
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
			// extindere tabela de dispersie
			// realocare vector nou pe dimensiune mai mare
			Student *newHTable;
			newSize += ARRAY_SIZE;
			newHTable = (Student*)malloc(newSize * sizeof(Student)); // alocare vector nou pe dimensiune noua

			for (int i = 0; i<newSize; i++) {
				newHTable[i].name = NULL; // marchez toate elementele ca fiind disponibila la inserare
			}

			// mutare elemente in noua tabela
			// inserare studenti in noua tabela pe noua dimensiune
			insert = 1;
			for (int i = 0; i<size && insert; i++) {
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
	for (unsigned int i = 0; i<size; i++) {
		if (HTable[i].name) {
			printf("Position: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	char numeCautat[] = "Marius Popa";
	int pozStudent = searchStudent(HTable, size, numeCautat);
	if (pozStudent != -1) {
		// student gasit in tabela de dispersie
		printf("\n\n Student identificat pe pozitia %d: %d %s\n", pozStudent, HTable[pozStudent].id, HTable[pozStudent].name);
	}
	else {
		// studentul nu a fost gasit in tabela de dispersie
		printf("\n\n Studentul %s nu exista in tabela de dispersie!\n", numeCautat);
	}

	
	// delete a student in hash table
	char studName[] = { "Georgescu Alexandru" };
	char deleted = deleteStudent(HTable, size, studName);

	// parsing entire hash table for content validation
	printf("\n Hash table content after deletion:\n", size);
	for (unsigned int i = 0; i<size; i++) {
		if (HTable[i].name) {
			printf("Position: %d, Student: %d %s\n", i, HTable[i].id, HTable[i].name);
		}
	} 

	// dezalocare tabela de dispersie
	for (unsigned int i = 0; i<size; i++) {
		if (HTable[i].name) {
			free(HTable[i].name); // dezalocare nume student
		}
	}
	free(HTable); // dezalocare vector suport pentru tabela de dispersie
	HTable = NULL;

	fclose(f);
}