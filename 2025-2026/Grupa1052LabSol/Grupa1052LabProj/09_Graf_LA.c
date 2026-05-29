#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>

struct NodLS // structura nod lista secundara
{
	unsigned char id_adiacent;
	struct NodLS* next;
};

struct NodLP // structura nod lista principala
{
	unsigned char id_varf;
	struct NodLP* next;
	struct NodLS* prim_lista_adiac;
};

typedef struct NodLP NodLP;
typedef struct NodLS NodLS;

NodLP* inserareNodLP(NodLP* lista, unsigned char varf)
{
	NodLP* nou = malloc(sizeof(NodLP));

	nou->id_varf = varf;
	nou->next = NULL;
	nou->prim_lista_adiac = NULL; // initial, lista de muchii este empty

	if (lista == NULL) return nou;

	NodLP* temp = lista;
	while (temp->next != NULL) temp = temp->next;

	temp->next = nou; // legarea lui nou la lista existenta la sfarsit

	return lista;
}

NodLS* inserareNodLS(NodLS* lista, unsigned char id_varf_adiacent)
{
	NodLS* nou = malloc(sizeof(NodLS));

	nou->next = lista;
	nou->id_adiacent = id_varf_adiacent;

	return nou; // inserare la inceput in lista secundara
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
				NodLS* temp_secundar = temp->prim_lista_adiac;
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
		graf_lista = inserareNodLP(graf_lista, i);

	while (!feof(f))
	{
		unsigned char src, dst;
		fscanf(f, "%hhu,%hhu", &src, &dst);

		// inserare muchie src,dst in lista de adiacenta
		NodLP* temp = graf_lista;
		unsigned char flag_inserare = 0;
		while (temp != NULL && flag_inserare == 0)
		{
			if (temp->id_varf == src)
			{
				// temp contine id nod dat de src
				temp->prim_lista_adiac = inserareNodLS(temp->prim_lista_adiac, dst); // inserare dst in lista secundara a nodului src

				flag_inserare = 1;
			}
			else
				temp = temp->next;
		}

		// inserare muchie dst,src in lista de adiacenta
		// graf neorientat -> matrice de adiacenta simetrica in raport cu diagonala principala
		temp = graf_lista;
		flag_inserare = 0;
		while (temp != NULL && flag_inserare == 0)
		{
			if (temp->id_varf == dst)
			{
				// temp contine id nod dat de dst
				temp->prim_lista_adiac = inserareNodLS(temp->prim_lista_adiac, src); // inserare src in lista secundara a nodului dst

				flag_inserare = 1;
			}
			else
				temp = temp->next;
		}
	}

	fclose(f);


	printf("Lista de adiacenta este:\n");
	NodLP* temp = graf_lista;
	while (temp != NULL)
	{
		printf("\nVarfurile adiacente pentru vaful %d sunt: ", temp->id_varf);
		NodLS* temp_sec = temp->prim_lista_adiac;
		while (temp_sec != NULL)
		{
			printf(" %d", temp_sec->id_adiacent);

			temp_sec = temp_sec->next;
		}


		temp = temp->next;
	}

	// traversare Depth-First a grafului
	unsigned char* outputDF = traversare_DF(graf_lista, nr_varfuri, 2);
	printf("\nSuccesiune varfuri prelucrate conform DF: ");
	for (unsigned char i = 0; i < nr_varfuri; i++)
		printf(" %d", outputDF[i]);
	printf("\n\n");
	// dezalocare vector cu varfuri prelucrate conform DF
	free(outputDF);

	// dezalocare lista de adiacenta
	while (graf_lista != NULL)
	{
		temp = graf_lista; // temp este nodul 1
		graf_lista = graf_lista->next; // graf_lista este nodul 2 SAU NULL

		while (temp->prim_lista_adiac != NULL)
		{
			NodLS* temp_sec = temp->prim_lista_adiac; // temp_sec este nodul 1 din lista secundara
			temp->prim_lista_adiac = temp->prim_lista_adiac->next; // inceputul listei secundare este mutat pe nodul 2 SAU NULL

			free(temp_sec);
		}

		// lista secundara este dezalocata complet
		free(temp);
	}

	if (graf_lista == NULL)
		printf("\nLista de adiacenta a fost dezalocata!\n\n");

	return 0;
}
