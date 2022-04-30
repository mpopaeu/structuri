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
	struct node* pNext;
}Node;

typedef struct Employee NodeInfo;

#define LINE_BUFFEER 1024
/*functions signatures for memory management*/
NodeInfo* createInfo(short, char*, char*, double);
Node* createNode(NodeInfo*);
/*functions signatures for list operations*/
Node* insertPozitieLista(Node*, NodeInfo*, int poz); // 1..n (poz <= 1 - inserare la inceput; poz > n - inserare la sfarsit)
void printInfo(NodeInfo*);
Node* splitList(Node*);
Node* deleteFirstNode(Node*);

void main()
{
	Node* list = NULL;
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
			list = insertPozitieLista(list, info, poz);
		}

		fclose(pFile);

		printf("\nLista Simpla dupa creare:\n");
		Node* aux = list;
		while (aux)
		{
			printInfo(aux->info);
			aux = aux->pNext;
		}
		Node* subList1 = list;
		Node* subList2 = splitList(subList1);
		printf("\nSublista Simpla 1 dupa split:\n");
		aux = subList1;
		printf("\n-----------------------\n");
		while (aux)
		{
			printInfo(aux->info);
			aux = aux->pNext;
		}
		printf("\nSublista Simpla 2 dupa split:\n");
		aux = subList2;
		printf("\n-----------------------\n");
		while (aux)
		{
			printInfo(aux->info);
			aux = aux->pNext;
		}

		// dezalocare liste simple (subList1, subList2)
		while (subList1)
		{
			subList1 = deleteFirstNode(subList1);
		}
		while (subList2)
		{
			subList2 = deleteFirstNode(subList2);
		}

		list = subList1;
		printf("\nSublista Simpla 1 dupa dezalocare:\n");
		aux = subList1;
		printf("\n-----------------------\n");
		while (aux)
		{
			printInfo(aux->info);
			aux = aux->pNext;
		}
		printf("\nSublista Simpla 2 dupa dezalocare:\n");
		aux = subList2;
		printf("\n-----------------------\n");
		while (aux)
		{
			printInfo(aux->info);
			aux = aux->pNext;
		}
	}
}

Node* splitList(Node* subList1)
{
	int counter = 0;
	Node* aux = subList1;
	while (aux)
	{
		counter++;
		aux = aux->pNext;
	}
	aux = subList1;
	int index = 1;
	while (index++ < counter / 2)
		aux = aux->pNext;
	Node* subList2 = aux->pNext;
	aux->pNext = NULL;
	return subList2;
}

Node* insertPozitieLista(Node* headList, NodeInfo* info, int poz)
{
	Node* node = createNode(info);
	if (poz <= 1 || headList == NULL)
	{
		node->pNext = headList;
		headList = node;
	}
	else
	{
		int index = 1;
		Node* aux = headList;
		while (aux->pNext && index < poz - 1)
		{
			index++;
			aux = aux->pNext;
		}
		node->pNext = aux->pNext;
		aux->pNext = node;
	}
	return headList;
}

void printInfo(NodeInfo* info)
{
	printf("Code: %d - Name: %s\n", info->code, info->name);
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
Node* createNode(NodeInfo* info)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->info = info;
	node->pNext = NULL;
	return node;
}

Node* deleteFirstNode(Node* list)
{
	if (list)
	{
		Node* tmp = list;
		list = list->pNext;

		free(tmp->info->name); // dezalocare nume angajat
		free(tmp->info->dept); // dezalocare departament
		free(tmp->info); // dezalocare angajat (Employee)
		free(tmp); // dezalocare nod LS
	}

	return list;
}