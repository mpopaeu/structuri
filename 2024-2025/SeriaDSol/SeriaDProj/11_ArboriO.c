#include <stdio.h>
#include <malloc.h>

struct NodTree {
	int key;
	struct NodTree* fiu, * frate;
};


// r - nod curent in apelul recursiv i
// id - cheia nodului cautat in AO
// gasit - adresa nodului care contine id in AO; trensferat prin adresa
void cautaNod(struct NodTree* r, int id, struct NodTree** gasit) {
	// cautare recursiva a unui nod cu cheie id in arbore oarecare
	// operatie de traversare in preordine cu verificarea continutului 
	// nodului curent r
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

struct NodTree* dezalocare_AO_postordine(struct NodTree* r) {
	if (r != NULL) {
		r->fiu = dezalocare_AO_postordine(r->fiu);
		struct NodTree* temp = r->frate; // salvare prim frate pentru r (inceput lista de frati)
		printf("Dezalocare nod cu cheia %d\n", r->key);
		free(r);
		r = NULL;

		while (temp != NULL) {
				temp->fiu = dezalocare_AO_postordine(temp->fiu); // dezalocare subarbori pentru nodul temp
				struct NodTree* t_frate = temp; // salvare temporara inceput de lista de fratie in vederea dezalocarii
				temp = temp->frate; // temp este urmatorul nod in lista de frati
				printf("Dezalocare nod cu cheia %d\n", t_frate->key);
				free(t_frate); // dezalocare inceput lista frati pentru care s-au dezalocat toti subarborii
			}
		}

	return r;
}

// r - nod radacina AO
// cheie - cheie nodului care se insereaza in AO
// idParinte - cheie nod care devine parinte pentru nodul de inserat cu cheie
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

		cautaNod(r, idParinte, &p); // cautare nod cu cheie idParinte; p pointer trimis prin adresa

		if (p && !p->fiu) // nodul parinte nu are descendenti
			p->fiu = nou; // nou devine primul fiu pentru parintele identificat p
		else {
			if (p)
			{
				// nodul parinte exista in AO
				if (!p->fiu->frate)
					p->fiu->frate = nou; // nou devine primul frate (nodul 2 din lista de descendenti pentru parintele p)
				else {
					struct NodTree* tmp = p->fiu;
					while (tmp->frate)
						tmp = tmp->frate; // nou devine ultimul nod din lista de descendenti ai parintelui p

					tmp->frate = nou;
				}
			}
			else
			{
				; // nodul nou cu cheie nu se insereaza in AO daca parintele p nu este gasit (p == NULL)
			}
		}
	}

	return r; 
}

void main() {
	struct NodTree* root = NULL;

	// inserare cheie in arbore
	printf("\nInserare NOD cheie 1:\n");
	root = inserare(root, 1, 0);
	printf("\nInserare NOD cheie 2:\n");
	root = inserare(root, 2, 1);
	printf("\nInserare NOD cheie 3:\n");
	root = inserare(root, 3, 1);
	printf("\nInserare NOD cheie 4:\n");
	root = inserare(root, 4, 1);
	printf("\nInserare NOD cheie 5:\n");
	root = inserare(root, 5, 2);
	printf("\nInserare NOD cheie 6:\n");
	root = inserare(root, 6, 2);
	printf("\nInserare NOD cheie 7:\n");
	root = inserare(root, 7, 6);
	printf("\nInserare NOD cheie 8:\n");
	root = inserare(root, 8, 7);

	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);
	printf("\n\n");

	printf("\nInserare NOD cheie 9:\n");
	root = inserare(root, 9, 7);
	// root = inserare(root, 9, 0); // nodul cu cheie 9 devine noua radacina de AO
	// root = inserare(root, 9, 17); // nodul cu cheie 17 nu exista in AO, nodul cu cheie 9 nu se insereaza
	
	printf("\nArborele in traversare in preordine:\n\n");
	preordine(root);

	printf("\nDezalocare Arbore Oarecare:\n");
	root = dezalocare_AO_postordine(root);

	printf("\nArborele in traversare in preordine dupa dezalocare:\n\n");
	preordine(root);

	printf("\n\n");
}