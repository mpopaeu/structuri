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
	if (ht != NULL) {
		// calculate the position to be used by storing the student
		int pos = positionHashFunction(s.name, size); // functie hash aplicata pe cheia de cautare (nume student)
		printf("Position: %d for %s\n", pos, s.name);

		// search the first available starting with pos
		char inserted = 0; // flag for insertion 

						   // look for first available position in hash table
						   // starting with pos and till size
		for (int i = pos; i < size && !inserted; i++) {
			if (ht[i].name == NULL) { // ht[i] inseamna un Student; verific daca name este NULL (i disponibil la inserare)
				ht[i] = s;
				inserted = 1;
			}
		}

		return inserted;
	}

	return -1; // nu exista tabela de dispersie
}


// search a student using its name
int searchStudent(Student* ht, int size, char* studName)
{
	if (ht) {
		int pos = positionHashFunction(studName, size);
		char found = 0;
		for (int i = pos; i < size && !found; i++)
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

	return -2; // nu exista tabela de dispersie
}

// delete a student in hash table using linear probing
char deleteStudent(Student* ht, int size, char* studName)
{
	if (ht != NULL) {
		// cauta pozitia finala a studentului in tabela hash
		int poz = searchStudent(ht, size, studName);
		if (poz == -1)
			return 0; // nu exista studentul cautat in tabela de dispersie
					  // stergerea nu are loc

		// "stergere" student
		free(ht[poz].name);
		ht[poz].name = 0; // pozitia se disponibilizeaza la inserare; stergere logica
		int inf, sup; // capete ale cluster-ului in care se sterge

		// determinare limita inferioara sub-cluster stanga
		char flag = 0;
		for (int i = poz - 1; i >= 0 && !flag; i--) // sub-cluster stanga lui poz [inf, poz - 1]
		{
			if (ht[i].name == 0)
			{
				flag = 1;
				inf = i + 1;
			}
		}
		if (!flag)
			inf = 0;

		// determinare limita superioara sub-cluster dreapta
		flag = 0;
		for (int i = poz + 1; i < size && !flag; i++) // sub-cluster dreapta lui poz [poz + 1, sup]
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
		for (int i = inf; i < poz; i++)
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

	return -1; // tabela nu exista 
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

	char nume_student[] = "Popescu Gigel";
	char sterg = deleteStudent(HTable, size, nume_student);
	// parsing entire hash table for content validation
	printf("\n Hash table content (size %d) after deletion:\n", size);
	for (unsigned int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Position: %d, Student: %s\n", i, HTable[i].name); // vizualizare clustere de studenti
		}
	}

	int pozStudent = searchStudent(HTable, size, nume_student);
	if (pozStudent != -1)
		// student identificat in tabela de dispersie
		printf("\n\n Student gasit pe pozitia %d: %d %s", pozStudent, HTable[pozStudent].id, HTable[pozStudent].name);
	else
		// studentul nu exista in tabela de dispersie
		printf("\n\n Studentul %s nu este in tabela de dispersie. \n", nume_student);


	// dezalocare tabela de dispersie
	for (unsigned int i = 0; i < size; i++) {
		if (HTable[i].name) {
			free(HTable[i].name); // dezalocare nume student (daca studentul este "valid" stocat in tabela de dispersie)
		}
	}
	free(HTable); // dezalocare vector de studenti
	HTable = NULL;

	pozStudent = searchStudent(HTable, size, nume_student);
	if (pozStudent >= 0)
		// student identificat in tabela de dispersie
		printf("\n\n Student gasit pe pozitia %d: %d %s", pozStudent, HTable[pozStudent].id, HTable[pozStudent].name);
	else
		if(pozStudent == -2)
			// tabela de dispersie nu exista
			printf("\n\n Structura tabela de dispersie inexistenta. \n");
		else
		// studentul nu exista in tabela de dispersie
		printf("\n\n Studentul %s nu este in tabela de dispersie. \n", nume_student);

	fclose(f);
}