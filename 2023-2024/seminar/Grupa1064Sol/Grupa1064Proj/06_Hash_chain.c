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

typedef struct ContBancar ContBancar;
typedef struct NodLS NodLS;

void inserare_tabela_hash(NodLS ** HT, unsigned char size, ContBancar cont)
{

}

int main()
{
	FILE* f = fopen("Conturi.txt", "r");
	NodLS** HTable = NULL; // var pt gestionarea tabelei de dispersie
	HTable = (NodLS**)malloc(HTABLE_SIZE * sizeof(NodLS*));
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

	fclose(f);
	return 0;

}