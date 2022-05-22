#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

// Definire structuri 

struct Student {
	int id;
	char* name;
	float avg;
};

struct NodAVL {
	struct Student stud;
	signed char GE;
	struct NodAVL* st, * dr;
};

typedef struct Student Student;
typedef struct NodAVL NodAVL;

#define LINESIZE 128

// maximul a doi intregi
int maxim(int a, int b) {
	return a > b ? a : b;
}


// inaltime (sub)arbore r
int h(NodAVL* r) {
	if (r)
		return 1 + maxim(h(r->st), h(r->dr));
	else
		return 0;
}


// gradul de echilibru al unui nod
void calculGENod(NodAVL* r) {
	if (r) {
		//prelucrare (calcul GE)
		r->GE = h(r->dr) - h(r->st);
	}
}


// rotire simpla la dreapta
NodAVL* rotireSimplaDr(NodAVL* pivot, NodAVL* fiuSt) {
	pivot->st = fiuSt->dr;
	calculGENod(pivot);
	fiuSt->dr = pivot;
	calculGENod(fiuSt);

	return fiuSt;
}

// rotire simpla la stanga
NodAVL* rotireSimplaSt(NodAVL* pivot, NodAVL* fiuDr) {
	pivot->dr = fiuDr->st;
	calculGENod(pivot);
	fiuDr->st = pivot;
	calculGENod(fiuDr);

	return fiuDr;
}

// rotire dubla stanga-dreapta
NodAVL* rotireDblStDr(NodAVL* pivot, NodAVL* fiuSt) {
	//aducerea dezechilibrului pe aceeasi directie
	pivot->st = rotireSimplaSt(fiuSt, fiuSt->dr);
	calculGENod(pivot);
	fiuSt = pivot->st;
	//rotire propriu-zisa in pivot
	fiuSt = rotireSimplaDr(pivot, fiuSt);
	calculGENod(fiuSt);

	return fiuSt;
}

// rotire dubla dreapta-stanga
NodAVL* rotireDblDrSt(NodAVL* pivot, NodAVL* fiuDr) {
	// aducerea dezechilibrului pe aceeasi directie
	pivot->dr = rotireSimplaDr(fiuDr, fiuDr->st);
	calculGENod(pivot);
	fiuDr = pivot->dr;
	// rotire propriu-zisa in pivot
	fiuDr = rotireSimplaSt(pivot, fiuDr);
	calculGENod(fiuDr);

	return fiuDr;
}

// inserare nod in AVL
NodAVL* insNodAVL(NodAVL* r, Student s, unsigned char* err) {
	if (r) {
		if (r->stud.id > s.id)
			r->st = insNodAVL(r->st, s, err);
		else
			if (r->stud.id < s.id)
				r->dr = insNodAVL(r->dr, s, err);
			else
				*err = 0;
	}
	else {
		NodAVL* nou;
		nou = (NodAVL*)malloc(sizeof(NodAVL));
		nou->stud = s;
		nou->st = NULL;
		nou->dr = NULL;
		r = nou;

		*err = 1;
	}

	// recalculez grad de echilibru pt nodul curent
	calculGENod(r);
	if (r->GE == 2) {
		if (r->dr->GE == -1) {
			//dezechilibru dreapta-stanga
			r = rotireDblDrSt(r, r->dr);
		}
		else {
			//dezechilibru dreapta
			r = rotireSimplaSt(r, r->dr);
		}
	}
	else {
		if (r->GE == -2) {
			if (r->st->GE == 1) {
				//dezechilibru combinat stanga-dreapta
				r = rotireDblStDr(r, r->st);
			}
			else {
				//dezechilibru stanga
				r = rotireSimplaDr(r, r->st);
			}
		}
	}

	return r;
}


// traversare AVL inordine
void InordineAVL(NodAVL* rAVL) {
	if (rAVL) {
		InordineAVL(rAVL->st);
		printf("\n[%d %d] ", rAVL->stud.id, rAVL->GE);
		InordineAVL(rAVL->dr);
	}
}

void main() {
	FILE* f;
	f = fopen("Students.txt", "r");

	char buffer[LINESIZE], seps[] = { "," }, * token;
	struct Student s;
	NodAVL* root = NULL;

	while (fgets(buffer, LINESIZE, f)) {
		token = strtok(buffer, seps);
		s.id = atoi(token);

		token = strtok(NULL, seps);
		s.name = (char*)malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(s.name, token);

		token = strtok(NULL, seps);
		s.avg = (float)atof(token);

		unsigned char err;
		root = insNodAVL(root, s, &err);
		if (!err)
		{
			printf("\nStudentul %hu NU a fost inserat!", s.id);
			free(s.name);
		}
	}

	printf("\nArbore AVL dupa creare:");
	InordineAVL(root);
}