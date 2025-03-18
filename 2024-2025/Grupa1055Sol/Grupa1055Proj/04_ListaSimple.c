#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define NR_CIFRE_CARD 16
#define DIM_MONEDA 3
#define DIM_VECTOR_CARDBANCAR 27

struct DataExpirare
{
	unsigned short int anul;
	unsigned char luna;
};

typedef struct DataExpirare DataExpirare;

struct CardBancar
{
	char nr_card[NR_CIFRE_CARD + 1]; // +1 pentru terminatot de string util in cazul utilizarii ca string
	char* titular;
	DataExpirare data;
	float sold;
	char moneda[DIM_MONEDA + 1]; // RON, EUR, USD
};

typedef struct CardBancar CardBancar;

struct Nod
{
	CardBancar card;
	struct Nod* next;
};

typedef struct Nod Nod;

int main()
{


	return 0;
}