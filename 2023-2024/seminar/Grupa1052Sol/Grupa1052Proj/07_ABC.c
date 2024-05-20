#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ContBancar {
	unsigned short int cheie;
	char iban[25]; // 24 dim iban + 1 byte pt 0x00
	float sold;
	char moneda[4]; // 3 dim cod moneda + 1 byte pt 0x00
	char* titular;
};

struct NodABC
{
	struct ContBancar cont;
	struct NodABC *st, *dr;
};

typedef struct ContBancar ContBancar;
typedef struct NodABC NodABC;

NodABC* inserare_cont_ABC(NodABC* r, ContBancar data, unsigned char* inserat)
{
	if (r)
	{
		// continui cautarea locului de inserat
		if (r->cont.cheie > data.cheie)
			r->st = inserare_cont_ABC(r->st, data, inserat);
		else
			if (r->cont.cheie < data.cheie)
				r->dr = inserare_cont_ABC(r->dr, data, inserat);
			else
				*inserat = 0;

	}
	else
	{
		// am gasit locul de inserat pentru cont bancare data
		NodABC* nou = (NodABC*)malloc(sizeof(NodABC));
		nou->cont = data;
		nou->st = NULL;
		nou->dr = NULL;

		r = nou;
	}

	return r;
}

void inordine_ABC(NodABC * r)
{
	if (r)
	{
		inordine_ABC(r->st);
		printf("%d ", r->cont.cheie);
		inordine_ABC(r->dr);
	}
}

// I/ r nod din ABC (initial, r este nod redacina ABC
// I/ key cheia contului bancare care se cauta in ABC
// /O return adresa din NodABC a contului bancar cu key; altfel, NULL daca nu exista cont bancar cu key
ContBancar* cauta_cont_bancar(NodABC* r, unsigned short int key)
{
	ContBancar* pdata = NULL;
	if (r)
	{
		if (r->cont.cheie > key)
		{
			pdata = cauta_cont_bancar(r->st, key);
		}
		else
		{
			if (r->cont.cheie < key)
			{
				pdata = cauta_cont_bancar(r->dr, key);
			}
			else
			{
				pdata = &(r->cont);
			}
		}
	}

	return pdata;
}


NodABC* dezalocare_ABC(NodABC* r)
{
	if (r != NULL)
	{
		// parsare in post-ordine a ABC
		r->st = dezalocare_ABC(r->st);
		r->dr = dezalocare_ABC(r->dr);

		// dezalocare nod curent
		free(r->cont.titular);
		free(r);
		r = NULL;
	}

	return r;
}


// numarul de conturi bancare cu acelasi titular
unsigned char nr_conturi_titular(NodABC* r, char* titular)
{
	unsigned char nr_titulari = 0;
	if (r)
	{
		// traversare ABC in preordine
		// prelucrare nod curent r inainte de vizitare descendenti
		if (strcmp(titular, r->cont.titular) == 0)
		{
			nr_titulari += 1;
		}

		// vizitare descendenti si aplicare aceleiasi logici in fiecare nod din descendenti
		nr_titulari += nr_conturi_titular(r->st, titular);
		nr_titulari += nr_conturi_titular(r->dr, titular);
	}

	return nr_titulari;
}

NodABC* stergere_nod_cheie(NodABC* r, unsigned short int cheie, ContBancar *p_data)
{
	if (r)
	{
		if (cheie < r->cont.cheie)
			r->st = stergere_nod_cheie(r->st, cheie, p_data); // continuare cautare pe subarbore stanga
		else
			if (cheie > r->cont.cheie)
				r->dr = stergere_nod_cheie(r->dr, cheie, p_data); // continuare cautare pe subarbore dreapta
			else
			{
				// nodul r este nodul de sters
				// salvare date cont bancar
				*p_data = r->cont;
				if ((r->st == NULL) && (r->dr == NULL))
				{
					// 1. r este frunza
					// dezalocare nod
					free(r);
					r = NULL;
				}
				else
				{
					if ((r->st != NULL) && (r->dr != NULL))
					{
						// 3. r cu 2 descendenti 
						// caut cel mai din dreapta nod (cheie maxima) din subarbore stanga
						NodABC* temp, * parinte_temp = NULL;
						// alegere subarbore stanga
						temp = r->st;
						while (temp->dr)
						{
							parinte_temp = temp;
							temp = temp->dr;
						}

						// rescriere r cu datele din temp
						r->cont = temp->cont;
						if (parinte_temp != NULL)
						{
							parinte_temp->dr = temp->st;
						}
						else
						{
							// radacina de subarbore stanga este cu cheie maxima
							r->st = temp->st;
						}
						// dezalocare nod temp
						free(temp);
					}
					else
					{
						// 2. r cu 1 singur descendent
						// salvare unic descendent
						NodABC* temp = r->dr;
						if (r->st != NULL)
							temp = r->st;

						// dezalocare r
						free(r);

						// modificare r cu unicul descendent pentru a fi returnar in apel recursiv anterior
						r = temp;
					}
				}
			}
	}

	return r;
}

int main()
{

	FILE* f = fopen("ContABC.txt", "r");

	char buffer[256], separatori[] = ",\n";
	NodABC* arbore = NULL; // retine adresa nodului radacina dupa creare structura

	while (fgets(buffer, sizeof(buffer), f))
	{
		struct ContBancar tCont;
		char* token = strtok(buffer, separatori);
		tCont.cheie = (unsigned short int)atoi(token);
		
		token = strtok(NULL, separatori);
		strcpy(tCont.iban, token);

		token = strtok(NULL, separatori);
		strcpy(tCont.moneda, token);

		token = strtok(NULL, separatori);
		tCont.titular = (char*)malloc(strlen(token) + 1);
		strcpy(tCont.titular, token);

		token = strtok(NULL, separatori);
		tCont.sold = (float)atof(token);

		// inserare cont bancar in arbore binar de cautare
		unsigned char inserat;
		arbore = inserare_cont_ABC(arbore, tCont, &inserat); // inserare nod in ABC
		if (!inserat)
		{
			printf("Nodul %d nu a fost inserat!\n", tCont.cheie);
			free(tCont.titular);
		}
	}

	// traversare ABC dupa creare
	printf("\nArbore traversat in inordine: ");
	inordine_ABC(arbore);
	printf("\n\n");

	// cautare nod pe baza de cheie in ABC
	ContBancar* p_cont = NULL;
	p_cont = cauta_cont_bancar(arbore, 84);
	if (p_cont != NULL)
	{
		printf("Cont bancar identificat: %d %s\n", p_cont->cheie, p_cont->iban);
	}
	else
		printf("Contul bancar nu exista in ABC!\n");

	// numar conturi cu acelasi titular
	unsigned char nr_titulari = 0;
	nr_titulari = nr_conturi_titular(arbore, "Sandru Vasile");
	printf("Numar de conturi bancare cu acelasi nume titular: %u", nr_titulari);

	// stergere nod in ABC
	ContBancar cont;
	cont.titular = NULL; // flag pentru succes operatie de stergere nod
	arbore = stergere_nod_cheie(arbore, 95, &cont);
	if (cont.titular != NULL)
	{
		// nodul a fost sters
		printf("\n\nCont bancar sters din arbore: %s %s\n", cont.iban, cont.titular);
	}
	else
	{
		printf("\n\nCont bancar neidentificat in arbore!\n");
	}
	printf("Arbore binar de cautare dupa operatia de stergere nod:\n");
	inordine_ABC(arbore);

	// dezalocare structura ABC
	arbore = dezalocare_ABC(arbore);
	printf("\nArborele dupa dezalocare: ");
	inordine_ABC(arbore);
	printf("\n\n");

	// dezalocare cont bancar extras din arbore binar de cautare
	free(cont.titular);

	fclose(f);
	return 0;
}