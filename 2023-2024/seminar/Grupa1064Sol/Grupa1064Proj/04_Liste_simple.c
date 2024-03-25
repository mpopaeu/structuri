#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct ContBancar
{
	char iban[25]; // 24 bytes pt iban + 1 byte terminator string
	char moneda[4]; // 3 bytes pt cod moneda + 1 byte terminator string
	char* titular;
	float sold;
};

struct Nod
{
	struct ContBancar cb;
	struct Nod* next;
};

typedef struct ContBancar ContBancar;
typedef struct Nod Nod;

Nod* inserare_sfarsit(Nod* p, ContBancar cont)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->cb = cont;
	nou->next = NULL;

	if (p == NULL)
		return nou;

	Nod* t = p;
	while (t->next != NULL)
		t = t->next;
	// t este ultimul nod din lista simpla p
	t->next = nou;

	return p;
}

// extensie pentru camp care poate avea valoare duplicata in lista simpla 
// titular, sold, moneda
Nod* interschimb_iban_adiacente(Nod* prim, char* cIBAN)
{
	if (prim == NULL || prim->next == NULL)
		return prim;

	if (strcmp(prim->cb.iban, cIBAN) == 0)
	{
		// se interschimba nodurile [1,2]
		Nod* p = prim, * q = prim->next, * s = q->next;
		p->next = s;
		q->next = p;
		prim = q;
	}
	else
	{
		// cazul general
		Nod* p = prim->next, * r = prim;
		while (p->next != NULL)
		{
			if (strcmp(p->cb.iban, cIBAN) == 0)
			{
				// iban exista in lista simpla
				Nod* q = p->next, * s = q->next;
				p->next = s;
				q->next = p;
				r->next = q;

				return prim;
			}
			else
			{
				r = r->next; // r = p;
				p = p->next;
			}
		}
	}

	return prim;
}


Nod* interschimb_iban_oarecare(Nod* prim, char* cIBAN1, char* cIBAN2)
{
	if (prim == NULL || prim->next == NULL)
		return prim;

	if (strcmp(prim->cb.iban, cIBAN1) == 0)
	{
		// cIBAN1 este pe nodul 1
		Nod* p = prim, *q, *t;
		if (strcmp(prim->next->cb.iban, cIBAN2) == 0)
		{
			// interschimb [1,2]
			return interschimb_iban_adiacente(prim, cIBAN1);
		}
		else
		{
			// interschimb [1, i]
			q = prim->next->next;
			t = prim->next;
			while (q)
			{
				if (strcmp(q->cb.iban, cIBAN2) == 0)
				{
					Nod* s = p->next, *w = q->next;
					p->next = w;
					q->next = s;
					t->next = p;
					return q;
				}
				else
				{
					q = q->next;
					t = t->next;
				}
			}
		}
	}
	else
	{
		if (strcmp(prim->cb.iban, cIBAN2) == 0)
		{
			Nod* p = prim;
			// cIBAN2 este pe nodul 1
			if (strcmp(prim->next->cb.iban, cIBAN1) == 0)
			{
				// interschimb [1,2]
				return interschimb_iban_adiacente(prim, cIBAN2);
			}
			else
			{
				Nod* q, * t;
				q = prim->next->next;
				t = prim->next;
				while (q)
				{
					if (strcmp(q->cb.iban, cIBAN1) == 0)
					{
						Nod* s = p->next, * w = q->next;
						p->next = w;
						q->next = s;
						t->next = p;
						return q;
					}
					else
					{
						q = q->next;
						t = t->next;
					}
				}
			}
		}
		else
		{
			// cazul [p, q]
			// 1. q == p->next (adiacente in interior)
			// 2. cazul general [cIBAN1,cIBAN2] sau [cIBAN2,cIBAN1]
		}
	}
}
int main()
{
	FILE* f = fopen("Conturi.txt", "r");
	Nod* prim = NULL;

	char nume_buff[128];
	struct ContBancar contB;
	fscanf(f, "%s\n", contB.iban);
	while (strlen(contB.iban))
	{
		fscanf(f, "%[^\n]", nume_buff);
		contB.titular = (char*)malloc(strlen(nume_buff) + 1);
		strcpy(contB.titular, nume_buff);

		fscanf(f, "%s", contB.moneda);
		fscanf(f, "%f", &contB.sold);

		// inserare nod in lista simpla
		prim = inserare_sfarsit(prim, contB);

		contB.titular = NULL; // pentru a elimina partajarea dintre ultimul nod inserat si contB
		contB.iban[0] = 0;
		fscanf(f, "%s\n", contB.iban);
	}

	Nod* t = prim;
	while (t != NULL)
	{
		printf("%s %s\n", t->cb.iban, t->cb.titular);
		t = t->next;
	}

	// interschimb noduri lista simpla cu modificare adrese de legatura
	prim = interschimb_iban_adiacente(prim, "RO04BRDE1234567890111222");
	printf("Lista simpla dupa interschimb:\n");
	t = prim;
	while (t != NULL)
	{
		printf("%s %s\n", t->cb.iban, t->cb.titular);
		t = t->next;
	}

	// dezalocare lista simpla
	while (prim)
	{
		t = prim;
		prim = prim->next;

		free(t->cb.titular);
		free(t);
	}
	printf("Lista simpla dupa dezalocare:\n");
	t = prim;
	while (t != NULL)
	{
		printf("%s %s\n", t->cb.iban, t->cb.titular);
		t = t->next;
	}
	
	fclose(f);
	return 0;
}