
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define VECTOR_SIZE 10

enum UM {RON, EUR, USD};

struct ContBancar
{
	char iban[24];
	char* titular;
	float sold;
	enum UM moneda;
	char activ; // boolean pentru cont activ; true - activ
};

// functia determina numarul de titulari "unici" din vector de conturi bancare

int main()
{
	FILE* f; 
	f = fopen("conturi.txt", "r");

	char buffer[BUFFER_SIZE], seps[] = ",\n";

	struct ContBancar v[VECTOR_SIZE];
	while (fgets(buffer, BUFFER_SIZE, f))
	{
		struct ContBancar cb;
		char * token = strtok(buffer, seps);
		strcpy(cb.iban, token);

		token = strtok(NULL, seps);
		cb.titular = (char*)malloc(strlen(token) + 1);
		strcpy(cb.titular, token);

		token = strtok(NULL, seps);
		cb.sold = atof(token);

		token = strtok(NULL, seps);
		if (strcmp(token, "RON") == 0)
			cb.moneda = RON;
		if (strcmp(token, "EUR") == 0)
			cb.moneda = EUR;
		if (strcmp(token, "USD") == 0)
			cb.moneda = USD;

		token = strtok(NULL, seps);
		if (strcmp(token, "true") == 0)
			cb.activ = 1;
		else
			if (strcmp(token, "false") == 0)
				cb.activ = 0;
		// populare vectorul v cu conturile din fisier
	}

	fclose(f);

}