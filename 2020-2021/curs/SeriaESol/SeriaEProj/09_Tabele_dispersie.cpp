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
	for (int i = 0; i<strlen(str); i++)
		sum += str[i];

	return sum % size;
}

char insertStudent(Student* ht, int size, Student s) {
	int pos = positionHashFunction(s.name, size); // apel functie pentru determinare pozitie in tabela hash (functia hash)
	printf("Position: %d for %s\n", pos, s.name);

	char inserted = 0;

	for (int i = pos; i<size && !inserted; i++) {
		if (ht[i].name == NULL) {
			ht[i] = s;
			inserted = 1;
		}
	}

	return inserted;
}


int searchStudent(Student* ht, int size, char* studName)
{
	int pos = positionHashFunction(studName, size); // pozitia initiala -> poate fi pozitie de coliziunea -> se cauta pozitia reala
	char found = 0;
	for (int i = pos; i<size && !found; i++)
	{
		if (ht[i].name == 0) // se termina cluster-ul -> se incheie op de cautare
			found = -1;
		else if (strcmp(ht[i].name, studName) == 0)
		{
			found = 1; // s-a identificat student in tabela hash
			pos = i; // pozitia reala pe care se afla studentul in tabela hash
		}
	}

	if (found == 1)
		return pos;
	else
		return -1;
}


char deleteStudent(Student* ht, int size, char* studName)
{
	int poz = searchStudent(ht, size, studName);
	if (poz == -1)
		return 0; // studentul nu a fost gasit in tabela hash

	free(ht[poz].name); // pozitia reala a studentului in tabela hash; dezalocare nume student
	ht[poz].name = NULL; // se disponibileaza pozitia reala a studentului
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
	for (int i = poz + 1; i<size && !flag; i++)
		if (ht[i].name == 0)
		{
			flag = 1;
			sup = i - 1;
		}
	if (!flag)
		sup = size - 1;

	Student* temp = (Student*)malloc(sizeof(Student)*(sup - inf)); // alocare vector suport pt stocare temporara studenti din cluster
	int  j = 0;
	for (int i = inf; i<poz; i++)
	{
		temp[j++] = ht[i]; // copiez studenti din tabela hash in vector suport temp pentru cluster 1
		ht[i].name = NULL; // disponibilizare pozitii din cluster 1
	}
	for (int i = poz + 1; i <= sup; i++)
	{
		temp[j++] = ht[i]; // copiez studenti din tabela hash in vector suport temp pentru cluster 2
		ht[i].name = NULL; // disponibilizare pozitii din cluster 2
	}

	for (int i = 0; i < (sup - inf); i++)
		flag = insertStudent(ht, size, temp[i]); // reinserare element i (student) din vector suport temo in tabela hash

	free(temp); // dezalocare vector suport

	return 1;
}

void main() {
	FILE* f;
	f = fopen("Students.txt", "r");

	char buffer[LINESIZE], seps[] = { ",\n" }, *token;
	Student s;

	Student * HTable; // tabela de dispersie/vector alocat la runtime
	int size = ARRAY_SIZE; // dimensiune initiala tabela de dispersie

	HTable = (Student*)malloc(size * sizeof(Student)); // alocare mem heap pentru vectorul suport
	for (unsigned int i = 0; i<size; i++) {
		HTable[i].name = NULL; // marcaj pentru a indica disponibilitate pozitie (i) la inserare in tabela hash
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

		char insert = insertStudent(HTable, size, s); // apel functie inserare student in tabela de dispersie
		int newSize = size;

		while (!insert) { // realocare tabela de dispersie pe zona mai mare (dimensiunea mai mare)
			Student *newHTable; // noua tabela de dispesie
			newSize += ARRAY_SIZE; // noua dimensiune a tabelei de dispersie
			newHTable = (Student*)malloc(newSize * sizeof(Student)); // alocare noua tabela de dispersie

			for (int i = 0; i<newSize; i++) {
				newHTable[i].name = NULL; // initializare elemente din noua tabela (marcate toate ca fiind disponibile pt inserare)
			}

			// copierea elementelor din vechea tabela in noua tabela
			insert = 1;
			for (int i = 0; i<size && insert; i++) { // traversare secventiala vechea tabela de dispersie
				if (HTable[i].name)
					insert = insertStudent(newHTable, newSize, HTable[i]); // "reinserarea" studentilor in noua tabela de dispersie
			}

			if (!insert) {
				free(newHTable); // noua tabela formeaza cluster de elemente pe final pe durata operatiei de copiere 
								// din tabela initiala
								// se dezaloca noua tabela de dispersie
								// se continua cu alocarea noii tabela pe o dimesiune si mai mare
			}
			else {
				// copiere cu succes a elementelor din tabela initiala HTable in noua tabela newHTable
				free(HTable); // se dezaloca tabela initiala

				HTable = newHTable; // actualizare var pointer catre noul vector suport (mai mare)
				size = newSize; // actualizare dimensiune pt noul vector suport 

				// noua tentativa de a insera setul de date s
				insert = insertStudent(HTable, size, s);
			}
		}
	}

	printf("\n Continut tabela de dispersie (dimensiune %d):\n", size);
	for (unsigned int i = 0; i<size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	char studName[] = { "Popescu Gigel" };
	char deleted = deleteStudent(HTable, size, studName);

	printf("\n Tabela de dispesie dupa stergere:\n", size);
	for (unsigned int i = 0; i<size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %d %s\n", i, HTable[i].id, HTable[i].name);
		}
	}

	fclose(f);
}