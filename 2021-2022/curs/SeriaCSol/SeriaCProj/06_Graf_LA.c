#include <stdio.h>
#include <malloc.h>

// structura nod lista principala
struct NodLS;
struct NodLP {
	unsigned int idVarf;
	struct NodLS* primListaVecini;
	struct NodLP* next;
};

// structura nod lista secundara
struct NodLS {
	unsigned int idNodAdiacent;
	struct NodLS* next;
};

typedef struct NodLP NodLP;
typedef struct NodLS NodLS;

// structura nod stiva
struct Nod {
	unsigned int idVarf;
	struct Nod* next;
};

typedef struct Nod Nod;

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

NodLP* cautaNodLP(NodLP* pLP, unsigned int idCautat) {
	NodLP* tmp = pLP;
	while (tmp) {
		if (tmp->idVarf == idCautat)
			return tmp; // adresa nod in LP cu idCautat

		tmp = tmp->next;
	}

	return tmp; // NULL; nu exista nod in LP cu idCautat
}

Nod* push(Nod* stack, unsigned int id)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->idVarf = id;
	nou->next = stack;

	return nou;
}

Nod* pop(Nod* stack, unsigned int *id)
{
	*id = 0;
	if (stack)
	{
		*id = stack->idVarf;

		Nod* temp = stack;
		stack = stack->next;

		free(temp);
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
		
		NodLP* tmp = cautaNodLP(pLP, varf);
		NodLS* tempLS = tmp->primListaVecini;

		while (tempLS)
		{
			// stabilire vecini pentru varf
			// parsare lista secundara cu id varfuri vecine pentru varf extras din stiva
			if (flags[tempLS->idNodAdiacent - 1] == 0)
			{
				// push pentru tempLS->idNodAdiacent (vecin cu varf) avanf flag 0
				stack = push(stack, tempLS->idNodAdiacent);
				// comutare flag pentru tempLS->idNodAdiacent 
				flags[tempLS->idNodAdiacent - 1] = 1;
			}

			tempLS = tempLS->next;
		}
		
	}

	free(flags);
	return output;
}

// TO DO: functia push pentru stiva

// TO DO: functia pop pentru stiva

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

	sscanf(buffer, "%u", &nrVarfuri); // preluare nr varfuri de pe prima linie din fisier
	for (unsigned int i = 1; i <= nrVarfuri; i++) // creare noduri LP
		pListaAdiacenta = inserareNodLP(pListaAdiacenta, i, NULL);


	while (fgets(buffer, sizeof(buffer), f)) {
		unsigned int src, dst;
		sscanf(buffer, "%u %u", &src, &dst);

		// inserare muchie (src, dst)
		NodLP* tmpLP = cautaNodLP(pListaAdiacenta, src);

		if (tmpLP) {
			// nodul cu idVarf == src
			tmpLP->primListaVecini = inserareNodLS(tmpLP->primListaVecini, dst);
		}
		else {
			// nu exista nodul cautat in LP
			printf("\nNodul cautat cu id %d nu exista.\n", src);
		}

		// inserare muchie (dst, src)
		tmpLP = cautaNodLP(pListaAdiacenta, dst);

		if (tmpLP) {
			// nodul cu idVarf == dst
			tmpLP->primListaVecini = inserareNodLS(tmpLP->primListaVecini, src);
		}
		else {
			// nu exista nodul cautat in LP
			printf("\nNodul cautat cu id %d nu exista.\n", dst);
		}
	}
	fclose(f);

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

	printf("\n\n");	

	unsigned int* out = DF(pListaAdiacenta, 3, nrVarfuri);
	printf("\nTraversare Depth-First graf implementat cu lista de adiacenta: ");
	for (unsigned int i = 0; i < nrVarfuri; i++)
		printf(" %u", out[i]);

	// dezalocare vector traversare DF
	free(out);

	// dezalocare lista de adiacenta
	while (pListaAdiacenta)
	{
		NodLP* temp = pListaAdiacenta;
		pListaAdiacenta = pListaAdiacenta->next;

		// dezalocare lista de varfuri adiacente
		NodLS* tempLS = temp->primListaVecini;
		while (tempLS)
		{
			NodLS* q = tempLS;
			tempLS = tempLS->next;

			free(q); // dezalocare nod in LS
		}

		free(temp); // dezalocare nod in LP
	}
}
