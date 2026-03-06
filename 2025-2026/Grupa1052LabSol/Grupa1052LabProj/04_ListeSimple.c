#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct Angajat
{
	char* nume;					// 4 bytes
	float salariu;				// 4 bytes
	char CNP[14];				// 14 bytes
	char* functie;				// 4 bytes
	unsigned char vechime_ani;	// 1 byte
};

typedef struct Angajat Angajat;

int main()
{

	FILE* f;

	f = fopen("Angajati.txt", "r");

	char buffer[256];
	char seps[] = ",\n";

	while (fgets(buffer, sizeof(buffer), f))
	{
		Angajat ang;
		char* token = strtok(buffer, seps);
		ang.nume = malloc(strlen(token) + 1); // +1 pt byte nul ca terminator de string
		strcpy(ang.nume, token);

		token = strtok(NULL, seps);
		ang.salariu = (float)atof(token);

		token = strtok(NULL, seps);
		strcpy(ang.CNP, token);

		token = strtok(NULL, seps);
		ang.functie = malloc(strlen(token) + 1);
		strcpy(ang.functie, token);

		token = strtok(NULL, seps);
		ang.vechime_ani = atoi(token);


	}

	fclose(f);

	return 0;
}