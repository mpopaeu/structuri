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

NodLP* cautaNodLP(NodLP* pLP, unsigned int idCautat) {
	NodLP* tmp = pLP;
	while (tmp) {
		if (tmp->idVarf == idCautat)
			return tmp; // adresa nod in LP cu idCautat

		tmp = tmp->next;
	}

	return tmp; // NULL; nu exista nod in LP cu idCautat
}

// inserare unsigned int pe stiva
Nod* push(Nod* stiva, unsigned int varf_graf)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->idVarf = varf_graf;
	nou->next = stiva;

	return nou;
}

// extragere unsigned int de pe stiva
Nod* pop(Nod* stiva, unsigned int* varf_salvat)
{
	if (stiva)
	{
		*varf_salvat = stiva->idVarf;
		Nod* temp = stiva;
		stiva = stiva->next;
		free(temp);
	}

	return stiva;
}

// traversare DF a grafului
unsigned int* DF(NodLP* pLP, unsigned int start, unsigned int nrVarfuri) {
	unsigned int* flags, * output, k = 0;
	Nod* stack = 0;

	// alocare vector de flaguri
	flags = (unsigned int*)malloc(nrVarfuri * sizeof(unsigned int));
	// initializare vector flaguri
	for (unsigned int i = 0; i < nrVarfuri; i++)
		flags[i] = 0; // initial, elmentele sunt marcate cu "disponibil la salvare pe stiva"

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

		// stabilire vecini pentru varf
		NodLP* tmpLP = cautaNodLP(pLP, varf);

		NodLS* tmpLS = tmpLP->primListaVecini;
		while (tmpLS)
		{
			unsigned int id_vecin = tmpLS->idNodAdiacent;
			if (flags[id_vecin - 1] == 0)
			{
				// id_vecin nu a fost salvat pe stiva (de lucru)
				// push id_vecin cu flags nul
				stack = push(stack, id_vecin);

				// comutare flags pentru id_vecin salvat pe stiva mai sus
				flags[id_vecin - 1] = 1;
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
			// inserare (src, dst)
			tmpLP->primListaVecini = inserareNodLS(tmpLP->primListaVecini, dst);

			// inserare(dst, src)
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

	// traversare Depth-First graf
	unsigned int* out = DF(pListaAdiacenta, 5, nrVarfuri);
	printf("\n\nSuccesiunea de varfuri in traversare DF: ");
	for (unsigned int i = 0; i < nrVarfuri; i++)
	{
		printf(" %u ", out[i]);
	}


	printf("\n\n");


	// dezalocare lista de adiacenta
	while (pListaAdiacenta) {
		tmpLP = pListaAdiacenta;
		while (tmpLP->primListaVecini) {
			NodLS* tmpLS = tmpLP->primListaVecini; // tempLS va fi dezalocat
			tmpLP->primListaVecini = tmpLP->primListaVecini->next; // actualizare inceput lista de vecini
			free(tmpLS); // dezalocare tmpLS
		}

		pListaAdiacenta = pListaAdiacenta->next; // noul inceput de lista principala
		free(tmpLP); // dezalocare tmpLP
	}

	// dezalocare vector cu varfuri in traversare DF
	free(out);

	// parsare lista de adiacenta
	printf("Continut lista de adiacenta dupa dezalocare lista de adiacenta:\n");
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

	fclose(f);
}


