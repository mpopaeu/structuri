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
	int pos = positionHashFunction(s.name, size); // functia hash -> offset/pozitie initiala ocupata in vector
	printf("Position: %d for %s\n", pos, s.name);

	char inserted = 0;

	for (int i = pos; i < size && !inserted; i++) {
		if (ht[i].name == NULL) {
			ht[i] = s; // i este pozitia reala pe care se va stoca studentul s in tabela hash
			inserted = 1; // flag pentru fortare iesire din do-for
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
		if (ht[i].name == 0) // ht[i].name == NULL
			found = -1;
		else if (strcmp(ht[i].name, studName) == 0)
		{
			found = 1; // alternative la chei de cautare cu valori posibil duplicate in tabela de dispersie
					   // ex: lista simpla (de studenti, de adrese la studenti)
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
	int poz = searchStudent(ht, size, studName); // pozitie reala in tabela de dispersie
	if (poz == -1)
		return 0;

	free(ht[poz].name); // dezalocare nume student
	ht[poz].name = 0;	// sau NULL; disponibilizare pozitie poz la inserare in tabela hash
	int inf, sup;

	char flag = 0;
	for (int i = poz - 1; i >= 0 && !flag; i--) // cautare limita inferioara sub-cluster stanga (inf)
	{
		if (ht[i].name == 0)
		{
			flag = 1;
			inf = i + 1;
		}
	}
	if (!flag)
		inf = 0; // daca flag este nul, atunci inf este primul offset din tabela hash

	flag = 0;
	for (int i = poz + 1; i < size && !flag; i++) // cautare limita superioara sub-cluster dreapta
		if (ht[i].name == 0)
		{
			flag = 1;
			sup = i - 1;
		}
	if (!flag)
		sup = size - 1; // daca flag este nul, atunci sup este ultimul offset din tabela hash

	struct Student* temp = (struct Student*)malloc(sizeof(struct Student) * (sup - inf));
	int  j = 0;
	for (int i = inf; i < poz; i++)
	{
		temp[j++] = ht[i]; // mutare date din tabela hash in temp (subcluster stanga)
		ht[i].name = 0;    // disponibilizez pozitie i in vederea ocuparii mai tarziu la reinserare din temp
	}
	for (int i = poz + 1; i <= sup; i++)
	{
		temp[j++] = ht[i]; // mutare date din tabela hash in temp (subcluster dreapta)
		ht[i].name = 0;	   // // disponibilizez pozitie i in vederea ocuparii mai tarziu la reinserare din temp
	}

	for (int i = 0; i < (sup - inf); i++) // elementele din vectorul temporar temp
		flag = insertStudent(ht, size, temp[i]); // reinserare element din temp in tabela hash

	free(temp); // dezalocare vector temporar

	return 1;
}

void main() {
	FILE* f;
	f = fopen("Studenti.txt", "r");

	char buffer[LINESIZE], seps[] = { ",\n" }, * token;
	struct Student s;

	struct Student* HTable;
	int size = ARRAY_SIZE;

	HTable = (struct Student*)malloc(size * sizeof(struct Student)); // vectorul suport pentru tabela hash
	for (int i = 0; i < size; i++) {
		HTable[i].name = NULL; // name este flag pentru pozitie disponibila/ocupata la inserare student
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

		char insert = insertStudent(HTable, size, s);
		int newSize = size;

		while (!insert) { // ma asigur ca mutarea datelor din tabela veche + inserare lui s cu succes
			struct Student* newHTable;
			newSize += ARRAY_SIZE;
			newHTable = (struct Student*)malloc(newSize * sizeof(struct Student));

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL;
			}

			insert = 1;
			// mutare elemente din tabela veche pe tabela noua prin re-inserare elemente student
			for (int i = 0; i < size && insert; i++) { // parsare tabela hash veche in intregime
				if (HTable[i].name)
					insert = insertStudent(newHTable, newSize, HTable[i]); // HTable[i] student in tabela veche
			}

			if (!insert) {
				free(newHTable); // dezalocare tabela noua deoarece mutarea elementelor din tabela veche a esuat
			}
			else {
				free(HTable); // dezalocare tabela hash veche

				HTable = newHTable; // comutare variabila tabela hash pe noua tabela hash
				size = newSize; // update dimensiune catre lungime tabela hash noua

				insert = insertStudent(HTable, size, s); // incercare noua de inserare student s in tabela hash
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
	char gasit = searchStudent(HTable, size, studName);
	if (gasit >= 0)
	{
		printf("\nStudentul a fost identificat in tabela de dispersie: %d %s!\n", 
				HTable[gasit].id, HTable[gasit].name);
	}
	else
	{
		printf("\nStudentul nu a fost gasit in tabela de dispersie!\n");
	}

	char deleted = 1;
	
	while (deleted)
	{
		deleted = deleteStudent(HTable, size, studName);
	}

	gasit = searchStudent(HTable, size, studName);
	if (gasit >= 0)
	{
		printf("\nStudentul a fost identificat in tabela de dispersie: %d %s!\n",
			HTable[gasit].id, HTable[gasit].name);
	}
	else
	{
		printf("\nStudentul nu a fost gasit in tabela de dispersie!\n");
	}

	// dezalocare tabela de dispersie
	for (unsigned int i = 0; i < (unsigned int)size; i++)
	{
		if (HTable[i].name != NULL)
			free(HTable[i].name);
	}

	free(HTable);
	HTable = NULL;

	fclose(f);
}