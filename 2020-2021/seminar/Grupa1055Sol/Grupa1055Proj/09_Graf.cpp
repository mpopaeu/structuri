#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char *nume;
	char nrGrupa[5];
};

// structura nod lista principala
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



void main() {
	FILE *f;
	f = fopen("Graf.txt", "r");

	char buffer[128];
	fgets(buffer, sizeof(buffer), f);

	NodLP* pListaAdiacenta = 0;
	unsigned int nrVarfuri = 0;

	sscanf(buffer, "%d", &nrVarfuri); // preluare nr varfuri de pe prima linie din fisier
	for (unsigned int i = 1; i <= nrVarfuri; i++) // creare noduri LP
		pListaAdiacenta = inserareNodLP(pListaAdiacenta, i, NULL);

	NodLP* tmpLP;
	while (fgets(buffer, sizeof(buffer), f)) {
		unsigned int src, dst;
		sscanf(buffer, "%d %d", &src, &dst);

		tmpLP = cautaNodLP(pListaAdiacenta, src);

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
	f = fopen("Studenti.txt", "r");
	char * token, file_buf[LINESIZE], sep_list[] = ",\n";

	while (fgets(file_buf, sizeof(file_buf), f)) {
		token = strtok(file_buf, sep_list);
		unsigned int idVarf = atoi(token);

		tmpLP = cautaNodLP(pListaAdiacenta, idVarf);

		token = strtok(NULL, sep_list);
		tmpLP->stud.id = atoi(token);

		token = strtok(NULL, sep_list);
		tmpLP->stud.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(tmpLP->stud.nume, token);

		token = strtok(NULL, sep_list);
		strcpy(tmpLP->stud.nrGrupa, token);

		token = strtok(NULL, sep_list);
		if (token)
			printf("\nEroare preluare token!");
	}

	// parsare lista de adiacenta
	tmpLP = pListaAdiacenta;
	while (tmpLP) {

		printf("\nVarf %d(%d) cu vecinii: ", tmpLP->idVarf, tmpLP->stud.id);

		NodLS* tmpLS = tmpLP->primListaVecini;
		while (tmpLS) {
			printf(" %d", tmpLS->idNodAdiacent);

			tmpLS = tmpLS->next;
		}

		tmpLP = tmpLP->next;
	}

	printf("\n\n");
	fclose(f);
}


