#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct BankAccount
{
	char iban[25]; // 24 bytes/positions for iban itself + 1 additional byte at the end (0x00)
	char* owner_name;
	double balance;
	char* currency;
};

typedef struct BankAccount BankAccount;

struct Node
{
	struct BankAccount data;
	struct Node* next;
};

typedef struct Node Node;

struct NodeD
{
	struct BankAccount *pdata;
	struct NodeD * next, * prev;
};

typedef struct NodeD NodeD;

struct DoubleList
{
	NodeD* head, * tail;
};

typedef struct DoubleList DoubleList;

struct NodeBST
{
	struct BankAccount data;
	struct NodeBST *left, *right;
};

typedef struct NodeBST NodeBST;