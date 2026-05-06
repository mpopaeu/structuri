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

struct NodTree* inserare(struct NodTree* r, int cheie, int idParinte) {

	if (!idParinte) { // nodul nou (cu cheie) va deveni noua radacina de arbore
		struct NodTree* nou = (struct NodTree*)malloc(sizeof(struct NodTree)); // nodul care se insereaza devine nod radacina
		nou->key = cheie;
		nou->fiu = NULL;
		nou->frate = NULL;

		if (r) {
			nou->fiu = r; // radacina curenta devine descendent pentru noua radacina inserata (cheie)
		}

		r = nou;
	}
	else { // se cauta nodul cu idParinte care va primi descendent pe nou cu cheie
		struct NodTree* nou = (struct NodTree*)malloc(sizeof(struct NodTree));
		nou->key = cheie;
		nou->fiu = NULL;
		nou->frate = NULL;

		struct NodTree* p = NULL;
		cautaNod(r, idParinte, &p); // p contine adresa nodului parinte pentru de inserat
		if (p && !p->fiu) // p nu are prim fiu
			p->fiu = nou; // nodul de inserat devine primul fiu al lui p
		else {
			if (p) // p a fost identificat; daca este pointer null atunci nu exista parinte pentru nou
			{
				if (!p->fiu->frate)
					p->fiu->frate = nou; // nou devine primul frate pentru p->fiu
				else {
					struct NodTree* tmp = p->fiu;
					while (tmp->frate) // parsare lista de frati pana la ultimul nod
						tmp = tmp->frate;

					tmp->frate = nou; // nou se adauga in lista de frati ai lui p->fiu
				}
			}
			else
			{
				free(nou); // dezalocare nou deoarece nodul parinte p este null (nu exista nod cu id cautat ca parinte pentru nou)
			}
		}
	}

	return r;
}

void preordine(struct NodTree* r) {
	if (r) {
		printf("%d  ", r->key); // prelucrare nod curent r

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

void postordine(struct NodTree* r) {
	if (r) {
		postordine(r->fiu); // parsez primul subarbore descendent lui r	

		if (r->fiu) {
			struct NodTree* tmp = r->fiu;
			while (tmp->frate) { // parsez restul de subarbori descendenti lui r 
				postordine(tmp->frate);
				tmp = tmp->frate;
			}
		}

		printf("%d  ", r->key); // prelucrare nod curent r
	}
}


struct NodTree*  dezalocareArbore(struct NodTree* r) {
	if (r) {
		if (r->fiu) {
			struct NodTree* tmp = r->fiu;
			while (tmp->frate) { // parsez restul de subarbori descendenti lui r 
				struct NodTree* pfrate = tmp->frate->frate;
				dezalocareArbore(tmp->frate);
				tmp->frate = pfrate;
			}
		}

		// stergere/dezalocare nodului curent r; 
		// r este frunza dupa dezalocarea subarborilor sai din apelurile anterioare
		struct NodTree* pfiu = r->fiu;
		free(r);
		r = NULL;

		dezalocareArbore(pfiu); // parsez primul subarbore descendent lui r	
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

	printf("\nArborele in traversare in postordine:\n\n");
	postordine(root);
	printf("\n\n");

	root = dezalocareArbore(root);
	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);
	printf("\n\n");
}