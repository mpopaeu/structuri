#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct NodLS {
	unsigned char id_adiacent;
	struct NodLS* next;
};


struct NodLP {
	unsigned char id_varf;
	struct NodLP* next;
	struct NodLS* lista_secundara;
};

typedef struct NodLS NodLS;
typedef struct NodLP NodLP;

NodLP* inserareNodLP(NodLP* lista, unsigned char varf)
{
	NodLP* nou = malloc(sizeof(NodLP));

	nou->id_varf = varf;
	nou->next = NULL;
	nou->lista_secundara = NULL; // lista secundara cu id varfuri adiacente lui varf

	if (lista == NULL) return nou;

	NodLP* temp = lista;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = nou;
	return lista;
}

NodLS* inserareNodLS(NodLS* lista, unsigned char varf_adiacent)
{
	NodLS* nou = malloc(sizeof(NodLS));

	nou->id_adiacent = varf_adiacent;
	nou->next = NULL;

	if (lista == NULL) return nou;

	NodLS* temp = lista;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = nou;
	return lista;
}

NodLS* put(NodLS* lista, unsigned char varf_adiacent)
{
	NodLS* nou = malloc(sizeof(NodLS));

	nou->id_adiacent = varf_adiacent;
	nou->next = NULL;

	if (lista == NULL) return nou;

	NodLS* temp = lista;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = nou;
	return lista;
}

NodLS* get(NodLS* lista, unsigned char* varf)
{
	if (lista != NULL)
	{
		NodLS* temp = lista;
		*varf = lista->id_adiacent;
		lista = lista->next;

		free(temp);
	}

	return lista;
}

unsigned char* traversare_BF(NodLP* graf, unsigned char *nr_varfuri, unsigned char varf_start)
{
	*nr_varfuri = 0;
	NodLP* temp = graf;
	while (temp != NULL)
	{
		*nr_varfuri += 1;
		temp = temp->next;
	}
	unsigned char* VIS = (unsigned char*)malloc(*nr_varfuri * sizeof(unsigned char));
	unsigned char* out = (unsigned char*)malloc(*nr_varfuri * sizeof(unsigned char));
	unsigned char k = 0; // offset curent pentru vectorul out (banda de iesire)

	for (unsigned char i = 0; i < *nr_varfuri; i++)
		VIS[i] = 0;

	NodLS* queue = NULL;
	queue = put(queue, varf_start);
	VIS[varf_start - 1] = 1; // comutare flag pentru varf_start
	while (queue != NULL)
	{
		unsigned char varfe;
		queue = get(queue, &varfe); // se extrage varful de graf de pe stiva
		out[k++] = varfe;

		// identificare si salvare pe stiva a vafurilor adiacente lui varfe
		temp = graf;
		unsigned char flag_gasit = 0;
		while (temp != NULL && flag_gasit == 0)
		{
			if (temp->id_varf == varfe)
			{
				// varfuri adiacente lui varfe trebuie verificate in raport cu VIS si, eventual, puse in coada
				NodLS* temp_secundar = temp->lista_secundara;
				while (temp_secundar != NULL)
				{
					if (VIS[temp_secundar->id_adiacent - 1] == 0)
					{
						// temp_secundar->id_adiacent nu a mai trecut prin coada anterior
						VIS[temp_secundar->id_adiacent - 1] = 1;
						queue = put(queue, temp_secundar->id_adiacent);
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

	NodLP* graf_lista = NULL;
	unsigned char nr_varfuri;
	fscanf(f, "%hhu", &nr_varfuri);

	for (unsigned char i = 1; i <= nr_varfuri; i++)
	{
		graf_lista = inserareNodLP(graf_lista, i);
	}

	while (!feof(f))
	{
		unsigned char src, dst;
		fscanf(f, "%hhu,%hhu", &src, &dst);

		// inserare muchie (src, dst)
		NodLP* temp = graf_lista;
		unsigned char flag_inserare = 0;
		while (temp != NULL && flag_inserare == 0)
		{
			if (temp->id_varf == src )
			{
				temp->lista_secundara = inserareNodLS(temp->lista_secundara, dst);
				flag_inserare = 1;
			}
			else
				temp = temp->next;
		}
		
		// inserare muchie (dst, src)
		temp = graf_lista;
		flag_inserare = 0;
		while (temp != NULL && flag_inserare == 0)
		{
			if (temp->id_varf == dst)
			{
				temp->lista_secundara = inserareNodLS(temp->lista_secundara, src);
				flag_inserare = 1;
			}
			else
				temp = temp->next;
		}
	}

	printf("Continut structura lista-de-liste: \n");
	NodLP* temp = graf_lista;
	while (temp != NULL)
	{
		printf("\nNodul %d are varfuri adiacente: ", temp->id_varf);
		NodLS* temp_secundar = temp->lista_secundara;
		while (temp_secundar != NULL)
		{
			printf(" %d ", temp_secundar->id_adiacent);
			temp_secundar = temp_secundar->next;
		}

		temp = temp->next;
	}

	fclose(f);

	printf("\nTraversare BF: ");
	unsigned char vector_size;
	unsigned char* output = traversare_BF(graf_lista, &vector_size, 7);
	for (unsigned char i = 0; i < vector_size; i++)
		printf(" %d ", output[i]);

	// dezalocare lista-de-liste
	
	while (graf_lista != NULL)
	{
		temp = graf_lista;
		graf_lista = graf_lista->next;
		// dezalocam nodul temp impreuna cu lista secundara agatata de acesta
		// dezalocare lista secundara de varfuri adiacente
		while (temp->lista_secundara != NULL)
		{
			NodLS* temp_secundar = temp->lista_secundara;
			temp->lista_secundara = temp->lista_secundara->next;

			free(temp_secundar);
		}
		// dezalocare nod din lista principala
		free(temp);
	}

	// dezalocare vector rezultat traversare BF

	return 0;
}