#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct Nod Nod;
typedef struct NodLS NodLS;
typedef struct NodLP NodLP;

// structura nod lista principala
struct NodLS;
struct NodLP {
	unsigned int idVarf;
	NodLS* primListaVecini;
	NodLP* next;
};

// structura nod lista secundara
struct NodLS {
	unsigned int idNodAdiacent;
	NodLS* next;
};

// structura nod stiva
struct Nod {
	unsigned int idVarf;
	Nod* next;
};

// inserare nod in lista secundara
NodLS* inserareNodLS(NodLS* pLS, unsigned int id) {
	NodLS* nou = (NodLS*)malloc(sizeof(NodLS));
	nou->idNodAdiacent = id;
	nou->next = 0;

	if (!pLS) { // LS nu contine nici un nod
		return nou;
	}
	else {
		// parsare LS pana la ultimul nod
		NodLS* tmp = pLS;
		while (tmp->next)
			tmp = tmp->next;

		tmp->next = nou;
	}

	return pLS;
}

// inserare nod in lista principala
NodLP* inserareNodLP(NodLP* pLP, unsigned int id, NodLS* pLstVecini) {
	NodLP* nou = (NodLP*)malloc(sizeof(NodLP));
	nou->idVarf = id;
	nou->primListaVecini = pLstVecini;
	nou->next = 0;

	if (!pLP) { // LP nu contine nici un nod
		return nou;
	}
	else {
		// parsare LP pana la ultimul nod
		NodLP* tmp = pLP;
		while (tmp->next)
			tmp = tmp->next;

		tmp->next = nou;
	}

	return pLP;
}

// cauta nod (varf graf) in lista principala
NodLP* cautaNodLP(NodLP* pLP, unsigned int idCautat) {
	NodLP* tmp = pLP;
	while (tmp) {
		if (tmp->idVarf == idCautat)
			return tmp; // adresa nod in LP cu idCautat

		tmp = tmp->next;
	}

	return tmp; // NULL; nu exista nod in LP cu idCautat
}

Nod* push(Nod* stack, unsigned int varf)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->idVarf = varf;
	nou->next = stack;

	return nou;
}

Nod* pop(Nod* stack, unsigned int *varf)
{
	if (stack)
	{
		*varf = stack->idVarf;
		Nod* tmp = stack;
		stack = stack->next;

		free(tmp);
	}

	return stack;
}

// traversare DF a grafului
unsigned int* DF(NodLP* pLP, unsigned int start, unsigned int nrVarfuri) {
	unsigned int* flags, * output, k = 0;
	Nod* stack = 0;

	// alocare vector de flaguri
	flags = (unsigned int*)malloc(nrVarfuri * sizeof(unsigned int));
	// initializare vector flaguri
	for (unsigned int i = 0; i < nrVarfuri; i++)
		flags[i] = 0;

	// alocare vector de iesire
	output = (unsigned int*)malloc(nrVarfuri * sizeof(unsigned int));

	// push varf de start
	stack = push(stack, start);
	flags[start - 1] = 1;

	while (stack) {
		unsigned int varf;
		// extragere nod graf din varful stivei
		stack = pop(stack, &varf);

		// salvare in banda de iesire a varfului extras in vederea prelucrarii
		output[k] = varf;
		k = k + 1;

		// TO DO: stabilire vecini pentru varf
		// cauta varf in LP
		NodLP* tmpLP = cautaNodLP(pLP, varf);
		NodLS* tmpLS = tmpLP->primListaVecini; // acces lista de varfuri adiacente
		while (tmpLS)
		{

			// TO DO: push pentru vecinii cu flags nul
			int vecin = tmpLS->idNodAdiacent;
			if (flags[vecin - 1] == 0)
			{
				// vecin nu a fost salvat anterior pe stack
				stack = push(stack, vecin);
				// TO DO: comutare flags pentru vecinii salvati pe stiva
				flags[vecin - 1] = 1; // comutare flag
			}

			tmpLS = tmpLS->next;
		}

	}

	return output;
}

// TO DO: functia traversare BF

// TO DO: functia put pentru coada

// TO DO: functia get pentru coada

void main() {
	FILE* f;
	f = fopen("Graf.txt", "r");

	char buffer[128];
	fgets(buffer, sizeof(buffer), f);

	NodLP* pListaAdiacenta = 0;
	unsigned int nrVarfuri = 0;

	sscanf(buffer, "%d", &nrVarfuri); // preluare nr varfuri de pe prima linie din fisier
	for (unsigned int i = 1; i <= nrVarfuri; i++) // creare noduri LP
		pListaAdiacenta = inserareNodLP(pListaAdiacenta, i, NULL);


	while (fgets(buffer, sizeof(buffer), f)) {
		unsigned int src, dst;
		sscanf(buffer, "%d %d", &src, &dst);

		NodLP* tmpLP = cautaNodLP(pListaAdiacenta, src);

		if (tmpLP) {
			// nodul cu idVarf == src
			tmpLP->primListaVecini = inserareNodLS(tmpLP->primListaVecini, dst);

			// pentru a insera si muchia inversa (graful devine neorientat)
			// cauta nod in LP cu varf sursa nodul 2 preluat din fisier
			tmpLP = cautaNodLP(pListaAdiacenta, dst);
			tmpLP->primListaVecini = inserareNodLS(tmpLP->primListaVecini, src);
		}
		else {
			// nu exista nodul cautat in LP
			printf("\nNodul cautat cu id %d nu exista.\n", src);
		}
	}

	// parsare lista de adiacenta
	NodLP* tmpLP = pListaAdiacenta;
	while (tmpLP) {

		printf("\nVarf %d cu vecinii: ", tmpLP->idVarf);

		NodLS* tmpLS = tmpLP->primListaVecini;
		while (tmpLS) {
			printf(" %d ", tmpLS->idNodAdiacent);

			tmpLS = tmpLS->next;
		}

		tmpLP = tmpLP->next;
	}
	unsigned int* vector_traversare = DF(pListaAdiacenta, 1, nrVarfuri);

	printf("\n\nTraversare DF graf:");
	for (unsigned int i = 0; i < nrVarfuri; i++)
		printf(" %u", vector_traversare[i]);

	// dezalocare vector_traversare
	free(vector_traversare);


	//vector_traversare = BF(pListaAdiacenta, 1, nrVarfuri);
	//printf("\n\nTraversare BF graf:");
	//for (unsigned int i = 0; i < nrVarfuri; i++)
	//	printf(" %u", vector_traversare[i]);
	//// dezalocare vector_traversare
	//free(vector_traversare);

	printf("\n\n");
	fclose(f);
}


