#include <stdio.h>
#include <malloc.h>

struct NodTree {
	int key;
	struct NodTree* fiu, * frate;
};

void cautaNod(struct NodTree* r, int id, struct NodTree** gasit) {
	if (r) {
		printf("Nod curent este: %d\n", r->key);
		if (r->key == id) { // prelucrez nodul curent r
			*gasit = r;
			return;
		}
		cautaNod(r->fiu, id, gasit); // parsez primul subarbore descendent lui r
		if (*gasit)
			return;
		if (r->fiu) {
			struct NodTree* tmp = r->fiu;
			while (tmp->frate) { // parsez restul de subarbori descendenti lui r 
				cautaNod(tmp->frate, id, gasit);
				if (*gasit)
					return;
				tmp = tmp->frate;
			}
		}
	}
}


void preordine(struct NodTree* r) {
	if (r) {
		printf("%d  ", r->key);

		preordine(r->fiu); // parsez primul subarbore descendent lui r	

		if (r->fiu) {
			struct NodTree* tmp = r->fiu;
			while (tmp->frate) { // parsez restul de subarbori descendenti lui r 
				preordine(tmp->frate);
				tmp = tmp->frate;
			}
		}
	}
}


struct NodTree* inserare(struct NodTree* r, int cheie, int idParinte) {

	if (!idParinte) { // nodul nou (cu cheie) va deveni noua radacina de arbore
		struct NodTree* nou = (struct NodTree*)malloc(sizeof(struct NodTree)); // nodul care se insereaza devine nod radacina
		nou->key = cheie;
		nou->fiu = NULL;
		nou->frate = NULL;

		if (r) {
			nou->fiu = r;
		}

		r = nou;
	}
	else { // se cauta nodul cu idParinte care va primi descendent pe nou cu cheie
		struct NodTree* nou = (struct NodTree*)malloc(sizeof(struct NodTree));
		nou->key = cheie;
		nou->fiu = NULL;
		nou->frate = NULL;

		struct NodTree* p = NULL;
		cautaNod(r, idParinte, &p);
		if (p && !p->fiu)
			p->fiu = nou;
		else {
			if (p)
			{
				if (!p->fiu->frate)
					p->fiu->frate = nou;
				else {
					struct NodTree* tmp = p->fiu;
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
	struct NodTree* root = NULL;

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

	root = inserare(root, 9, 7);
	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);
	printf("\n\n");
}