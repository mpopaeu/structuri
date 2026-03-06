#include <stdio.h>
#include <string.h>

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
	printf("Dimensiune structura Angajat = %d bytes\n\n", sizeof(Angajat));

	Angajat ang;

	ang.nume = "Popescu Georgian";
	ang.salariu = (float)7788.29;
	strcpy(ang.CNP, "1950826421098");
	ang.functie = "Data analyst";
	ang.vechime_ani = 8;

	Angajat* pang;

	pang = &ang;

	printf("Nume angajat = %s, functie angajat = %s\n", pang->nume, (*pang).functie);

	return 0;
}