#include <stdio.h>
#include <malloc.h>

struct NodTree {
	int key;
	struct NodTree* fiu, * frate;
};

// [in] r - nod curent in arbore oarecare; poate fi orice nod in functie de lantul de apeluri recursive
// [in] id - cheia nodului care se cauta in arborele oarecare
// [in,out] gasit - pointer catre nodul identificat; NULL daca nodul nu este gasit
void cautaNod(struct NodTree* r, int id, struct NodTree** gasit) {
	if (r) {
		printf("Nod curent este: %d\n", r->key);
		if (r->key == id) { // prelucrez nodul curent r
			*gasit = r;
			return;
		}
		cautaNod(r->fiu, id, gasit); // parsez primul subarbore descendent al lui r
		if (*gasit)
			return;
		if (r->fiu) {
			struct NodTree* tmp = r->fiu;
			while (tmp->frate) { // parsez restul de subarbori descendenti ai lui r 
				cautaNod(tmp->frate, id, gasit);
				if (*gasit)
					return;
				tmp = tmp->frate;
			}
		}
	}
}

// [in] r - nod curent in arbore oarecare; poate fi orice nod in functie de lantul de apeluri recursive
void preordine(struct NodTree* r) {
	if (r) {
		printf("%d  ", r->key); // prelucrare nod curent

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

// [in] r - radacina de arbore oarecare
// [in] cheie - cheia de inserat in arborele r
// [in] idParinte - cheia pentru nodul parinte al nodului de inserat cu cheie
// [out] radacina de arbore oarecare, eventul diferita fata de [in] r daca idParinte este 0
struct NodTree* inserare(struct NodTree* r, int cheie, int idParinte) {
	struct NodTree* nou = (struct NodTree*)malloc(sizeof(struct NodTree)); // nodul care se insereaza devine nod radacina
	nou->key = cheie;
	nou->frate = NULL;

	if (!idParinte) { // nodul nou (cu cheie) va deveni noua radacina de arbore
		// arborele contine cel putin 1 nod SAU este EMPTY (0 noduri)
		printf("\n Inserare nod radacina %d:\n", cheie);
		nou->fiu = r;

		r = nou;
	}
	else { // se cauta nodul cu idParinte care va primi descendent pe nou cu cheie
		nou->fiu = NULL;

		struct NodTree* p = NULL;
		printf("\n Cauta nod parinte %d pentru nodul %d:\n", idParinte, cheie);
		cautaNod(r, idParinte, &p);
		if (p && !p->fiu)
			p->fiu = nou; // nodul este gasit, dar nu are prim descendent (fiu); var nou devine primul frate pentru fiu
		else {
			if (p)
			{
				if (!p->fiu->frate)
					p->fiu->frate = nou; // nodul de inserat (var nou) devine frate pentru fiu
				else {
					struct NodTree* tmp = p->fiu;
					while (tmp->frate)
						tmp = tmp->frate;

					tmp->frate = nou; // nodul de inserat este ultimul nod in lista de descendenti ai lui idParinte (var p)
				}
			}
			else
			{
				free(nou); // nu exista parintele cautat
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