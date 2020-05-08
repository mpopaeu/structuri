//#include <string.h>
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


NodTree *inserare(NodTree *r, int cheie, int idParinte) {

	if (!idParinte) {
		NodTree* nou = (NodTree*)malloc(sizeof(NodTree)); // nodul care se insereaza devine nod radacina
		nou->key = cheie;
		nou->fiu = NULL;
		nou->frate = NULL;

		if (r) {
			nou->fiu = r; // daca exista arbore atunci cheie devine noua radacina cu descendent r
		}

		r = nou;
	}
	else {
		NodTree* p = NULL;
		cautaNod(r, idParinte, p);
		if (p) {
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

void main() {
	NodTree *root = NULL;

	// inserare cheie in arbore
	root = inserare(root, 1, 0);
	printf("\nInserare noua\n");
	root = inserare(root, 2, 1);
	printf("\nInserare noua\n");
	root = inserare(root, 3, 1);
	printf("\nInserare noua\n");
	root = inserare(root, 4, 1);
	printf("\nInserare noua\n");
	root = inserare(root, 5, 2);
	printf("\nInserare noua\n");
	root = inserare(root, 6, 2);
	printf("\nInserare noua\n");
	root = inserare(root, 7, 6);
	printf("\nInserare noua\n");
	root = inserare(root, 8, 7);

	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);
	printf("\n\n");

	root = inserare(root, 9, 4);
	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);

	root = inserare(root, 10, 0);
	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);

	printf("\n\n");
}