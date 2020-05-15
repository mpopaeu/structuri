#include <string.h>
#include <stdio.h>
#include <malloc.h>

struct NodTree {
	int key;
	NodTree *fiu, *frate;
};


void cautaNod(NodTree* r, int id, NodTree* &gasit) {
	if (r) {
		printf("Nod curent este: %d\n", r->key);
		if (r->key == id) { // prelucrez nodul curent r
			gasit = r;
			return;
		}
		cautaNod(r->fiu, id, gasit); // parsez primul subarbore descendent lui r
		if (gasit)
			return;
		if (r->fiu) {
			NodTree *tmp = r->fiu;
			while (tmp->frate) { // parsez restul de subarbori descendenti lui r 
				cautaNod(tmp->frate, id, gasit);
				if (gasit)
					return;
				tmp = tmp->frate;
			}
		}
	}
}

NodTree *inserare(NodTree *r, int cheie, int idParinte) {

	if (!idParinte) {
		NodTree* nou = (NodTree*)malloc(sizeof(NodTree)); // nodul care se insereaza devine nod radacina
		nou->key = cheie;
		nou->fiu = NULL;
		nou->frate = NULL;

		if (r) {
			nou->fiu = r; // modificare radacina arbore oarecare
		}

		r = nou;
	}
	else {		
		NodTree* p = 0;
		cautaNod(r, idParinte, p);
		if (p != NULL) { // a fost identificat nod cu idParinte in arbore oarecare
			NodTree* nou = (NodTree*)malloc(sizeof(NodTree));
			nou->key = cheie;
			nou->fiu = NULL;
			nou->frate = NULL;

			if (!p->fiu)
				p->fiu = nou;
			else {

				if (!p->fiu->frate)
					p->fiu->frate = nou;
				else {
					NodTree* tmp = p->fiu;
					while (tmp->frate)
						tmp = tmp->frate;

					tmp->frate = nou;
				}
			}
		}
	}

	return r;
}

void preordine(NodTree* r) {
	if (r) {
		printf("%d  ", r->key);

		preordine(r->fiu); // parsez primul subarbore descendent lui r	

		if (r->fiu) {
			NodTree *tmp = r->fiu;
			while (tmp->frate) { // parsez restul de subarbori descendenti lui r 
				preordine(tmp->frate);
				tmp = tmp->frate;
			}
		}
	}
}

void main() {
	NodTree *root = NULL;

	// inserare cheie in arbore
	root = inserare(root, 1, 0);
	root = inserare(root, 2, 1);
	root = inserare(root, 3, 1);
	root = inserare(root, 4, 1);
	root = inserare(root, 5, 2);
	root = inserare(root, 6, 2);
	root = inserare(root, 7, 6);
	root = inserare(root, 8, 7);

	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);
	printf("\n\n");

	root = inserare(root, 9, 0);
	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);
	printf("\n\n");
}