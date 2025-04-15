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
		sum += str[i]; // insumare coduri ASCII pentru stringul str (cheie)

	return sum % size; // rezultatul este in interiorul zonei alocate pr vector suport tabela hash
}

char insertStudent(struct Student* ht, int size, struct Student s) {
	int pos = positionHashFunction(s.name, size); // functie hash aplicata pe nume student
	printf("Position: %d for %s\n", pos, s.name);

	char inserted = 0;

	for (int i = pos; i < size && !inserted; i++) {
		if (ht[i].name == NULL) {
			ht[i] = s; // scriere date s in tabela hash
			inserted = 1;
		}
	}

	return inserted; // 0 - nu a fost inserat, 1 - s a fost inserat
}


int searchStudent(struct Student* ht, int size, char* studName)
{
	int pos = positionHashFunction(studName, size); // pozitia pe care ar trebui sa fie stocat setul de date
	char found = 0;
	for (int i = pos; i < size && !found; i++)
	{
		if (ht[i].name == 0) // validare existenta set date pe offset i in tabela hash
			found = -1;
		else if (strcmp(ht[i].name, studName) == 0) // cautare in extenso pe cheia de cautare
		{
			found = 1;
			pos = i;
		}
	}

	if (found == 1)
		return pos; // date identificate in tabela hash pe offset pos (pozitie reala)
	else
		return -1; // datele cautate nu sunt in tabela hash
}


char deleteStudent(struct Student* ht, int size, char* studName)
{
	int poz = searchStudent(ht, size, studName);
	if (poz == -1)
		return 0; // studentul nu a fost identificat in tabela hash

	free(ht[poz].name); // dezalocare nume student
	ht[poz].name = 0; // disponibilize poz pentru inserari viitoare
	int inf, sup;

	char flag = 0;
	for (int i = poz - 1; i >= 0 && !flag; i--) // determinare limita inferioara sub-cluster stanga
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
	for (int i = poz + 1; i < size && !flag; i++) // cautare limita superioara sub-cluster dreapta
		if (ht[i].name == 0)
		{
			flag = 1;
			sup = i - 1;
		}
	if (!flag)
		sup = size - 1;

	struct Student* temp = (struct Student*)malloc(sizeof(struct Student) * (sup - inf)); // alocare vector temporar cu studenti din cele 2 sub-clustere
	int  j = 0;
	for (int i = inf; i < poz; i++) // copiere data din sub-cluster stanga in vector temp
	{
		temp[j++] = ht[i];
		ht[i].name = 0; // disponibilizare i in tabela hash
	}
	for (int i = poz + 1; i <= sup; i++) // copiere data din sub-cluster dreapta in vector temp
	{
		temp[j++] = ht[i];
		ht[i].name = 0; // disponibilizare i in tabela hash
	}
	
	// elemente cuprinse intre inf si sup sunt disponibile in a fi ocupate cu date la inserare in tabela hash

	for (int i = 0; i < (sup - inf); i++)
		flag = insertStudent(ht, size, temp[i]); // re-inserare date din temp in tabela de dispersie

	free(temp);

	return 1;
}

void main() {
	FILE* f;
	f = fopen("Studenti.txt", "r");

	char buffer[LINESIZE], seps[] = { ",\n" }, * token;
	struct Student s;

	struct Student* HTable; // pointer acces la tabela de dispersie
	int size = ARRAY_SIZE; // capacitate de stocare initiala a tabelei hash

	HTable = (struct Student*)malloc(size * sizeof(struct Student));
	for (int i = 0; i < size; i++) {
		HTable[i].name = NULL; // flag pentru marcare elemente disponibile la inserare
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

		char insert = insertStudent(HTable, size, s); // inserare student s in tabela hash; return flag inserare
		int newSize = size;

		while (!insert) {
			struct Student* newHTable;
			newSize += ARRAY_SIZE; // noua dimensiune a tabelei hash
			newHTable = (struct Student*)malloc(newSize * sizeof(struct Student));

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL; // initial, toate elementele de pe noua tabela sunt disponibile la inserare
			}

			// mutarea elementelor de pa tabela curenta pe noua tabela
			insert = 1;
			for (int i = 0; i < size && insert; i++) { // se parseaza (secvential) toate elementele din tabela curenta (HTable)
				if (HTable[i].name) // exista set de date stocat pe offset i in HTable
					insert = insertStudent(newHTable, newSize, HTable[i]); // re-inserare elemenet i din HTable pe newHTable
			}

			if (!insert) {
				free(newHTable); // mutarea elementelor de pe tabela curenta a esuat; se dezaloca noua tabela 
			}
			else { // mutarea tuturor elementelor a fost efectuata pe noua tabela newHTable
				free(HTable); // dezalocare tabela curenta

				HTable = newHTable; // comutare var HTable pe noua tabela
				size = newSize; // update lungime noua tabela; comutare size pe newSize

				insert = insertStudent(HTable, size, s); // noua tentativa de inserare s
			}
		}
	}

	printf("\n Continut tabela de dispersie (dimensiune %d):\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	int offs_stud = searchStudent(HTable, size, "Gigel opescuP");
	if (offs_stud != -1)
	{
		printf("Student identificat in tabela hash: %s %d\n", HTable[offs_stud].name, HTable[offs_stud].id);
	}
	else
	{
		printf("Studentul cautat nu exista in tabela hash!\n");
	}

	char studName[] = { "Popescu Gigel" };
	char deleted = deleteStudent(HTable, size, studName);

	printf("\n Tabela de dispesie dupa stergere: %d elemente\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %d %s\n", i, HTable[i].id, HTable[i].name);
		}
	}

	fclose(f);
}