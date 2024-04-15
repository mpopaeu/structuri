#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define HTABLE_SIZE 200

struct ContBancar
{
	char iban[25]; // 24 bytes pt iban + 1 byte terminator string
	char moneda[4]; // 3 bytes pt cod moneda + 1 byte terminator string
	char* titular;
	float sold;
};

struct NodLS
{
	struct ContBancar data;
	struct NodLS* next;
};

struct NodLSR // nod lista simpla cu referinta la ContBancar din tabela de dispersie
{
	struct ContBancar * pdata;
	struct NodLSR* next;
};

typedef struct ContBancar ContBancar;
typedef struct NodLS NodLS;
typedef struct NodLSR NodLSR;

unsigned char functie_hash_string(char* cheie, unsigned char ht_size)
{
	return cheie[0] % ht_size;
}

NodLS* inserare_sfarsit(NodLS* p, ContBancar cont)
{
	NodLS* nou = (NodLS*)malloc(sizeof(NodLS));
	nou->data = cont;
	nou->next = NULL;

	if (p == NULL)
		return nou;

	NodLS* t = p;
	while (t->next != NULL)
		t = t->next;
	// t este ultimul nod din lista simpla p
	t->next = nou;

	return p;
}

void inserare_tabela_hash(NodLS ** HT, unsigned char size, ContBancar cont)
{
	// 1. calcul pozitie in tabela hash
	unsigned char pos = functie_hash_string(cont.titular, size); // cuprins in [0; 199]

	// 2. inserare cont bancar in lista simpla de pe pozitia determinata la 1.
	HT[pos] = inserare_sfarsit(HT[pos], cont); // HT[pos] se modifica la insearea primului nod 
											   // in lista HT[pos] empty (0 noduri)
}

NodLSR* inserare_inceput_ref(NodLSR* lista, ContBancar* cont)
{
	NodLSR* nou = (NodLSR*)malloc(sizeof(NodLSR));
	nou->pdata = cont;
	nou->next = lista;

	return nou;
}

// cautare conturi bancare pentru un titular specificat
// referintele conturilor bancare se salveaza in lista separata cu noduri NodLSR
NodLSR* cauta_conturi_titular(NodLS** HT, unsigned char size, char* titular_cautat)
{
	// 1. calcul pozitie in tabela hash
	unsigned char pos = functie_hash_string(titular_cautat, size); // cuprins in [0; 199]

	// 2. cautare secventiala in lista HT[pos] conturi bancare cu titular_cautat
	NodLSR* lista_conturi = NULL; // structura destinatie
	NodLS* temp = HT[pos]; // temp este temporar pentru parsare lista simpla HT[pos] din tabela hash
	while (temp != NULL)
	{
		if (strcmp(temp->data.titular, titular_cautat) == 0)
		{
			// este identificat un nod cu titularul cautat
			// referinta la ContBancar din nodul temp este salvata in lista simpla destinatie lista_conturi
			lista_conturi = inserare_inceput_ref(lista_conturi, &temp->data);
		}

		temp = temp->next;
	}

	return lista_conturi;
}

// stergere conturi bancare pentru titular specificat
void stergere_conturi_bancare(NodLS** HT, unsigned char ht_size, char* titular_cautat)
{

}

int main()
{
	FILE* f = fopen("Conturi.txt", "r");
	NodLS** HTable = NULL; // var pt gestionarea tabelei de dispersie
	HTable = (NodLS**)malloc(HTABLE_SIZE * sizeof(NodLS*)); // alocare HTABLE_SIZE elemente
										// fiecare element este NodLS* (adresa inceput LS)
	for (unsigned char i = 0; i < HTABLE_SIZE; i++) 
		HTable[i] = NULL; // lista HTable[i] este empty
	
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

		// inserare cont bancar in lista dubla
		inserare_tabela_hash(HTable, HTABLE_SIZE, contB);

		contB.titular = NULL; // pentru a elimina partajarea dintre ultimul nod inserat si contB
		contB.iban[0] = 0;
	
		fscanf(f, "%s\n", contB.iban);
	}

	// cautare in tabela de dispersie (pentru cheia de cautare: titular cont bancar)
	// cheia de cautare nu are valoare unica -> salvare mai multe conturi cu acelasi nume titular
	// salvare conturi in lista simpla separata fata de tabela de dispersie
	NodLSR* conturi_titular = cauta_conturi_titular(HTable, HTABLE_SIZE, "Popescu Iulian");
	if (conturi_titular != NULL)
	{
		// lista de conturi contine cel putin 1 nod
		// exista cel putin 1 cont bancar pentru titular cautat in tabela de dispersie
		printf("Lista conturi bancare titular cautat:\n");
		NodLSR* temp = conturi_titular;
		while (temp != NULL)
		{
			printf("%s %s\n", temp->pdata->iban, temp->pdata->titular);
			temp = temp->next;
		}
	}
	else
	{
		// nu exista in tabela de dispersie conturi bancare cu titular cautat
		printf("Nu exista titular cautat in tabela de dispersie!\n");
	}


	// stergere conturi bancare din tabela de dispersie pentru titular specificat 
	stergere_conturi_bancare(HTable, HTABLE_SIZE, "Popescu Iulian");

	// dezalocare tabela de dispersie
	// se parseaza secvential vectorul suport al tabelei de dispersie
	for (unsigned char i = 0; i < HTABLE_SIZE; i++)
	{
		while (HTable[i] != NULL)
		{
			// lista HTable[i] contine cel putin 1 nod si trebuie dezalocata
			NodLS* temp = HTable[i];
			HTable[i] = HTable[i]->next;

			free(temp->data.titular); // dezalocare extensie in heap pentru datele contului bancar
			free(temp);				  // dezalocare nod din lista cu conturi bancare HTable[i]
		}
	}

	// dezalocare lista cu referinte la conturile bancare din tabela de dispersi
	while (conturi_titular != NULL)
	{
		// exista cel putin 1 nod in lista de referinte la conturi bancare
		NodLSR* temp = conturi_titular;
		conturi_titular = conturi_titular->next;

		free(temp); // doar dezalocare de nod, deoarece conturile bancare au fost dezalocate 
		// mai sus la dezalocare tabela de dispersie
	}

	fclose(f);
	return 0;
}