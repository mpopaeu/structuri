#include <stdio.h>
#include <malloc.h>

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

NodLP* cautaNodLP(NodLP* pLP, unsigned int idCautat) {
	NodLP* tmp = pLP;
	while (tmp) {
		if (tmp->idVarf == idCautat)
			return tmp; // adresa nod in LP cu idCautat

		tmp = tmp->next;
	}

	return NULL; // nu exista nod in LP cu idCautat
}

Nod* push(Nod* stack, unsigned int idv)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->idVarf = idv;
	nou->next = stack;

	return nou;
}

Nod* pop(Nod* stack, unsigned int &varf)
{
	if (stack)
	{
		varf = stack->idVarf;

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
		stack = pop(stack, varf);

		// salvare in banda de iesire a varfului extras in vederea prelucrarii
		output[k] = varf;
		k = k + 1;

		// stabilire vecini pentru varf
		NodLP* tmpLP = cautaNodLP(pLP, varf);
		NodLS* tmpLS = tmpLP->primListaVecini;
		while (tmpLS)
		{
			if (flags[tmpLS->idNodAdiacent - 1] == 0)
			{
				// push pentru vecinii cu flags nul
				stack = push(stack, tmpLS->idNodAdiacent);

				// comutare flags pentru vecinii salvati pe stiva
				flags[tmpLS->idNodAdiacent - 1] = 1;
			}

			tmpLS = tmpLS->next;
		}
		
	}

	free(flags);

	return output;
}



// TO DO: implementare traversare BF (lista de adiacenta)

// TO DO
// creare structura graf pe baza de matrice de adiacenta
// implementari DF si BF pentru graf creat cu matrice de adiacenta

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

		// (src, dst)
		NodLP* tmpLP = cautaNodLP(pListaAdiacenta, src);

		if (tmpLP) {
			// nodul cu idVarf == src
			tmpLP->primListaVecini = inserareNodLS(tmpLP->primListaVecini, dst);
		}
		else {
			// nu exista nodul cautat in LP
			printf("\nNodul cautat cu id %d nu exista.\n", src);
		}

		// (dst, src)
		tmpLP = cautaNodLP(pListaAdiacenta, dst);

		if (tmpLP) {
			// nodul cu idVarf == src
			tmpLP->primListaVecini = inserareNodLS(tmpLP->primListaVecini, src);
		}
		else {
			// nu exista nodul cautat in LP
			printf("\nNodul cautat cu id %d nu exista.\n", dst);
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

	fclose(f);

	unsigned int* out = DF(pListaAdiacenta, 2, nrVarfuri);
	printf("\nTraversare #1 DF: ");
	for (unsigned char i = 0; i < nrVarfuri; i++)
		printf(" %d ", out[i]);
	printf("\n\n");

	free(out);

	out = DF(pListaAdiacenta, 5, nrVarfuri);
	printf("\nTraversare #2 DF: ");
	for (unsigned char i = 0; i < nrVarfuri; i++)
		printf(" %d ", out[i]);
	printf("\n\n");

	free(out);
	// dezalocare lista de adiacenta
	while (pListaAdiacenta)
	{
		tmpLP = pListaAdiacenta;
		pListaAdiacenta = pListaAdiacenta->next;

		// dezalocare lista secundara cu vecinii nodului tmpLP->idVarf
		while (tmpLP->primListaVecini)
		{
			NodLS* tmpLS = tmpLP->primListaVecini;
			tmpLP->primListaVecini = tmpLP->primListaVecini->next;

			free(tmpLS);
		}

		// dezalocare nod lista principala
		free(tmpLP);		
	}

	// parsare lista de adiacenta
	printf("\n\nLista de adiacenta dupa dezalocare:\n");
	tmpLP = pListaAdiacenta;
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
}


