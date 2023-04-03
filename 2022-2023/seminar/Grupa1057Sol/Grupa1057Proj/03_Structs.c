#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define VECTOR_SIZE 10
#define BUFFER_SIZE 256

struct ContBancar
{
	char iban[25];
	char* titular;
	char moneda[4];
	float sold;
	unsigned int nr_carduri;
};

struct Nod
{
	char moneda[4];
	double sold_total;
	struct Nod *next;
};

struct Nodt
{
	char* titular;
	unsigned int nr_carduri;
	struct Nodt* next;
};

struct NodCB
{
	struct ContBancar cb;
	struct NodCB* next;
};

struct NodStiva
{
	struct NodCB* p_nod;
	struct NodStiva* next;
};

struct Nod* inserare_inceputLS(struct Nod* p, struct ContBancar cb)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	strcpy(nou->moneda, cb.moneda);
	nou->sold_total = cb.sold;
	nou->next = p;

	return nou;
}

// functie pentru determinare solduri conturi bancare grupate pe moneda
// conturile utilizate sunt cele stocate in vectorul vcd

struct Nod* solduri_conturi(struct ContBancar* vcb, unsigned char nr_conturi)
{
	struct Nod* primNod = NULL; // lista simpla nu contine nici un nod (empty)

	for (unsigned char i = 0; i < nr_conturi; i++)
	{
		struct Nod* t = primNod;
		char gasit = 0;
		while (t && (gasit == 0))
		{
			if (strcmp(vcb[i].moneda, t->moneda) == 0)
			{
				// string-uri identice pentru moneda
				gasit = 1;
				t->sold_total += vcb[i].sold;
			}
			t = t->next; // modificare t cu adresa nodului succesor
		}

		if (gasit == 0)
		{
			// nu a fost identificat nod cu moneda din vcb[i]
			// nod nou se insereaza in lista simpla gestionata cu primNod
			primNod = inserare_inceputLS(primNod, vcb[i]);
		}
	}

	return primNod;
}

// functie determinare numar de carduri per titular cont
//struct Nodt* titulari_carduri(struct ContBancar* vcb, unsigned char nr_conturi)
//{
//	// pentru fiecare cont bancar din vector:
//	// 1. se verifica daca titular este in lista Nodt
//	// 2. DA, se incrementeaza nr carduri din nod aferent listei Nodt
//	// 3. NU, se adauga titular in lista Nodt si se initializeaza nr carduri din noul nod
//
//	// se face return pe adresa de inceput a nii liste
//}


// "inchidere" conturi bancare cu sold nul (se efectueaza pe vector)
//unsigned char inchidere_conturi_sold_nul(struct ContBancar* vcb, unsigned char nr_conturi)
//{
//	// pentru fiecare cont bancar din vector:
//	// 1. se verifica daca sold este nul
//	// 2. DA, se dezaloca titular cont, se shift-eaza la stanga conturile ramase (i+1, n), 
//	// se actualizeaza numar de conturi
//	// 3. NU, se trece la verificarea urmatorului cont din vector
//
//	// se face return pe valoarea actualizata a numarul de conturi din vector
//}

// stergere nod din lista simpla (2 cerinte)
struct Nod* stergere_nod(struct Nod* p)
{
	if (p) // exista cel putin 1 nod in lista simpla
	{
		struct Nod* t = p;
		p = p->next;

		free(t);
	}

	return p;
}

struct Nodt* stergere_nodt(struct Nodt* p)
{
	if (p) // exista cel putin 1 nod in lista simpla
	{
		struct Nodt* t = p;
		p = p->next;

		free(t->titular);
		free(t);
	}

	return p;
}

// stergere lista simpla (2 versiuni pentru 2 tipuri de liste simpla)
struct Nod* sterege_lista_nod(struct Nod* p)
{
	while (p)
	{
		p = stergere_nod(p);
	}

	return p;
}


struct Nodt* sterege_lista_nodt(struct Nodt* p)
{
	while (p)
	{
		p = stergere_nodt(p);
	}

	return p;
}

// inserare cont bancar in lista simpla (de conturi bancare) astfel incat
// nodurile sa fie sortate crescator in functie de sold
// inserare de nod in interiorul listei simple
struct NodCB* inserare_interior_sort_sold(struct NodCB* p, struct ContBancar cb)
{
	struct NodCB* cont_nou = (struct NodCB*)malloc(sizeof(struct NodCB));
	cont_nou->cb = cb;
	cont_nou->cb.titular = (char*)malloc(strlen(cb.titular) + 1);
	strcpy(cont_nou->cb.titular, cb.titular);

	if (p == NULL || p->cb.sold>=cb.sold)
	{
		cont_nou->next = p;
		p = cont_nou;
	}
	else
	{
		struct NodCB* t = p;
		char gasit = 0;
		while (t->next && gasit == 0)
		{
			if (t->next->cb.sold > cb.sold)
				gasit = 1;
			else
				t = t->next;
		}

		//t este nodul din fata nodului de inserat
		cont_nou->next = t->next;
		t->next = cont_nou;
	}

	return p;
}

// varianta cu sold descrescator
// crearea si consumarea oneshot a unei structuri de tip stiva
// LiFo - inserarea si stergerea unui nod la inceputul listei simple (structura suport pentru stiva)
struct NodStiva* push(struct NodStiva* stiva, struct NodCB* p_cb)
{
	// inserare nod cu adresa de nod din lista conturi bancare la inceputul structurii suport (lista simpla)
	struct NodStiva* nod_nou = (struct NodStiva*)malloc(sizeof(struct NodStiva));
	nod_nou->p_nod = p_cb;
	nod_nou->next = stiva;

	return nod_nou;
}

struct NodStiva* pop(struct NodStiva* stiva, struct NodCB** nod_extras)
{
	// stergere nod de la inceputul structurii suport (lista simpla)
	if (stiva)
	{
		struct NodStiva* t = stiva;
		stiva = stiva->next;
		*nod_extras = t->p_nod;
		free(t);
	}

	return stiva;
}

int main()
{

	struct ContBancar cb, vcb[VECTOR_SIZE];
	FILE* f;
	unsigned int i = 0;
	unsigned char nr_conturi;

	f = fopen("Conturi.txt", "r");

	char buffer[BUFFER_SIZE], seps[]=",\n";

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		char* token;
		token = strtok(buffer, seps);
		strcpy(cb.iban, token);

		token = strtok(NULL, seps);
		cb.titular = (char*)malloc(strlen(token) + 1); // +1 pentru terminat de string, adica byte 0x00
		strcpy(cb.titular, token);

		token = strtok(NULL, seps);
		strcpy(cb.moneda, token);

		token = strtok(NULL, seps);
		cb.sold = atof(token);

		token = strtok(NULL, seps);
		cb.nr_carduri = atoi(token);

		vcb[i++] = cb;
	}

	nr_conturi = (unsigned char)i;

	struct Nod* primNod = NULL;

	primNod = solduri_conturi(vcb, nr_conturi); // i este ultima valoare din secventa de preluare date din fisier

	struct Nodt* primTit = NULL;
	//primTit = titulari_carduri(vcb, nr_conturi); // creare lista de titulari cu ne carduri asociate

	//creare lista noduri bancare cu lista sortata dupa sold
	struct NodCB* primCB = NULL;
	for (i = 0; i < nr_conturi; i++)
	{
		primCB = inserare_interior_sort_sold(primCB, vcb[i]);
	}

	struct NodCB* t = primCB;
	printf("Lista conturi bancare sortate crescator\n");

	while (t)
	{
		printf("%s %.2f \n", t->cb.iban, t->cb.sold);
		t = t->next;
	}

	//Prelucrare conturi bancare in ordine descrescatoare a soldului

	//creare stiva cu referinta la nodurile din lista de conturi bancare
	t = primCB;
	struct NodStiva* stiva = NULL;
	while (t)
	{
		stiva = push(stiva, t);
		t = t->next;
	}

	//Prelucrare dat din stiva

	printf("Lista conturi bancare sortate descrescator\n");
	while (stiva)
	{
		stiva = pop(stiva, &t);
		printf("%s %.2f\n", t->cb.iban, t->cb.sold);
	}


	/*nr_conturi = inchidere_conturi_sold_nul(vcb, nr_conturi);
	printf("Vector conturi bancare dupa eliminare conturi cu sold nul:\n");
	for (i = 0; i < nr_conturi; i++)
		printf("%s %f\n", vcb[i].titular, vcb[i].sold);*/

	//dezalocare lista solduri
	while (primNod)
	{
		struct Nod* t = primNod;
		primNod = primNod->next;
		free(t);
	}

	//dezalocare lista conturi bancare
	while (primCB)
	{
		struct NodCB* t_CB = primCB;
		primCB = primCB->next;
		free(t_CB->cb.titular);
		free(t_CB);
	}

	//dezalocare titulari din vector
	for (i = 0; i < nr_conturi; i++)
	{
		free(vcb[i].titular);
	}

	fclose(f);
	return 0;
}