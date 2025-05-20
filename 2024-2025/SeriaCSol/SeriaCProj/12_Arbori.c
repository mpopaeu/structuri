#include <stdio.h>
#include <malloc.h>

struct NodTree {
	int key;
	struct NodTree* fiu, * frate;
};

// r - radacina subarbore; nod curent in abordare recursiva
// id - cheie nod parinte care se cauta pentru nodul de inserat
// gasit - adresa nodului cu id identificat in arbore; pointer trimis prin adresa
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

// r - nod curent (radacina subarbore)
// cheie - cheia nodului de inserat
// idParinte - cheie nod parinte sub care se aseaza nodul nou cheie
struct NodTree* inserare(struct NodTree* r, int cheie, int idParinte) {

	if (!idParinte) { // nodul nou (cu cheie) va deveni noua radacina de arbore
		struct NodTree* nou = (struct NodTree*)malloc(sizeof(struct NodTree)); // nodul care se insereaza devine nod radacina
		nou->key = cheie;
		nou->fiu = NULL;
		nou->frate = NULL;

		if (r) { // exista cel putin 1 nod in arbore (radacina arbore curent)
			nou->fiu = r; // arborele devine sub-arbore pentru noua radacina nou
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
			p->fiu = nou; // nodul nou devine prim fiu al parintelui idParinte
		else {
			if (p)
			{ // nodul nou devine ultimul frate al primului fiu pentru parintele idParinte
				if (!p->fiu->frate)
					p->fiu->frate = nou; // nou este primul frate pentru p->fiu (p parinte cu idParinte)
				else {
					struct NodTree* tmp = p->fiu;
					while (tmp->frate)
						tmp = tmp->frate;

					tmp->frate = nou; // nodul nou se insereaza la sfarsitul listei de frati pentru p->fiu
				}
			}
		}
	}

	return r;
}


struct NodTree* dezalocare_arbore(struct NodTree* r) {
	if (r) {
		struct NodTree* p_frate = NULL;
		if (r->fiu)
		{
			p_frate = r->fiu->frate;
		}
		r->fiu = dezalocare_arbore(r->fiu); // parsez primul subarbore descendent lui r	

		if (p_frate) {
			struct NodTree* tmp = p_frate;
			while (tmp) { // parsez restul de subarbori descendenti lui r 
				p_frate = tmp->frate;
				tmp = dezalocare_arbore(tmp);
				tmp = p_frate;
			}
		}

		// prelucrare nod - dezalocare structura dinamica din mem heap
		printf("Dezalocare nod %d\n", r->key);
		free(r);
		r = NULL;
	}

	return r;
}

void main() {
	struct NodTree* root = NULL;

	// inserare cheie in arbore
	printf("\nInserare cheie 1\n");
	root = inserare(root, 1, 0);
	printf("\nInserare cheie 2\n");
	root = inserare(root, 2, 1);
	printf("\nInserare cheie 3\n");
	root = inserare(root, 3, 1);
	printf("\nInserare cheie 4\n");
	root = inserare(root, 4, 1);
	printf("\nInserare cheie 5\n");
	root = inserare(root, 5, 2);
	printf("\nInserare cheie 6\n");
	root = inserare(root, 6, 2);
	printf("\nInserare cheie 7\n");
	root = inserare(root, 7, 6);
	printf("\nInserare cheie 8\n");
	root = inserare(root, 8, 7);

	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);
	printf("\n\n");

	printf("\nInserare cheie 9\n");
	root = inserare(root, 9, 7);
	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);
	printf("\n\n");

	// dezalocare arbore oarecare implementat fiu-frate cu structuri dinamice
	root = dezalocare_arbore(root);
	printf("\nArborele in traversare in preordine DUPA DEZALOCARE:\n\n");
	preordine(root);
	printf("\n\n");
}