#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LINESIZE 128
#define DIM_VECTOR 100

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodHeap {
	Student stud;
	int hKey;
};

void filtrareBottomUp(NodHeap* strHeap, int nrNoduri) {
	int offs_curent = nrNoduri - 1;
	int offs_parinte = (offs_curent - 1) / 2;
	while ((offs_parinte != offs_curent) && (strHeap[offs_parinte].hKey < strHeap[offs_curent].hKey)) {
		// conditia de max-heap nu este respectata

		// 1. interschimb continut noduri
		int auxt;
		char* numet;
		char grupat[5];
		// interschimb id-uri
		auxt = strHeap[offs_curent].stud.id;
		strHeap[offs_curent].stud.id = strHeap[offs_parinte].stud.id;
		strHeap[offs_parinte].stud.id = auxt;
		// interschimb nume studenti
		numet = strHeap[offs_curent].stud.nume;
		strHeap[offs_curent].stud.nume = strHeap[offs_parinte].stud.nume;
		strHeap[offs_parinte].stud.nume = numet;
		// interschimb nr grupa
		strcpy(grupat, strHeap[offs_curent].stud.nrGrupa);
		strcpy(strHeap[offs_curent].stud.nrGrupa, strHeap[offs_parinte].stud.nrGrupa);
		strcpy(strHeap[offs_parinte].stud.nrGrupa, grupat);
		// interschimb chei noduri
		auxt = strHeap[offs_curent].hKey;
		strHeap[offs_curent].hKey = strHeap[offs_parinte].hKey;
		strHeap[offs_parinte].hKey = auxt;

		// 2. actualizare offset element curent (care urca in arbore)
		offs_curent = offs_parinte;			// noul offset al elementului curent
		offs_parinte = (offs_curent - 1) / 2; // determinar offset pentru noul parinte
	}
}

//// TEMA: implementare filtrare top-down nod radacina
//void filtrareTopDown(NodHeap* strHeap, int nrNoduri) {
//}

NodHeap* inserareNodHeap(NodHeap* strHeap, NodHeap nodInserat, int &nrNoduri, int &capacitate) {
	if (nrNoduri == capacitate) {
		// nu mai este spatiu in strHeap pentru a face inserare unui nou nod
		// realocare strHeap pe o capcitate extinsa cu 100 elemente
		capacitate += DIM_VECTOR;
		NodHeap* strNewHeap = (NodHeap*)malloc(sizeof(NodHeap) * capacitate);

		// copiere elemente din vechea structura heap (la capacitate maxim) in nou structura
		for (int i = 0; i < nrNoduri; i++) {
			strNewHeap[i].stud.id = strHeap[i].stud.id;
			strNewHeap[i].stud.nume = strHeap[i].stud.nume;
			strcpy(strNewHeap[i].stud.nrGrupa, strHeap[i].stud.nrGrupa);
			strNewHeap[i].hKey = strHeap[i].hKey;
		}

		// dezalocare vector la capacitate maxim
		free(strHeap);
		// actualizare structura/vector cu noua adresa de vector cu capacitate marita
		strHeap = strNewHeap;
	}

	// strHeap[nrNoduri] = nodInserat;
	strHeap[nrNoduri].stud.id = nodInserat.stud.id;
	strHeap[nrNoduri].stud.nume = nodInserat.stud.nume;
	strcpy(strHeap[nrNoduri].stud.nrGrupa, nodInserat.stud.nrGrupa);
	strHeap[nrNoduri].hKey = nodInserat.hKey;

	nrNoduri += 1;

	filtrareBottomUp(strHeap, nrNoduri);

	return strHeap;
}
//
//// TEMA: implementare operatie stergere nod in structura heap
//Student stergereNodHeap(NodHeap* strHeap, int &nrNoduri) {
//	// interschimb primul cu ultimul nod
//
//	// salvare student din ultimul nod in variabila locala pe care o returnam in apelator
//
//	// decrementare nrNoduri
//
//	// filtrare top-down
//
//	// returneaza student din variabila locala
//}
//

void main() {

	NodHeap * vHeap;
	NodHeap nodStud;

	int capacitate = DIM_VECTOR;
	// alocare spatiu tabela de dispersie
	vHeap = (NodHeap*)malloc(sizeof(NodHeap) * capacitate);
	// numarul de noduri existent in structura arbore Heap
	int nrNoduri = 0;
	

	FILE * f;
	f = fopen("StudHeap.txt", "r");
	char studBuff[20];

	char * token, file_buf[LINESIZE], sep_list[] = ",";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		nodStud.stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		nodStud.stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(nodStud.stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(nodStud.stud.nrGrupa, token);

		token = strtok(NULL, sep_list);
		nodStud.hKey = atoi(token);

		// inserare Student in structura Heap
		inserareNodHeap(vHeap, nodStud, nrNoduri, capacitate);

		nodStud.stud.nume = NULL; // evitare partajare zona heap pentru nume student
	}

	// afisare structura heap
	int nivel = 0;
	for (int i = 0; i < nrNoduri; i++) {
		if ((i + 1) == pow(2, nivel)) {
			printf("\n");
			nivel += 1;
		}
		printf("%d ", vHeap[i].hKey);
	}
	printf("\n");

	fclose(f);
}