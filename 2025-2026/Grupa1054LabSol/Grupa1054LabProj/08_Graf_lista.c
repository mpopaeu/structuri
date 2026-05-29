#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct NodLS {
	unsigned char varf_adiacent;
	struct NodLS* next;
};

struct NodLP {
	unsigned char varf;
	struct NodLS* prim_listasec;
	struct NodLP* next;
};

typedef struct NodLP NodLP;
typedef struct NodLS NodLS;

NodLP* inserareNodLP(NodLP* lista, unsigned char id_varf)
{
	NodLP* nou = malloc(sizeof(NodLP));

	nou->varf = id_varf;
	nou->next = NULL;
	nou->prim_listasec = NULL;

	if (lista == NULL)
		return nou;

	NodLP* temp = lista;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = nou;
	return lista;
}

NodLS* inserareNodLS(NodLS* lista, unsigned char id_adiacent)
{
	NodLS* nou = malloc(sizeof(NodLS));
	nou->varf_adiacent = id_adiacent;
	nou->next = lista;

	return nou;
}

NodLS* push(NodLS* stack, unsigned char id_adiacent)
{
	NodLS* nou = malloc(sizeof(NodLS));
	nou->varf_adiacent = id_adiacent;
	nou->next = stack;

	return nou;
}

NodLS* pop(NodLS* stack, unsigned char *id_varf)
{
	if (stack != NULL)
	{
		*id_varf = stack->varf_adiacent;
		NodLS* temp = stack;
		stack = stack->next;

		free(temp);
	}
	
	return stack;
}

unsigned char* traversare_DF(NodLP* graf, unsigned char varf_start, unsigned char * size_vector)
{
	
	// determinare nr de noduri din lista principala
	*size_vector = 0;
	NodLP* temp = graf;
	while (temp != NULL)
	{
		*size_vector += 1;
		temp = temp->next;
	}

	unsigned char* VIS = (unsigned char*)malloc(*size_vector * sizeof(unsigned char));
	unsigned char* out = (unsigned char*)malloc(*size_vector * sizeof(unsigned char));
	unsigned char k = 0; // offset curent pentru vectorul out (banda de iesire)

	for (unsigned char i = 0; i < *size_vector; i++)
		VIS[i] = 0;

	NodLS* stack = NULL;
	stack = push(stack, varf_start);
	VIS[varf_start - 1] = 1; // comutare flag pentru varf_start
	while (stack)
	{
		unsigned char varfe;
		stack = pop(stack, &varfe); // se extrage varful de graf de pe stiva
		out[k++] = varfe;

		// identificare si salvare pe stiva a vafurilor adiacente lui varfe
		temp = graf;
		unsigned char verificat = 0;
		while (temp != NULL && verificat == 0)
		{
			if (temp->varf == varfe)
			{
				NodLS* temp_sec = temp->prim_listasec;
				while (temp_sec != NULL)
				{
					if (VIS[temp_sec->varf_adiacent - 1] == 0)
					{
						// varf adiacent trebui pus pe stiva
						VIS[temp_sec->varf_adiacent - 1] = 1;
						stack = push(stack, temp_sec->varf_adiacent);
					}

					temp_sec = temp_sec->next;
				}

				verificat = 1;
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

	for (unsigned char i = 0; i < nr_varfuri; i++)
		graf_lista = inserareNodLP(graf_lista, (unsigned char)(i + 1));

	while (!feof(f))
	{
		unsigned char src, dst;
		fscanf(f, "%hhu,%hhu", &src, &dst);

		NodLP* temp = graf_lista;
		unsigned char inserat = 0;
		while (temp != NULL && inserat ==0)
		{
			if (temp->varf == src)
			{
				NodLS* temp_sec = temp->prim_listasec;
				temp->prim_listasec = inserareNodLS(temp->prim_listasec, dst);
				inserat = 1;
			}
			else
				temp = temp->next;
		}

		temp = graf_lista;
		inserat = 0;
		while (temp != NULL && inserat == 0)
		{
			if (temp->varf == dst)
			{
				NodLS* temp_sec = temp->prim_listasec;
				temp->prim_listasec = inserareNodLS(temp->prim_listasec, src);
				inserat = 1;
			}
			else
				temp = temp->next;
		}
	}
	fclose(f);

	printf("\nContinut structura lista-de-liste pentru stocare graf:\n");

	NodLP* temp = graf_lista;
	while (temp != NULL)
	{
		printf("\nNodul %d din graf cu noduri adiacente: ", temp->varf);
		NodLS* temp_sec = temp->prim_listasec;
		while (temp_sec != NULL)
		{
			printf(" %d", temp_sec->varf_adiacent);
			temp_sec = temp_sec->next;
		}

		temp = temp->next;
	}

	unsigned char* output_DF = NULL, output_size;
	output_DF = traversare_DF(graf_lista, 4, &output_size);
	printf("\n\nRezultat parsare graf DF:");
	for (unsigned char i = 0; i < output_size; i++)
		printf(" %d ", output_DF[i]);


	//dezalocare structura lista de adiacenta
	temp = graf_lista;
	while (temp != NULL)
	{
		// dezalocare lista secundara agatata de temp in lista principala
		while (temp->prim_listasec != NULL)
		{
			NodLS* temp_sec = temp->prim_listasec;
			temp->prim_listasec = temp->prim_listasec->next;

			free(temp_sec);
		}

		temp = temp->next;
	}

	// dezalocare lista principala
	while (graf_lista != NULL)
	{
		temp = graf_lista;
		graf_lista = graf_lista->next;

		free(temp);
	}

	// dezalocare vector rezultat din traversare DF
	free(output_DF);

	return 0;
}