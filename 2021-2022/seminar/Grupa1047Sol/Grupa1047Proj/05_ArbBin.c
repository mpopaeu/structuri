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
	struct node* pLeft, *pRight;
}NodeBST;

typedef struct Employee NodeInfo;
#define LINE_BUFFER 1024

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

NodeBST* insert_node_BST(NodeBST* r, NodeInfo* emp_info, unsigned char *insert)
{
	if (r)
	{
		// continuarea cautare loc de inserat
		if (r->info->code > emp_info->code)
			r->pLeft = insert_node_BST(r->pLeft, emp_info, insert);
		else
			if (r->info->code < emp_info->code)
				r->pRight = insert_node_BST(r->pRight, emp_info, insert);
			else
				*insert = 0; // inserare nu are loc deoarece cheia este duplicat
		return r;
	}
	else
	{
		// locul de inserat este identificat
		NodeBST* nou = (NodeBST*)malloc(sizeof(NodeBST));
		nou->info = emp_info;
		nou->pLeft = NULL;
		nou->pRight = NULL;

		*insert = 1; // inserarea are loc
		return nou;
	}
}

void inordine(NodeBST *r)
{
	if (r)
	{
		inordine(r->pLeft);
		printf("\n%hu %s", r->info->code, r->info->name);
		inordine(r->pRight);
	}
}

NodeBST* delete_node_BST(NodeBST* r, unsigned short int emp_id, struct Employee* *emp)
{
	if (r)
	{
		// continuarea cautare nod care se sterge
		if (r->info->code > emp_id)
			r->pLeft = delete_node_BST(r->pLeft, emp_id, emp);
		else
			if (r->info->code < emp_id)
				r->pRight = delete_node_BST(r->pRight, emp_id, emp);
			else
			{
				// a fost identificat nodul de sters (r)
				if (r->pLeft == NULL && r->pRight == NULL)
				{
					// nodul de sters este frunza in arbore binar de cautare
					*emp = r->info; // salvare adresa heap Employee in parametrul de output emp
					free(r);
					r = NULL; // se rescrie NULL in parintele nodului de sters in apelul (i-1)
				}
				else
				{
					if (r->pLeft != NULL && r->pRight != NULL)
					{
						// nodul de sters are 2 descendenti
						NodeBST* temp = r->pRight;
						while (temp->pLeft)
							temp = temp->pLeft;

						*emp = r->info;
						
						// v1
						r->pRight = delete_node_BST(r->pRight, temp->info->code, &r->info);

						// v2
						// r->info = temp->info;
						// struct Employee *p_emp;
						// r->pRight = delete_node_BST(r->pRight, temp->info->code, &p_emp);
					}
					else
					{
						// nodul de sters are 1 singur descendent
						// tmp folosit pentru stocarea unicului descendent
						NodeBST* temp;
						if (r->pLeft)
							temp = r->pLeft;
						else
							temp = r->pRight;

						*emp = r->info;
						free(r);
						r = temp; // unicul descendent intors in apelul (i-1) unde va rescrie descendentul parintelui nodului sters
					}
				}
			}		
	}

	return r;
}

// extragere noduri de pe nivel specificat (vector, lista)
// determinare drum invers de la nod specificat prin cheie

void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	char* token = NULL, lineBuffer[LINE_BUFFER];
	const char* sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;

	NodeBST* root = NULL;

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

			unsigned char insert;
			root = insert_node_BST(root, info, &insert);

			if (insert)
			{
				printf("\nAngajatul %hu a fost inserat in arbore.", info->code);
			}
			else
			{
				printf("\nAngajatul %hu NU a fost inserat in arbore.", info->code);
				free(info->name);
				free(info->dept);
			}
		}
		fclose(pFile);
	}


	printf("\nArborele BST dupa creare:\n");
	inordine(root);

	struct Employee* pemp = NULL;
	root = delete_node_BST(root, 10101, &pemp);
	if (pemp)
	{
		printf("\nAngajatul %hu %s a fost extras din arbore.", pemp->code, pemp->name);
	}
	else
	{
		printf("\nAngajatul NU exista in arbore!");
	}

	printf("\nArborele BST dupa stergere nod:\n");
	inordine(root);
}