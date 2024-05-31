#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	float medie; // data derivata
};

struct NodAVL {
	struct Student s;
	char GE;
	struct NodAVL* st, * dr;
};

// maximul a doi intregi
int maxim(int a, int b) {
	return a > b ? a : b;
}

// inaltime (sub)arbore r
int h(struct NodAVL* r) {
	if (r)
		return 1 + maxim(h(r->st), h(r->dr));
	else
		return 0;
}


// gradul de echilibru al unui nod
void calculGENod(struct NodAVL* r) {
	if (r) {
		//prelucrare (calcul GE)
		r->GE = h(r->dr) - h(r->st);
	}
}


// rotire simpla la dreapta
struct NodAVL* rotireSimplaDr(struct NodAVL* pivot, struct NodAVL* fiuSt) {
	pivot->st = fiuSt->dr;
	calculGENod(pivot);
	fiuSt->dr = pivot;
	calculGENod(fiuSt);

	return fiuSt;
}

// rotire simpla la stanga
struct NodAVL* rotireSimplaSt(struct NodAVL* pivot, struct NodAVL* fiuDr) {
	pivot->dr = fiuDr->st;
	calculGENod(pivot);
	fiuDr->st = pivot;
	calculGENod(fiuDr);

	return fiuDr;
}

// rotire dubla stanga-dreapta
struct NodAVL* rotireDblStDr(struct NodAVL* pivot, struct NodAVL* fiuSt) {
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
struct NodAVL* rotireDblDrSt(struct NodAVL* pivot, struct NodAVL* fiuDr) {
	// aducerea dezechilibrului pe aceeasi directie
	pivot->dr = rotireSimplaDr(fiuDr, fiuDr->st);
	calculGENod(pivot);
	fiuDr = pivot->dr;
	// rotire propriu-zisa in pivot
	fiuDr = rotireSimplaSt(pivot, fiuDr);
	calculGENod(fiuDr);

	return fiuDr;
}



struct NodAVL* inserare(struct NodAVL* r, struct Student st, int* er)
{
	if (r == NULL) {
		struct NodAVL* nou = (struct NodAVL*)malloc(sizeof(struct NodAVL));
		nou->dr = NULL;
		nou->st = NULL;
		nou->s = st;
		r = nou;
	}
	else if (r->s.id == st.id) *er = 1;
	else if (r->s.id > st.id)
		r->st = inserare(r->st, st, er);
	else
		r->dr = inserare(r->dr, st, er);

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

void TraversareInordine(struct NodAVL* r)
{
	if (r) {
		TraversareInordine(r->st);
		printf("\n%d %s %d\n", r->s.id, r->s.nume, r->GE);
		TraversareInordine(r->dr);
	}
}

struct NodAVL* DezalocareArboreBinCautare(struct NodAVL* r)
{
	if (r) {
		TraversareInordine(r->st);
		TraversareInordine(r->dr);

		// dezalocare nod curent r
		free(r->s.nume); // dezalocare nume student stocat in nod r
		free(r);		// dezalocare nod din ABC

		r = NULL;	// actualizare continut nod curent r dupa dezalocare lui r
	}

	return r;
}

void main() {

	struct Student stud;
	struct NodAVL* root = NULL;

	FILE* f;
	f = fopen("Studenti.txt", "r");

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		stud.medie = (float)atof(token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		// inserare student in ABC
		int err = 0;
		// float test = 0; // test cu parametrul 3 ca referinta
		root = inserare(root, stud, &err);
		if (err) {
			printf("\nStudentul cu id %d exista in arbore.\n", stud.id);
			free(stud.nume);
		}
		else
			printf("\nStudentul %s a fost inserat\n", stud.nume);
	}

	fclose(f);

	// traversare in inordine (ordine crescatoare id-uri studenti)
	printf("\nTraversare arbore inordine:\n\n");
	TraversareInordine(root);

	// dezalocare arbore binar de cautare
	root = DezalocareArboreBinCautare(root);
	printf("\nTraversare arbore inordine dupa dezalocare:\n\n");
	TraversareInordine(root);
}

