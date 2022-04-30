#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"
struct Employee
{
	short code;
	char* name;
	char* dept;
	double salary;
};

typedef struct node
{
	struct Employee* info;
	struct node* pNext, *pPrev;
}Node;

typedef struct listd
{
	struct node* first, * last;
}ListD;

typedef struct Employee NodeInfo;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo*);
/*functions signatures for list operations*/
ListD insertListPos(ListD, NodeInfo*, unsigned int poz); // 1..n (poz = 0, 1 - inserare la inceput; poz > n - inserare la sfarsit)
void printInfo(NodeInfo*);

// splitare lista dubla la mijloc in 2 subliste
// dezalocare lista dubla

void main()
{
	ListD list;
	list.first = list.last = NULL; // initial, lista duble este empty
	FILE* pFile = fopen("Data.txt", "r");
	char* token = NULL, lineBuffer[LINE_BUFFEER];
	const char* sepList = ",\n";
	char* name = NULL, * dept = NULL; short code = 0; double salary = 0.0;
	int poz = 0;
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
			poz = atoi(token);
			NodeInfo* info = createInfo(code, name, dept, salary);
			list = insertListPos(list, info, poz);
		}

		printf("\nLista Dubla dupa creare (inceput->sfarsit):\n");
		Node* aux = list.first;
		while (aux)
		{
			printInfo(aux->info);
			aux = aux->pNext;
		}

		printf("\nLista Dubla dupa creare (sfarsit->inceput):\n");
		aux = list.first;
		while (aux)
		{
			printInfo(aux->info);
			aux = aux->pPrev;
		}

		fclose(pFile);
	}
}

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
Node* createNode(NodeInfo* empInfo)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = empInfo;
	node->pNext = NULL;
	node->pPrev = NULL;
	return node;
}

ListD insertListPos(ListD listD, NodeInfo* info, unsigned int poz)
{
	Node* new_node = createNode(info);
	if (listD.first == NULL)
	{
		// inserare in lista dubla empty
		listD.first = listD.last = new_node;
	}
	else
	{
		if (poz <= 1)
		{
			// inserare la inceput in lista dubla non-empty
			new_node->pNext = listD.first;
			listD.first->pPrev = new_node;
			listD.first = new_node;
		}
		else
		{
			unsigned int index = 1;
			Node* aux = listD.first;
			while (aux && (index < poz))
			{
				index++;
				aux = aux->pNext;
			}

			if (aux)
			{
				// inserare la interior
				new_node->pNext = aux;
				new_node->pPrev = aux->pPrev;
				aux->pPrev->pNext = new_node;
				aux->pPrev = new_node;
			}
			else
			{
				// inserare la sfarsitul listei duble
				new_node->pPrev = listD.last;
				listD.last->pNext = new_node;
				listD.last = new_node;
			}
			
		}
	}

	return listD;
}

void printInfo(NodeInfo* info)
{
	printf("Code: %d - Name: %s\n", info->code, info->name);
}