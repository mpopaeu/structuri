#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct Nod Nod;
typedef struct NodLS NodLS;
typedef struct NodLP NodLP;

// Node structure of the main simple list
struct NodLS;
struct NodLP {
	unsigned int idVarf;
	NodLS* primListaVecini;
	NodLP* next;
};

// Node structure of the secondary simple list (adjacent vertices of the vertex 
// stored by corresponding node in main list)
struct NodLS {
	unsigned int idNodAdiacent;
	NodLS* next;
};

// Mode structure of the stack data structure
struct Nod {
	unsigned int idVarf;
	Nod* next;
};

// insert node into adjacent vertices list
NodLS* inserareNodLS(NodLS* pLS, unsigned int id) {
	NodLS* nou = (NodLS*)malloc(sizeof(NodLS));
	nou->idNodAdiacent = id;
	nou->next = 0;

	if (!pLS) { // list is empty
		return nou;
	}
	else {
		// parse list untill the end 
		NodLS* tmp = pLS;
		while (tmp->next)
			tmp = tmp->next;

		tmp->next = nou;
	}

	return pLS;
}

// insert node into the main list
NodLP* inserareNodLP(NodLP* pLP, unsigned int id, NodLS* pLstVecini) {
	NodLP* nou = (NodLP*)malloc(sizeof(NodLP));
	nou->idVarf = id;
	nou->primListaVecini = pLstVecini;
	nou->next = 0;

	if (!pLP) { // list is empty
		return nou;
	}
	else {
		// parse list untill the last node in the chain
		NodLP* tmp = pLP;
		while (tmp->next)
			tmp = tmp->next;

		tmp->next = nou;
	}

	return pLP;
}

// search for a specific vertex int the main list 
NodLP* cautaNodLP(NodLP* pLP, unsigned int idCautat) {
	NodLP* tmp = pLP;
	while (tmp) {
		if (tmp->idVarf == idCautat)
			return tmp; // returns the node address where idCautat is placed into

		tmp = tmp->next;
	}

	return tmp; // tmp is NULL when idCautat is not found out in the main list
}

// push a vertex onto a stack data structure
Nod* push(Nod* stack, unsigned int varf)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->idVarf = varf;
	nou->next = stack;

	return nou;
}

// delete the top of the stack; save the stored vertex from the deleted top
Nod* pop(Nod* stack, unsigned int* varf)
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

// parse the graph in Depth-First way
unsigned int* DF(NodLP* pLP, unsigned int start, unsigned int nrVarfuri) {
	unsigned int* flags, * output, k = 0;
	Nod* stack = 0;

	// allocation of array of flags (to know if a vertex has been saved onto the stack data structure)
	flags = (unsigned int*)malloc(nrVarfuri * sizeof(unsigned int));
	// initialize the items of the array of flags
	for (unsigned int i = 0; i < nrVarfuri; i++)
		flags[i] = 0;

	// allocation of the output stream containing the order of vertices according to DF
	output = (unsigned int*)malloc(nrVarfuri * sizeof(unsigned int));

	// push the starting vertex to make the traversal
	stack = push(stack, start);
	flags[start - 1] = 1;

	while (stack) {
		unsigned int varf;
		// get the vertex from top of the stack
		stack = pop(stack, &varf);

		// save the vertex into the output stream 
		output[k] = varf;
		k = k + 1;

		// search the adjacent vertices for the above extracted vertex 
		// search the extracted vertex in the main list to get the adjacent vertices secondary list 
		NodLP* tmpLP = cautaNodLP(pLP, varf);
		NodLS* tmpLS = tmpLP->primListaVecini; // access to the adjacent vertices list
		while (tmpLS)
		{

			// push adjacent vertices having the visiting flag on null
			int vecin = tmpLS->idNodAdiacent;
			if (flags[vecin - 1] == 0)
			{
				// save the adjacent vertex onto the stack data structure 
				stack = push(stack, vecin);
				// switch the flag as visited vertex
				flags[vecin - 1] = 1;
			}

			tmpLS = tmpLS->next;
		}

	}

	return output;
}

// TO DO: function for Breadth-First

// TO DO: function for put operation on queue

// TO DO: function for get operation on queue

void main() {
	FILE* f;
	f = fopen("Graph.txt", "r");

	char buffer[128];
	fgets(buffer, sizeof(buffer), f);

	NodLP* pListaAdiacenta = 0;
	unsigned int nrVarfuri = 0;

	sscanf(buffer, "%d", &nrVarfuri); // number of vertices taken over the first line in the file
	for (unsigned int i = 1; i <= nrVarfuri; i++)
		pListaAdiacenta = inserareNodLP(pListaAdiacenta, i, NULL); // create one node in main list for one single vertex


	while (fgets(buffer, sizeof(buffer), f)) {
		unsigned int src, dst;
		sscanf(buffer, "%d %d", &src, &dst);

		NodLP* tmpLP = cautaNodLP(pListaAdiacenta, src);

		if (tmpLP) {
			// idVarf is src
			tmpLP->primListaVecini = inserareNodLS(tmpLP->primListaVecini, dst); // insert the edge (src, dst)

			// insert the reverse relation the edge (dst, src)
			// search the dst vertex in main list 
			tmpLP = cautaNodLP(pListaAdiacenta, dst);
			tmpLP->primListaVecini = inserareNodLS(tmpLP->primListaVecini, src); // insert the edge (dst, src)
		}
		else {
			// vertex with src does not exist in the main list
			printf("\nSearched vertex having id %d does not exist in the main list.\n", src);
		}
	}

	// print out the adjacency list
	NodLP* tmpLP = pListaAdiacenta;
	while (tmpLP) {

		printf("\nVertex %d having adjacent vertices: ", tmpLP->idVarf);

		NodLS* tmpLS = tmpLP->primListaVecini;
		while (tmpLS) {
			printf(" %d ", tmpLS->idNodAdiacent);

			tmpLS = tmpLS->next;
		}

		tmpLP = tmpLP->next;
	}
	unsigned int* trav_array = DF(pListaAdiacenta, 1, nrVarfuri);

	printf("\n\nGraph in DF mode:");
	for (unsigned int i = 0; i < nrVarfuri; i++)
		printf(" %u", trav_array[i]);

	// deallocate trav_array
	free(trav_array);


	//trav_array = BF(pListaAdiacenta, 1, nrVarfuri);
	//printf("\n\nGraph in BF mode:");
	//for (unsigned int i = 0; i < nrVarfuri; i++)
	//	printf(" %u", trav_array[i]);
	//// deallocate trav_array
	//free(trav_array);

	printf("\n\n");
	fclose(f);
}


