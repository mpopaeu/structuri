#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define VECTOR_SIZE 10
#define BUFFER_SIZE 256

struct ContBancar
{
	char iban[24];
	char* titular;
	char moneda[4];
	float sold;
	unsigned int nr_carduri;
};

// functie pentru determinare solduri conturi bancare grupate pe moneda
// conturile utilizate sunt cele stocate in vectorul vcd

int main()
{

	struct ContBancar cb, vcb[VECTOR_SIZE];
	FILE* f;
	unsigned int i = 0;

	f = fopen("Conturi.txt", "r");

	char buffer[BUFFER_SIZE], seps[]=",\n";

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		char* token;
		token = strtok(buffer, seps);
		strcpy(cb.iban, token);

		token = strtok(NULL, seps);
		cb.titular = (char*)malloc(strlen(token) + 1); // +1 pentru terminat de string, adica byte 0x00
		strcpy(cb.titular, token);

		token = strtok(NULL, seps);
		strcpy(cb.moneda, token);

		token = strtok(NULL, seps);
		cb.sold = atof(token);

		token = strtok(NULL, seps);
		cb.nr_carduri = atoi(token);

		vcb[i++] = cb;
	}

	fclose(f);
	return 0;
}