#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct NodLS;
struct NodLP {
	unsigned int idVarf;
	Student stud;
	NodLS* primListaVecini;
	NodLP* next;
};

// structura nod lista secundara
struct NodLS {
	unsigned int idNodAdiacent;
	NodLS* next;
};

// structura nod coada/stiva
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

Nod* put(Nod* queue, unsigned int idv)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->idVarf = idv;
	nou->next = NULL;

	if (!queue)
		return nou;
	else
	{
		Nod* tmp = queue;
		while (tmp->next)
			tmp = tmp->next;

		tmp->next = nou;
	}

	return queue;
}

Nod* get(Nod* queue, unsigned int &varf)
{
	if (queue)
	{
		varf = queue->idVarf;
		Nod* tmp = queue;

		queue = queue->next;
		free(tmp);
	}

	return queue;
}

// traversare BF a grafului
unsigned int* BF(NodLP* pLP, unsigned int start, unsigned int nrVarfuri) {
	unsigned int* flags, * output, k = 0;
	Nod* queue = 0;

	// alocare vector de flaguri
	flags = (unsigned int*)malloc(nrVarfuri * sizeof(unsigned int));
	// initializare vector flaguri
	for (unsigned int i = 0; i < nrVarfuri; i++)
		flags[i] = 0;

	// alocare vector de iesire
	output = (unsigned int*)malloc(nrVarfuri * sizeof(unsigned int));

	// push varf de start
	queue = put(queue, start);
	flags[start - 1] = 1;

	while (queue) {
		unsigned int varf;
		// extragere nod/varf graf din coada
		queue = get(queue, varf);

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
				// put pentru vecini cu flags nul (0)
				queue = put(queue, tmpLS->idNodAdiacent);

				// comutare flags pentru vecinii salvati in coada
				flags[tmpLS->idNodAdiacent - 1] = 1;
			}

			tmpLS = tmpLS->next;
		}
	}

	free(flags);

	return output;
}

// TO DO
// implementare DF (stiva in loc de coada)

// TO DO
// creare structura graf cu matrice de adiacenta
// implementari BF si DF pentru graf creat cu matrice de adiacenta

int main() {
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
		}
		else {
			// nu exista nodul cautat in LP
			printf("\nNodul cautat cu id %d nu exista.\n", src);
		}

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

	fclose(f);

	// inserare studenti in varfurile din graf (confirm id varf precizat in fisier)
	f = fopen("StudGraf.txt", "r");
	char studBuff[20];
	Student stud;

	char* token, file_buf[LINESIZE], sep_list[] = ",\n";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		unsigned int vStud = atoi(token);

		token = strtok(NULL, sep_list);
		stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(stud.nrGrupa, token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");

		NodLP* tmpLP = cautaNodLP(pListaAdiacenta, vStud);
		tmpLP->stud.id = stud.id;
		tmpLP->stud.nume = stud.nume;
		strcpy(tmpLP->stud.nrGrupa, stud.nrGrupa);
	}
	fclose(f);

	// parsare lista de adiacenta
	NodLP* tmpLP = pListaAdiacenta;
	while (tmpLP) {

		printf("\nVarf %d (%d-%s) cu vecinii: ", tmpLP->idVarf, tmpLP->stud.id, tmpLP->stud.nume);

		NodLS* tmpLS = tmpLP->primListaVecini;
		while (tmpLS) {
			printf(" %d ", tmpLS->idNodAdiacent);

			tmpLS = tmpLS->next;
		}

		tmpLP = tmpLP->next;
	}

	// traversare breadth-first graf
	unsigned int* out = BF(pListaAdiacenta, 1, nrVarfuri);
	printf("\nTraversare BF #1: ");
	for (unsigned char i = 0; i < nrVarfuri; i++)
		printf(" %d ", out[i]);
	printf("\n\n");

	free(out);

	out = BF(pListaAdiacenta, 6, nrVarfuri);
	printf("\nTraversare BF #2: ");
	for (unsigned char i = 0; i < nrVarfuri; i++)
		printf(" %d ", out[i]);
	printf("\n\n");

	free(out);


	// dezalocare lista de adiacenta
	while (pListaAdiacenta)
	{
		tmpLP = pListaAdiacenta;
		pListaAdiacenta = pListaAdiacenta->next;

		// dezalocare lista de varfuri adiacente (lista secundara) pt tmpLP
		while (tmpLP->primListaVecini)
		{
			NodLS* tmpLS = tmpLP->primListaVecini;
			tmpLP->primListaVecini = tmpLP->primListaVecini->next;

			free(tmpLS);
		}

		// dezalocare nod tmpLP
		free(tmpLP->stud.nume);
		free(tmpLP);
	}

	// parsare lista de adiacenta
	printf("\n\n\nLista de adiacenta dupa dezalocare: \n");
	tmpLP = pListaAdiacenta;
	while (tmpLP) {

		printf("\nVarf %d (%d-%s) cu vecinii: ", tmpLP->idVarf, tmpLP->stud.id, tmpLP->stud.nume);

		NodLS* tmpLS = tmpLP->primListaVecini;
		while (tmpLS) {
			printf(" %d ", tmpLS->idNodAdiacent);

			tmpLS = tmpLS->next;
		}

		tmpLP = tmpLP->next;
	}


	printf("\n\n");

	return 0;
}