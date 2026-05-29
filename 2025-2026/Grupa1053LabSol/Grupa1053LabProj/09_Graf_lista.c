#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct NodLS
{
	unsigned char id_adiacent;
	struct NodLS* next;
};

struct NodLP
{
	unsigned char id_varf;
	struct NodLP* next;
	struct NodLS* prim_lista_sec; // lista de varfuri adiacente varfului id_varf stocat in NodLP
};

typedef struct NodLS NodLS;
typedef struct NodLP NodLP;

NodLP* inserareNodLP(NodLP* lista, unsigned char id)
{
	NodLP* nou = malloc(sizeof(NodLP));

	nou->id_varf = id;
	nou->next = NULL;
	nou->prim_lista_sec = NULL;

	if (lista == NULL) return nou;

	NodLP* temp = lista;
	while (temp->next != NULL) temp = temp->next;

	temp->next = nou;

	return lista;
}


NodLS* inserareNodLS(NodLS* lista_sec, unsigned char id_varf)
{
	NodLS* nou = malloc(sizeof(NodLS));

	nou->id_adiacent = id_varf;
	nou->next = lista_sec;

	return nou;
}

NodLS* push(NodLS* list, unsigned char varf)
{
	NodLS* nou = (NodLS*)malloc(sizeof(NodLS));

	nou->id_adiacent = varf;
	nou->next = list;

	return nou;
}

NodLS* pop(NodLS* list, unsigned char* varf_extras)
{
	if (list)
	{
		*varf_extras = list->id_adiacent;

		NodLS* temp = list;
		list = list->next;

		free(temp);
	}

	return list;
}

unsigned char* traversare_DF(NodLP* graf, unsigned char nr_varfuri, unsigned char varf_start)
{
	unsigned char* VIS = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	unsigned char* out = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));
	unsigned char k = 0; // offset curent pentru vectorul out (banda de iesire)

	for (unsigned char i = 0; i < nr_varfuri; i++)
		VIS[i] = 0;

	NodLS* stack = NULL; // structura de date temporara pentru stocare id varfuri care urmeaza sa fie vizitate/prelucrate in mod DF
	stack = push(stack, varf_start);
	VIS[varf_start - 1] = 1; // comutare flag pentru varf_start
	while (stack != NULL)
	{
		unsigned char varfe;
		stack = pop(stack, &varfe); // se extrage varful de graf de pe stiva
		out[k++] = varfe;

		// identificare si salvare pe stiva a vafurilor adiacente lui varfe
		NodLP* temp = graf;
		unsigned char flag_gasit = 0;
		while (temp != NULL && flag_gasit == 0)
		{
			if (temp->id_varf == varfe)
			{
				// varfuri adiacente lui varfe trebuie verificate in raport cu VIS si, eventual, puse in coada
				NodLS* temp_secundar = temp->prim_lista_sec;
				while (temp_secundar != NULL)
				{
					if (VIS[temp_secundar->id_adiacent - 1] == 0)
					{
						// temp_secundar->id_adiacent nu a mai trecut prin coada anterior
						VIS[temp_secundar->id_adiacent - 1] = 1;
						stack = push(stack, temp_secundar->id_adiacent);
					}
					temp_secundar = temp_secundar->next;
				}

				flag_gasit = 1;
			}
			else
				temp = temp->next;
		}

	}

	// dezalocare vector VIS
	free(VIS);

	return out;
}

int main()
{
	FILE* f = fopen("Graf.txt", "r");

	unsigned char nr_varfuri;
	fscanf(f, "%hhu", &nr_varfuri);

	NodLP* graf_lista = NULL;
	for (unsigned char i = 1; i <= nr_varfuri; i++)
	{
		graf_lista = inserareNodLP(graf_lista, i);
	}

	while (!feof(f))
	{
		unsigned char src, dst;
		fscanf(f, "%hhu,%hhu", &src, &dst);

		// inserare [src,dst]
		NodLP* temp = graf_lista;
		unsigned char flag_traversare = 0;
		while (temp != NULL && flag_traversare == 0) // parsare lista principala cu varfuri din graf
		{
			if (temp->id_varf == src)
			{
				// a fost identificat varful incident spre exterior
				temp->prim_lista_sec = inserareNodLS(temp->prim_lista_sec, dst); // inserare dst in lista de varfuri adiacente pentru src

				flag_traversare = 1;
			}
			else
				temp = temp->next;
		}

		// inserare [dst,src]
		temp = graf_lista;
		flag_traversare = 0;
		while (temp != NULL && flag_traversare == 0) // parsare lista principala cu varfuri din graf
		{
			if (temp->id_varf == dst)
			{
				// a fost identificat varful incident spre exterior (dst)
				temp->prim_lista_sec = inserareNodLS(temp->prim_lista_sec, src); // inserare src in lista de varfuri adiacente pentru dst

				flag_traversare = 1;
			}
			else
				temp = temp->next;
		}

	}

	fclose(f);

	printf("Lista de liste pentru stocare graf:\n");
	NodLP* temp = graf_lista;
	while (temp != NULL)
	{
		printf("Varfuri adiacente pentru varful %d: ", temp->id_varf);

		NodLS* temp_sec = temp->prim_lista_sec;
		while (temp_sec != NULL)
		{
			printf(" %d ", temp_sec->id_adiacent);
			temp_sec = temp_sec->next;
		}

		temp = temp->next;
		printf("\n");
	}

	// traversare Depth-First a grafului
	unsigned char* outputDF = traversare_DF(graf_lista, nr_varfuri, 2);
	printf("\nSuccesiune varfuri prelucrate conform DF: ");
	for (unsigned char i = 0; i < nr_varfuri; i++)
		printf(" %d", outputDF[i]);
	printf("\n\n");
	// dezalocare vector cu varfuri prelucrate conform DF
	free(outputDF);

	// dezalocare lista de liste (lista de adiacenta)
	return 0;
}