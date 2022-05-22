#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
struct Employee
{
	unsigned short code;
	char* name;
	char* dept;
	double salary;
};

typedef struct node
{
	struct Employee* info;
	struct node* pNext;
}Node;

typedef struct Employee NodeInfo;

#define LINE_BUFFER 1024
#define HASH_TABLE_SIZE 100 // doar pana la 255 elemente; tip unsigned char

NodeInfo* createInfo(short code, char* name, char* dept, double salary)
{
	struct Employee* emp = (NodeInfo*)malloc(sizeof(NodeInfo));
	emp->code = code;
	emp->name = (char*)malloc(strlen(name) + 1);
	strcpy(emp->name, name);
	emp->dept = (char*)malloc(strlen(dept) + 1);
	strcpy(emp->dept, dept);
	emp->salary = salary;
	return emp;
}

// [in] list - lista simpla in care se insereaza angajatul emp
// [in] emp - adresa cu datele angajatului care se insereaza la inceputul listei list
// [return] adresa de inceput actualizata a listei list dupa inserare nod/angajat la inceput
Node* insert_node(Node* list, NodeInfo* emp)
{
	Node* nou = (Node*)malloc(sizeof(Node));

	nou->info = emp;
	nou->pNext = list;

	return nou;
}

// [in] ht_size - dimensiunea vectorului suport pentru tabela de dispersie (max 255 liste de coliziuni)
// [in] key - cheia de cautare (cheie numerica)
// [return] pozitia in tabela de dispersie unde se va afla setul de date identificat prin key
unsigned char hash_function(unsigned char ht_size, unsigned short int key)
{
	return(key % ht_size);
}

// [in] ht - vectorul suport (in mem heap) pentru tabela hash cu chaining
// [in] ht_size - nr de elemente vector ht
// [in] emp - datele angajatului care se insereaza in ht
// [return] -
void inserare_hash_table(Node** ht, unsigned char ht_size, NodeInfo* emp)
{
	unsigned char poz = hash_function(ht_size, emp->code); // poz de nr lista in care emp tb sa se insereze
	printf("\nPozitie calculata %u pentru cheia %s", poz, emp->name);

	ht[poz] = insert_node(ht[poz], emp); // inserare angajat emp la inceputul listei simple ht[poz]
}

// [in] ht - vector suport pentru tabela hash
// [in] ht_size - nr de elemente vector ht
// [in] key - cheia de cautare a unui angajat
// [return] - adresa angajat identificat; daca nu exista in tabela hash, atunci este NULL
NodeInfo* search_employee(Node** ht, unsigned char ht_size, unsigned short int key)
{
	unsigned char poz = hash_function(ht_size, key);

	Node* tmp = ht[poz]; // adresa primului nod din lista poz
	while (tmp)
	{
		if (tmp->info->code == key)
		{
			return tmp->info; // adresa angajatului identificat in lista poz
		}

		tmp = tmp->pNext;
	}

	return NULL; // nu exista angajat cu cheia cautata key
}

// stergere angajat in tabela hash dupa cod
// dezalocare tabela hash cu chaining
// export angajati in vector; se selecteaza angajatii cu cod in interval specificat; export cu stergere angajati din tabela hash
// [in] ht - tabela hash implementata cu chaining
// [in] size - nr de elemente tabela hash ht
// [in] inf - limita inferioara a intervalului de coduri pentru care se cauta angajati in tabela hash ht
// [in] sup - limita superioara a intervalului de coduri pentru care se cauta angajati in tabela hash ht
// [out] vemp_size - numarul de angajati identificati in tabela ht pe baza interval coduri; este calculat in functie
// [out] result - cod de eroare cu privire la validarea input-ului
// [return] adresa de mem heap unde incepe vectorul de angajati identificati in intervalul [inf, sup]; vectorul nu partajeaza zone de heap cu tabela hash
struct Employee* export_employees(Node** ht, unsigned char size, unsigned short int inf, unsigned short int sup, 
									unsigned int *vemp_size, unsigned char *result)
{
	*vemp_size = 0; // intializare dimensiune vector
	struct Employee* vemp = NULL; // vectorul de angajati care se creeaza si populeaza in functie

	*result = 0; // operatie efectuata cu succes, nu exista erori de I/O
	if (inf > sup)
	{
		*result = 1; // cod de eroare pentru limite incorecte [inf, sup]
	}
	else
	{

		for (unsigned short int i = inf; i <= sup; i++)
		{
			NodeInfo* pemp = search_employee(ht, size, i); // caut angajat cu codul i
			if (pemp != NULL)
			{
				// exista angajat cu codul i
				*vemp_size += 1; // incrementez nr de angajati identificati in tabela hash
			}
		}

		if (*vemp_size != 0)
		{
			// exista cel putin 1 angajat identificat in tabela hash
			unsigned int k = 0;
			// alocare vector de angajati
			vemp = (struct Employee*)malloc(*vemp_size * sizeof(struct Employee));

			for (unsigned short int i = inf; i <= sup; i++)
			{
				NodeInfo* pemp = search_employee(ht, size, i);
				if (pemp != NULL)
				{
					// exista angajat cu codul i
					vemp[k].code = pemp->code;
					vemp[k].salary = pemp->salary;

					vemp[k].name = (char*)malloc(strlen(pemp->name) + 1);
					strcpy(vemp[k].name, pemp->name);

					vemp[k].dept = (char*)malloc(strlen(pemp->dept) + 1);
					strcpy(vemp[k].dept, pemp->dept);

					k += 1;
				}
			}
		}
	}

	return vemp;
}


void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	char* token = NULL, lineBuffer[LINE_BUFFER];
	const char* sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
	
	Node** HTable = NULL; // vectorul suport pentru tabela hash cu chaining

	HTable = (Node**)malloc(HASH_TABLE_SIZE * sizeof(Node*));

	for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		HTable[i] = NULL;

	if (pFile)
	{
		while (fgets(lineBuffer, sizeof(lineBuffer), pFile) != NULL)
		{
			token = strtok(lineBuffer, sepList);
			code = atoi(token);
			name = strtok(NULL, sepList);
			dept = strtok(NULL, sepList);
			token = strtok(NULL, sepList);
			salary = atof(token);
			token = strtok(NULL, sepList);
			int poz = atoi(token);
			NodeInfo* info = createInfo(code, name, dept, salary);
			
			inserare_hash_table(HTable, HASH_TABLE_SIZE, info); // inserare angajat info in tabela hash
		}
		fclose(pFile);

		// parsare tabela hash pentr validare continut
		printf("\nContinut tabela de dispersie:");
		for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		{
			if (HTable[i])
			{
				printf("\nLista de coliziuni %u", i);
				Node* tmp = HTable[i];
				while (tmp)
				{
					printf("\n\t%hu %s", tmp->info->code, tmp->info->name);

					tmp = tmp->pNext;
				}
			}
		}

		// cautare angajat in tabela hash dupa cheie de cautare (cod angajat)
		NodeInfo* emp = search_employee(HTable, HASH_TABLE_SIZE, (unsigned short int)10031);
		if (emp)
		{
			printf("\nAngajat identificat in tabela hash: %hu %s", emp->code, emp->name);
		}
		else
			printf("\nAngajatul nu a fost identificat");

		unsigned int v_size;
		struct Employee* v_emp;
		unsigned char result;

		v_emp = export_employees(HTable, HASH_TABLE_SIZE, (unsigned int)10100, (unsigned int)10001, &v_size, &result);

		if (result == 0)
		{
			if (v_emp)
			{
				// exista cel putin 1 angajat identificat
				printf("\nVector angajati exportati din tabela hash:");
				for (unsigned int i = 0; i < v_size; i++)
					printf("\n\t%hu  %s", v_emp[i].code, v_emp[i].name);
			}
			else
			{
				printf("\nVector empty cu angajati \"filtrati\" din tabela hash\n");
			}
		}
		else
		{
			printf("\nInterval coduri angajati este specificat eronat.\n");
		}

		// dezalocare tabela hash
		for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
		{
			if (HTable[i])
			{
				// exista cel putin 1 nod in lista simpla HTable[i]
				while (HTable[i])
				{
					Node* tmp = HTable[i];

					HTable[i] = HTable[i]->pNext; // noul inceput de lista simpla HTable[i]

					free(tmp->info->name);
					free(tmp->info->dept);
					free(tmp->info);
					free(tmp);
					// tmp = NULL;
				}
			}
		}
		free(HTable); // dezalocare vector de liste (empty)
		HTable = NULL;

		printf("\nContinut tabela de dispersie dupa dezalocare:");
		if (HTable)
		{
			for (unsigned char i = 0; i < HASH_TABLE_SIZE; i++)
			{
				if (HTable[i])
				{
					printf("\nLista de coliziuni %u", i);
					Node* tmp = HTable[i];
					while (tmp)
					{
						printf("\n\t%hu %s", tmp->info->code, tmp->info->name);

						tmp = tmp->pNext;
					}
				}
			}
		}

		// dezalocare vector de angajati
		for (unsigned int i = 0; i < v_size; i++)
		{
			free(v_emp[i].name);
			free(v_emp[i].dept);
		}
		free(v_emp);
		v_emp = NULL;

		printf("\nVector angajati exportati din tabela hash dupa dezalocare:");
		if (v_emp)
		{
			for (unsigned int i = 0; i < v_size; i++)
				printf("\n\t%hu  %s", v_emp[i].code, v_emp[i].name);
		}
	}
}