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
	// 1. determinare pozitie in tabela de dispersie (vector)
	int pos = positionHashFunction(s.name, size);
	printf("Position: %d for %s\n", pos, s.name);

	char inserted = 0;// 0 - inserare nu are loc

	// 2. cautare prima pozitie disponibila pentru a stoca s
	for (int i = pos; i < size && !inserted; i++) {
		if (ht[i].name == NULL) {
			ht[i] = s; // scriere date student in tabela de dispersie pe pozitia calculata cu pas +1
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
		return 0; // studentul nu a fost identificat in tabela hash

	free(ht[poz].name); // dezalocare extensie a studentului in heap
	ht[poz].name = 0; // disponibilizez pozitia studentului pentru a fi ocupata mai tarziu de alt set de date
	int inf, sup;

	char flag = 0;
	for (int i = poz - 1; i >= 0 && !flag; i--)
	{
		// cautare limita inferioara sub-cluster stanga
		if (ht[i].name == 0)
		{
			flag = 1;
			inf = i + 1; // inf limita inferioara
		}
	}
	if (!flag)
		inf = 0;

	flag = 0;
	for (int i = poz + 1; i < size && !flag; i++)
		// cautare limita superioara sub-cluster dreapta
		if (ht[i].name == 0)
		{
			flag = 1;
			sup = i - 1; // sup limita superioara
		}
	if (!flag)
		sup = size - 1;

	// temp este vector temporar cu studentii din sub-clusterele stanga si dreapta pozitiei din care a fost sters studentul cautat
	struct Student* temp = (struct Student*)malloc(sizeof(struct Student) * (sup - inf));
	int  j = 0;
	// salvare studenti din subcluster stanga
	for (int i = inf; i < poz; i++)
	{
		temp[j++] = ht[i]; 
		ht[i].name = NULL; // pozitia este disponibilizata pentru inserare ulterioara
	}
	// salvare studenti din subcluster dreapta
	for (int i = poz + 1; i <= sup; i++)
	{
		temp[j++] = ht[i];
		ht[i].name = NULL; // pozitia este disponibilizata pentru inserare ulterioara
	}


	// reinserare elemente din vector temporar in tabela de dispersie pentru a pastra corect mecanismul linear probing
	// functia hash asigura ocuparea pozitiilor cuprinse in [inf, sup]
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

	struct Student* HTable; // pointer la vector suport al tabelei de dispersie
	int size = ARRAY_SIZE; // lungime initiala a tabelei de dispersie

	HTable = (struct Student*)malloc(size * sizeof(struct Student)); // alocare dinamica a vectorului suport
	for (int i = 0; i < size; i++) {
		HTable[i].name = NULL; // "disponibilizez" toate locatiile din vectorul suport al tabelei de dispersie
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

		char insert = insertStudent(HTable, size, s);
		int newSize = size;

		while (!insert) { // inserarea unui student nu a avut loc in tabela de dispersie
			struct Student* newHTable;
			newSize += ARRAY_SIZE;
			newHTable = (struct Student*)malloc(newSize * sizeof(struct Student)); // alocare vector suport nou pe lungime mai mare cu +ARRAY_SIZE

			for (int i = 0; i < newSize; i++) {
				newHTable[i].name = NULL; // marcaj elemente din noua tabela ca fiind disponibile la a fi ocupate cu date Student
			}

			insert = 1;
			// mutarea datelor (studentilor) din tabela curenta pe noua tabela mai mare
			// mutarea studentilor are loc prin reinserarea acestora in tablela noua: functia hash depinde de lungime tabela
			for (int i = 0; i < size && insert; i++) { // oprire loop la primul esec de reinserare
				if (HTable[i].name)
					insert = insertStudent(newHTable, newSize, HTable[i]);
			}

			if (!insert) {
				free(newHTable); // dezalocare noua tabela de dispersie deoarece nu s-au mutat toate elementele
			}
			else {
				// elementele au fost mutate integral din tabela curenta (HTable, size) in tabela noua (newHTable, newSize)
				free(HTable); // dezalocare tabela curent

				HTable = newHTable; // comutare pointer la tabela hash pe noua tabela (newHTable)
				size = newSize; // comutare variabila size pe noua dimensiune tabela (newSize)

				insert = insertStudent(HTable, size, s); // noua incercare de a insera studentul care a declansat procesul de realocare a tabelei hash
			}
		}
	}

	// traversare secventiala a tabelei de dispersie (ne-recomandat!!!!)
	printf("\n Continut tabela de dispersie (dimensiune %d):\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %s\n", i, HTable[i].name);
		}
	}

	// limitare functie: pos_student este pozitia primei aparitii pentru Popescu Gigel""
	int pos_student = searchStudent(HTable, size, "Popescu Gigel");
	if (pos_student != -1)
	{
		printf("Student identificat: %d, %f\n", HTable[pos_student].id, HTable[pos_student].avg);
	}
	else
	{
		printf("Studentul nu a fost identificat in tabela de dispersie!\n");
	}

	char studName[] = { "Popescu Gigel" };
	char deleted = deleteStudent(HTable, size, studName);

	// parsare secventiala doar din motive didactice!!!!
	// parsare secventiala permisa doar pentru campuri care nu au rol de CHEIE!!!
	printf("\n Tabela de dispesie dupa stergere: %d elemente\n", size);
	for (int i = 0; i < size; i++) {
		if (HTable[i].name) {
			printf("Pozitie: %d, Student: %d %s\n", i, HTable[i].id, HTable[i].name);
		}
	}

	fclose(f);
}