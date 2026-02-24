#include <stdio.h>

struct Client
{
	unsigned int id;
	char* denumire;
	unsigned char tip;
	char ultima_comanda[10];
	float valoare_totala_comenzi;
};

typedef struct Client Client;

int main()
{
	Client c;

	printf("Dimensiune Clien = %d bytes\n", sizeof(Client));

	return 0;
}