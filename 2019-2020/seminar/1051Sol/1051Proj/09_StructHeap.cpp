#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LINESIZE 128
#define DIM 100

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodHeap {
	Student stud;
	int key;
};

void filtrare_bottom_up(NodHeap* sHeap, int nr_noduri)
{
	int offset_nod_curent = nr_noduri - 1;
	int offset_nod_parinte = (offset_nod_curent - 1) / 2;

	while ((offset_nod_curent != 0) && (sHeap[offset_nod_curent].key > sHeap[offset_nod_parinte].key))
	{
		int auxt;
		char* numet;
		char grupat[5];

		// interschimb noduri sHeap[offset_nod_curent] si sHeap[offset_nod_parinte]
		auxt = sHeap[offset_nod_curent].stud.id;
		sHeap[offset_nod_curent].stud.id = sHeap[offset_nod_parinte].stud.id;
		sHeap[offset_nod_parinte].stud.id = auxt;

		numet = sHeap[offset_nod_curent].stud.nume;
		sHeap[offset_nod_curent].stud.nume = sHeap[offset_nod_parinte].stud.nume;
		sHeap[offset_nod_parinte].stud.nume = numet;

		strcpy(grupat, sHeap[offset_nod_curent].stud.nrGrupa);
		strcpy(sHeap[offset_nod_curent].stud.nrGrupa, sHeap[offset_nod_parinte].stud.nrGrupa);
		strcpy(sHeap[offset_nod_parinte].stud.nrGrupa, grupat);

		auxt = sHeap[offset_nod_curent].key;
		sHeap[offset_nod_curent].key = sHeap[offset_nod_parinte].key;
		sHeap[offset_nod_parinte].key = auxt;

		// actualizare offset_nod_curent
		offset_nod_curent = offset_nod_parinte;
		// recalculare offset_nod_parinte pentru a identifica noul nod parinte al nodului curent
		offset_nod_parinte = (offset_nod_curent - 1) / 2;
	}
}

NodHeap* inserare_nod_heap(NodHeap* sHeap, NodHeap new_nod, int &nr_noduri, int &capacitate)
{
	if (nr_noduri == capacitate)
	{
		// nu exista loc de inserat in structura heap sHeap
		// realocare structura pe dimensiune mai mare
		capacitate += DIM;
		NodHeap* newStructHeap = (NodHeap*)malloc(sizeof(NodHeap) * capacitate);

		// copiere elemente din vechea structura in noua structura
		for (int i = 0; i < nr_noduri; i++)
		{
			newStructHeap[i].stud.id = sHeap[i].stud.id;
			newStructHeap[i].stud.nume = sHeap[i].stud.nume;
			strcpy(newStructHeap[i].stud.nrGrupa, sHeap[i].stud.nrGrupa);
			newStructHeap[i].key = sHeap[i].key;
		}

		// dezalocare structura Heap veche (incarcata la capacitate maxima)
		free(sHeap);
		// actualizare sHeap pentru preluarea noii structuri
		sHeap = newStructHeap;
	}

	// copiere nod nou pe ultima pozitie in vectorul suport la Structurii Heap
	sHeap[nr_noduri].stud.id = new_nod.stud.id;
	sHeap[nr_noduri].stud.nume = new_nod.stud.nume;
	strcpy(sHeap[nr_noduri].stud.nrGrupa, new_nod.stud.nrGrupa);
	sHeap[nr_noduri].key = new_nod.key;
	
	// incrementare nur efectiv de noduri in Structura Heap
	nr_noduri += 1;

	// aplicare procedura filtrare bottom-up
	filtrare_bottom_up(sHeap, nr_noduri);

	return sHeap;
}

// TEMA: stergere nod din Structura Heap


void main() {

	NodHeap* sHeap; // vectorul care stocheaza elementele din structura Heap
	NodHeap new_nod;

	int capacitate_stocare = DIM;
	int nr_noduri_heap = 0;

	// alocare spatiu vector suport pentru structura Heap
	sHeap = (NodHeap*)malloc(sizeof(NodHeap) * capacitate_stocare);

	FILE * f;
	f = fopen("StudHeap.txt", "r");
	char studBuff[20];

	char * token, file_buf[LINESIZE], sep_list[] = ",";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		new_nod.stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		new_nod.stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(new_nod.stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(new_nod.stud.nrGrupa, token);

		token = strtok(NULL, sep_list);
		new_nod.key = atoi(token);

		// inserare Student in Structura Heap 
		sHeap = inserare_nod_heap(sHeap, new_nod, nr_noduri_heap, capacitate_stocare);

		new_nod.stud.nume = NULL;
	}

	// afisare Structura Heap pentru validare continut
	int nivel = 0;
	for (int i = 0; i < nr_noduri_heap; i++)
	{
		if ((i + 1) == pow(2, nivel))
		{
			printf("\n");
			nivel += 1;
		}
		printf(" %d ", sHeap[i].key);
	}

	printf("\n\n");

	fclose(f);

}