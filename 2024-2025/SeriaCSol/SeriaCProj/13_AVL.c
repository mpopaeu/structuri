
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


struct  Student {
	int id;
	char* nume;
	float medie;
};

struct NodAVL {
	struct Student stud;
	int GE;
	struct NodAVL* st, * dr;
};

typedef struct Student Student;
typedef struct NodAVL NodAVL;


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
	pivot->st = fiuSt->dr; // stanga pivotului devine subarbore Y (vezi curs)
	calculGENod(pivot);	   // recalculare GE pivot
	fiuSt->dr = pivot;     // fiul pivotului promoveaza (dreapta devine pivot) pe nivel superior
	calculGENod(fiuSt);    // recalculare GE fiu al pivotului

	return fiuSt;
}

// rotire simpla la stanga
NodAVL* rotireSimplaSt(NodAVL* pivot, NodAVL* fiuDr) {
	pivot->dr = fiuDr->st; // dreapta pivot devine subarbore Y
	calculGENod(pivot);
	fiuDr->st = pivot;     // fiul pivotului promoveaza (stanga sa devine pivot) pe nivel superior
	calculGENod(fiuDr);

	return fiuDr;
}

// rotire dubla stanga-dreapta
NodAVL* rotireDblStDr(NodAVL* pivot, NodAVL* fiuSt) {
	//aducerea dezechilibrului pe aceeasi directie
	pivot->st = rotireSimplaSt(fiuSt, fiuSt->dr); // rotire de pregatire (efectuata in fiu stanga al pivotului care devine pivot la rotirea #1)
	calculGENod(pivot);
	fiuSt = pivot->st; // actualizare fiu stanga al pivotului
	//rotire propriu-zisa in pivot
	fiuSt = rotireSimplaDr(pivot, fiuSt); // dezechilibrul este pe aceeasi directie
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
NodAVL* insNodAVL(NodAVL* r, Student s, int* err) {
	if (r) {
		if (r->stud.id > s.id)
			r->st = insNodAVL(r->st, s, err);
		else
			if (r->stud.id < s.id)
				r->dr = insNodAVL(r->dr, s, err);
			else
				*err = 1;
	}
	else {
		NodAVL* nou;
		nou = (NodAVL*)malloc(sizeof(NodAVL));
		nou->stud = s;
		nou->st = NULL;
		nou->dr = NULL;
		r = nou;
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
		printf(" %d %d ", rAVL->stud.id, rAVL->GE);
		InordineAVL(rAVL->dr);
	}
}

int main() {

	return 0;
}